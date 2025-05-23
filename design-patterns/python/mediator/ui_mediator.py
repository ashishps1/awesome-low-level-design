from abc import ABC, abstractmethod
from .ui_component import UIComponent

class UIMediator(ABC):
    @abstractmethod
    def component_changed(self, component: UIComponent) -> None:
        pass 