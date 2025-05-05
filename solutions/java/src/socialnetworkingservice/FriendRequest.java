package socialnetworkingservice;

public class FriendRequest {
    private final User from;
    private final User to;
    private FriendRequestStatus status = FriendRequestStatus.PENDING;

    public FriendRequest(User from, User to) {
        this.from = from;
        this.to = to;
    }

    public void accept() {
        this.status = FriendRequestStatus.ACCEPTED;
    }

    public void reject() {
        this.status = FriendRequestStatus.REJECTED;
    }

    public User getFrom() {
        return from;
    }

    public User getTo() {
        return to;
    }

    public FriendRequestStatus getStatus() {
        return status;
    }
}
