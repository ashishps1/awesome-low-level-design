public class AuthorizationHandler extends BaseHandler {
    @Override
    public void handle(Request request) {
        if (!"ADMIN".equals(request.userRole)) {
            System.out.println("AuthorizationHandler: ❌ Access denied.");
            return;
        }
        System.out.println("AuthorizationHandler: ✅ Authorized.");
        forward(request);
    }
}