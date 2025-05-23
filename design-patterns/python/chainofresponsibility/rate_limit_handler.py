from .base_handler import BaseHandler
from .request import Request

class RateLimitHandler(BaseHandler):
    def handle(self, request: Request) -> None:
        if request.request_count > 100:
            print(f"Rate limit exceeded for user: {request.user}")
            return
        print(f"Rate limit check passed for user: {request.user}")
        self._forward(request) 