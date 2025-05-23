namespace Mediator
{
    public abstract class UIComponent
    {
        protected readonly IUIMediator mediator;

        public UIComponent(IUIMediator mediator)
        {
            this.mediator = mediator;
        }

        public void NotifyMediator()
        {
            mediator.ComponentChanged(this);
        }
    }
} 