package socialnetworkingservice

type NotificationType int

const (
	FriendRequest NotificationType = iota
	FriendRequestAccepted
	Like
	Mention
)
