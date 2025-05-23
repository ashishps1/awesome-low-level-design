namespace Observer
{
    public interface IFitnessDataSubject
    {
        void RegisterObserver(IFitnessDataObserver observer);
        void RemoveObserver(IFitnessDataObserver observer);
        void NotifyObservers();
    }
} 