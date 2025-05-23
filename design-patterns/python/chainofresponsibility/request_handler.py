from abc import ABC, abstractmethod
from .request import Request

class RequestHandler(ABC):
    @abstractmethod
    def set_next(self, next_handler: 'RequestHandler') -> None:
        pass

    @abstractmethod
    def handle(self, request: Request) -> None:
        pass 