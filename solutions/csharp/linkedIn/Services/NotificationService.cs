class NotificationService
{
    public void SendNotification(Member member, Notification notification)
    {
        member.Update(notification);
    }
}