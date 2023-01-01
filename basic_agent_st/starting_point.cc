//
// Created by Gastone Pietro Rosati Papini on 10/08/22.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <numeric>
//#include "codegen/lib/pass_primitive/pass_primitive.h"
#include "codegen/lib/primitives/primitives.h"
#include "codegen/lib/v_opt/v_opt.h"

extern "C" {
#include "screen_print_c.h"
}
#include "screen_print.h"
#include "server_lib.h"
#include "logvars.h"
#include <iostream>

// --- MATLAB PRIMITIVES INCLUDE ---
// #include "primitives.h"
// --- MATLAB PRIMITIVES INCLUDE ---

#define DEFAULT_SERVER_IP    "127.0.0.1"
#define SERVER_PORT                30000  // Server port
#define DT 0.05

double v_0;
double a_0;
double lookhead;
double x_in = 10.0;
double x_tr,x_stop;
double coeffsT1[6];
double coeffsT2[6];
double best_coeff[6];
double stop_coeff[6];
double j0_coeff[6];

double x_s = 5.0;
double max_sf;
double t_f;
double vfj0,tfj0;

double v_r = 8.0;
double V_min = 3.0;
double V_max = 15.0;

double t_s = x_s / V_min;
double t_in = x_in / V_min;

double t_green,t_red;


// Handler for CTRL-C
#include <signal.h>
static uint32_t server_run = 1;
void intHandler(int signal) {
    server_run = 0;
}

double v1,v2,T1,T2;

double low_level_ctrl
        (double vel, double acc, double minAcc, double maxAcc)
{
    static double old_req_acc = 0.0;
    double long_gain = 1.0;
    double j0 = best_coeff[3];
    double s0 = best_coeff[4];
    double cr0 = best_coeff[5];
    double toffs = 0.0;
    double jT0 = j0 + toffs * s0 + 0.5 * toffs * toffs * cr0;
    double jT1 = j0 + (DT+toffs)*s0 + 0.5*(DT*toffs)*(DT*toffs)*cr0;
    double Jint = (DT * (jT1) + jT0) * 0.5;
    double req_acc = std::min(std::max((old_req_acc + long_gain * Jint),minAcc),maxAcc);
    old_req_acc = req_acc;
//    double req_vel = v_opt(DT,vel,acc,best_s,best_v)

    static double integral = 0.0;
    double P_gain = 0.02;
    double I_gain = 1.0;
    double error = req_acc - acc;
    integral = integral + error * DT;
    double req_ped = P_gain * error + I_gain * integral;

    if(vel < 0.1 && old_req_acc < 0 && Jint > 0.0)
    {
        old_req_acc = 0.0;
        integral = 0.0;
    }

    return req_ped;
}

void freeflow
    (double a0, double v0, double xf, double vr)
{
    pass_primitive(v0,a0,xf,vr,vr,0.0,0.0,coeffsT2,&v2,&T2,coeffsT1,&v1,&T1);
}

