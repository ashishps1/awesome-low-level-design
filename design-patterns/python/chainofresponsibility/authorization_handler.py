from .base_handler import BaseHandler
from .request import Request

class AuthorizationHandler(BaseHandler):
    def handle(self, request: Request) -> None:
        if request.user_role != "admin":
            print(f"Authorization failed: User {request.user} is not authorized")
            return
        print(f"Authorization successful for user: {request.user}")
        self._forward(request) 