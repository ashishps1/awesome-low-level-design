public class Request {
    public String user;
    public String userRole;
    public int requestCount;
    public String payload;

    public Request(String user, String role, int requestCount, String payload) {
        this.user = user;
        this.userRole = role;
        this.requestCount = requestCount;
        this.payload = payload;
    }
}