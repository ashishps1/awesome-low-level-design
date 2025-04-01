namespace PubSubSystem
{
    public interface ISubscriber
    {
        void OnMessage(Message message);
    }
}