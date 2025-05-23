from .base_handler import BaseHandler
from .request import Request

class BusinessLogicHandler(BaseHandler):
    def handle(self, request: Request) -> None:
        print(f"Processing business logic for request: {request.payload}")
        self._forward(request) 