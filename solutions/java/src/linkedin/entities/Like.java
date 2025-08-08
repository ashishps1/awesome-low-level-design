package linkedin.entities;

import java.time.LocalDateTime;

public class Like {
    private final Member member;
    private final LocalDateTime createdAt;

    public Like(Member member) {
        this.member = member;
        this.createdAt = LocalDateTime.now();
    }
    public Member getMember() { return member; }
}
