package linkedin.entities;

import linkedin.enums.ConnectionStatus;

import java.time.LocalDateTime;

public class Connection {
    private final Member fromMember;
    private final Member toMember;
    private ConnectionStatus status;
    private final LocalDateTime requestedAt;
    private LocalDateTime acceptedAt;

    public Connection(Member fromMember, Member toMember) {
        this.fromMember = fromMember;
        this.toMember = toMember;
        this.status = ConnectionStatus.PENDING;
        this.requestedAt = LocalDateTime.now();
    }

    public Member getFromMember() { return fromMember; }
    public Member getToMember() { return toMember; }
    public ConnectionStatus getStatus() { return status; }

    public void setStatus(ConnectionStatus status) {
        this.status = status;
        if (status == ConnectionStatus.ACCEPTED) {
            this.acceptedAt = LocalDateTime.now();
        }
    }
}
