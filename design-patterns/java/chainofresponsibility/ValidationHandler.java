public class ValidationHandler extends BaseHandler {
    @Override
    public void handle(Request request) {
        if (request.payload == null || request.payload.trim().isEmpty()) {
            System.out.println("ValidationHandler: ❌ Invalid payload.");
            return;
        }
        System.out.println("ValidationHandler: ✅ Payload valid.");
        forward(request);
    }
}