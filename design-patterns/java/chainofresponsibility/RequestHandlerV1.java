public class RequestHandlerV1 {
    public void handle(Request request) {
        if (!authenticate(request)) {
            System.out.println("Request Rejected: Authentication failed.");
            return;
        }

        if (!authorize(request)) {
            System.out.println("Request Rejected: Authorization failed.");
            return;
        }

        if (!rateLimit(request)) {
            System.out.println("Request Rejected: Rate limit exceeded.");
            return;
        }

        if (!validate(request)) {
            System.out.println("Request Rejected: Invalid payload.");
            return;
        }

        System.out.println("Request passed all checks. Executing business logic...");
        // Proceed to business logic
    }

    private boolean authenticate(Request req) {
        return req.user != null;
    }

    private boolean authorize(Request req) {
        return "ADMIN".equals(req.userRole);
    }

    private boolean rateLimit(Request req) {
        return req.requestCount < 100;
    }

    private boolean validate(Request req) {
        return req.payload != null && !req.payload.isEmpty();
    }
}