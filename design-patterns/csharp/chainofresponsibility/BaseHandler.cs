namespace ChainOfResponsibility
{
    public abstract class BaseHandler : IRequestHandler
    {
        protected IRequestHandler Next { get; private set; }

        public void SetNext(IRequestHandler next)
        {
            Next = next;
        }

        public abstract void Handle(Request request);

        protected void HandleNext(Request request)
        {
            if (Next != null)
            {
                Next.Handle(request);
            }
        }
    }
} 