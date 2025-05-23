from .base_handler import BaseHandler
from .request import Request

class AuthHandler(BaseHandler):
    def handle(self, request: Request) -> None:
        if not request.user:
            print("Authentication failed: No user provided")
            return
        print(f"Authentication successful for user: {request.user}")
        self._forward(request) 