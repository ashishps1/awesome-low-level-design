from abc import ABC
from .ui_mediator import UIMediator

class UIComponent(ABC):
    def __init__(self, mediator: UIMediator):
        self.mediator = mediator

    def notify_mediator(self) -> None:
        self.mediator.component_changed(self) 