from .request import Request
from .auth_handler import AuthHandler
from .authorization_handler import AuthorizationHandler
from .rate_limit_handler import RateLimitHandler
from .validation_handler import ValidationHandler
from .business_logic_handler import BusinessLogicHandler

def main():
    # Create the chain of handlers
    auth_handler = AuthHandler()
    authz_handler = AuthorizationHandler()
    rate_limit_handler = RateLimitHandler()
    validation_handler = ValidationHandler()
    business_logic_handler = BusinessLogicHandler()

    # Set up the chain
    auth_handler.set_next(authz_handler)
    authz_handler.set_next(rate_limit_handler)
    rate_limit_handler.set_next(validation_handler)
    validation_handler.set_next(business_logic_handler)

    # Create a valid request
    valid_request = Request(
        user="john",
        user_role="admin",
        request_count=50,
        payload="Valid request data"
    )

    # Create an invalid request
    invalid_request = Request(
        user="jane",
        user_role="user",
        request_count=150,
        payload=""
    )

    print("Processing valid request:")
    auth_handler.handle(valid_request)

    print("\nProcessing invalid request:")
    auth_handler.handle(invalid_request)

if __name__ == "__main__":
    main() 