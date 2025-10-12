from abc import ABC, abstractmethod
from direction import Direction
from light_color import LightColor
from typing import TYPE_CHECKING
import time

if TYPE_CHECKING:
    from intersection_controller import IntersectionController

class IntersectionState(ABC):
    @abstractmethod
    def handle(self, context: 'IntersectionController'):
        pass

class EastWestGreenState(IntersectionState):
    def handle(self, context: 'IntersectionController'):
        print(f"\n--- INTERSECTION {context.get_id()}: Cycle -> East-West GREEN ---")

        # Turn East and West green, ensure North and South are red
        context.get_light(Direction.EAST).start_green()
        context.get_light(Direction.WEST).start_green()
        context.get_light(Direction.NORTH).set_color(LightColor.RED)
        context.get_light(Direction.SOUTH).set_color(LightColor.RED)

        # Wait for green light duration
        time.sleep(context.get_green_duration() / 1000.0)

        # Transition East and West to Yellow
        context.get_light(Direction.EAST).transition()
        context.get_light(Direction.WEST).transition()

        # Wait for yellow light duration
        time.sleep(context.get_yellow_duration() / 1000.0)

        # Transition East and West to Red
        context.get_light(Direction.EAST).transition()
        context.get_light(Direction.WEST).transition()

        # Change the intersection's state back to let North-South go
        context.set_state(NorthSouthGreenState())

class NorthSouthGreenState(IntersectionState):
    def handle(self, context: 'IntersectionController'):
        print(f"\n--- INTERSECTION {context.get_id()}: Cycle Start -> North-South GREEN ---")

        # Turn North and South green, ensure East and West are red
        context.get_light(Direction.NORTH).start_green()
        context.get_light(Direction.SOUTH).start_green()
        context.get_light(Direction.EAST).set_color(LightColor.RED)
        context.get_light(Direction.WEST).set_color(LightColor.RED)

        # Wait for green light duration
        time.sleep(context.get_green_duration() / 1000.0)

        # Transition North and South to Yellow
        context.get_light(Direction.NORTH).transition()
        context.get_light(Direction.SOUTH).transition()

        # Wait for yellow light duration
        time.sleep(context.get_yellow_duration() / 1000.0)

        # Transition North and South to Red
        context.get_light(Direction.NORTH).transition()
        context.get_light(Direction.SOUTH).transition()

        # Change the intersection's state to let East-West go
        context.set_state(EastWestGreenState())