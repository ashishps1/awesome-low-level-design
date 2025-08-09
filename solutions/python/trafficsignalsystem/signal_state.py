from abc import ABC, abstractmethod
from light_color import LightColor
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from traffic_light import TrafficLight

class SignalState(ABC):
    @abstractmethod
    def handle(self, context: 'TrafficLight'):
        pass

class YellowState(SignalState):
    def handle(self, context: 'TrafficLight'):
        context.set_color(LightColor.YELLOW)
        # After being yellow, the next state is red.
        context.set_next_state(RedState())

class GreenState(SignalState):
    def handle(self, context: 'TrafficLight'):
        context.set_color(LightColor.GREEN)
        # After being green, the next state is yellow.
        context.set_next_state(YellowState())

class RedState(SignalState):
    def handle(self, context: 'TrafficLight'):
        context.set_color(LightColor.RED)
        # Red is a stable state, it transitions to green only when the intersection controller commands it.
        # So, the next state is self.
        context.set_next_state(RedState())