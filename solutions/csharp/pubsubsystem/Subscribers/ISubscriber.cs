interface ISubscriber
{
    string GetId();
    void OnMessage(Message message);
}