from .base_handler import BaseHandler
from .request import Request

class ValidationHandler(BaseHandler):
    def handle(self, request: Request) -> None:
        if not request.payload:
            print("Validation failed: Empty payload")
            return
        print("Validation successful")
        self._forward(request) 