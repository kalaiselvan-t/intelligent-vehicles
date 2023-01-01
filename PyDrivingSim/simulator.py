# Authors : Gastone Pietro Rosati Papini
# Date    : 09/08/2022
# License : MIT

import signal

from pydrivingsim import World, Vehicle, TrafficLight, Agent

class GracefulKiller:
  kill_now = False
  def __init__(self):
    signal.signal(signal.SIGINT, self.exit_gracefully)
    signal.signal(signal.SIGTERM, self.exit_gracefully)

  def exit_gracefully(self, *args):
    self.kill_now = True

def main():
    vehicle = Vehicle()
    vehicle.set_screen_here()
    agent = Agent(vehicle)
    trafficlight = TrafficLight()
    trafficlight.set_pos((162,-2))

    killer = GracefulKiller()
    while not killer.kill_now and World().loop:
        agent.compute()
        action = agent.get_action()

        vehicle.set_screen_here()
        vehicle.control([action[0], 0])

        World().update()

    agent.terminate()
    World().exit()

main()