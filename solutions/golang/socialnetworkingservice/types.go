package socialnetworkingservice

type NotificationType int

const (
    NotificationTypeFriendRequest NotificationType = iota
    NotificationTypeFriendRequestAccepted
    NotificationTypeLike
    NotificationTypeComment
    NotificationTypeMention
)

func (nt NotificationType) String() string {
    return [...]string{
        "FRIEND_REQUEST",
        "FRIEND_REQUEST_ACCEPTED",
        "LIKE",
        "COMMENT",
        "MENTION",
    }[nt]
}