int main(int argc, const char * argv[]) {
    logger.enable(true);

    // Messages variables
    scenario_msg_t scenario_msg;
    manoeuvre_msg_t manoeuvre_msg;
    size_t scenario_msg_size = sizeof(scenario_msg.data_buffer);
    size_t manoeuvre_msg_size = sizeof(manoeuvre_msg.data_buffer);
    uint32_t message_id = 0;

#ifndef _MSC_VER
    // More portable way of supporting signals on UNIX
    struct sigaction act;
    act.sa_handler = intHandler;
    sigaction(SIGINT, &act, NULL);
#else
    signal(SIGINT, intHandler);
#endif

    server_agent_init(DEFAULT_SERVER_IP, SERVER_PORT);

    // Start server of the Agent
    printLine();
    printTable("Waiting for scenario message...", 0);
    printLine();
    while (server_run == 1) {

        // Clean the buffer
        memset(scenario_msg.data_buffer, '\0', scenario_msg_size);

        // Receive scenario message from the environment
        if (server_receive_from_client(&server_run, &message_id, &scenario_msg.data_struct) == 0) {
            // Init time
            static auto start = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::now()-start;
            double num_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(time).count()/1000.0;
            printLogTitle(message_id, "received message");

            // Data struct
            input_data_str *in = &scenario_msg.data_struct;
            manoeuvre_msg.data_struct.CycleNumber = in->CycleNumber;
            manoeuvre_msg.data_struct.Status = in->Status;

            // Agent Code
            v_0 = in->VLgtFild;
            a_0 = in->ALgtFild;
            lookhead = std::max(50.0,v_0 * 5.0);

            if(in->NrTrfLights != 0)
            {
                x_tr = in->TrfLightDist;
                x_stop = in->TrfLightDist - x_s / 2.0;
            }

            if(in->TrfLightDist == 0.0 || x_tr > lookhead)
            {
                freeflow(a_0,v_0,in->TrfLightDist,v_r);
                for (int i = 0; i < 6; ++i)
                {
                    best_coeff[i] = coeffsT2[i];
                }
            }
            else
            {
                switch(in->TrfLightCurrState)
                {
                    case 1:
                        t_green = 0;
                        t_red = in->TrfLightFirstTimeToChange - t_in;
                        break;
                    case 2:
                        t_green = in->TrfLightSecondTimeToChange + t_s;
                        t_red = in->TrfLightThirdTimeToChange - t_in;
                        break;
                    case 3:
                        t_green = in->TrfLightFirstTimeToChange + t_s;
                        t_red = in->TrfLightSecondTimeToChange - t_in;
                        break;
                }
                if(in->TrfLightCurrState == 1 && in->TrfLightDist <= x_s)
                {
                    freeflow(v_0,a_0,lookhead,v_r);
                    for (int i = 0; i < 6; ++i)
                    {
                        best_coeff[i] = coeffsT2[i];
                    }
                }
                else
                {
                    pass_primitive(v_0,a_0,x_tr,V_min,V_max,t_green,t_red,coeffsT2,&v2,&T2,coeffsT1,&v1,&T1);
                    double sum1 = std::accumulate(std::begin(coeffsT1),std::end(coeffsT1),0.0,std::plus<double>());
                    double sum2 = std::accumulate(std::begin(coeffsT2),std::end(coeffsT2),0.0,std::plus<double>());
                    if(sum1 == 0.0 && sum2 == 0.0)
                    {
                        stop_primitive(v_0,a_0,x_stop,stop_coeff,&max_sf,&t_f);
                        for (int i = 0; i < 6; ++i)
                        {
                            best_coeff[i] = stop_coeff[i];
                        }
                    }
                    else
                    {
                        if ((coeffsT1[2] < 0.0 && coeffsT2[2] > 0.0) || (coeffsT1[2] > 0.0 && coeffsT2[2] < 0.0))
                        {
                            pass_primitive_j0(v_0,a_0,x_tr,V_min,V_max,j0_coeff,&vfj0,&tfj0);
                            for (int i = 0; i < 6; ++i)
                            {
                                best_coeff[i] = j0_coeff[i];
                            }
                        }
                        else
                        {
                            if (std::abs(coeffsT1[2]) < std::abs(coeffsT2[2]))
                            {
                                for (int i = 0; i < 6; ++i)
                                {
                                    best_coeff[i] = coeffsT1[i];
                                }
                            }
                            else
                            {
                                for (int i = 0; i < 6; ++i)
                                {
                                    best_coeff[i] = coeffsT2[i];
                                }
                            }
                        }
                    }
                }
            }

            // Example of using log
            logger.log_var("Example", "cycle", in->CycleNumber);
//          logger.log_var(,"No of traffic lights: ", in->NrTrfLights);
            std::cout << "Traffic distance: " << in->TrfLightDist << std::endl;



            
            manoeuvre_msg.data_struct.RequestedAcc = low_level_ctrl(in->VLgtFild,in->ALgtFild,-2.0, 2.0);
//            manoeuvre_msg.data_struct.TargetSpeed = 3.0;
            // ADD LOW LEVEL CONTROL CODE HERE

            // Write log
            logger.write_line("Example");

            // Screen print
            printLogVar(message_id, "Time", num_seconds);
            printLogVar(message_id, "Status", in->Status);
            printLogVar(message_id, "CycleNumber", in->CycleNumber);

            // Send manoeuvre message to the environment
            if (server_send_to_client(server_run, message_id, &manoeuvre_msg.data_struct) == -1) {
                perror("error send_message()");
                exit(EXIT_FAILURE);
            } else {
                printLogTitle(message_id, "sent message");
            }
        }
    }

    // Close the server of the agent
    server_agent_close();
    return 0;
}