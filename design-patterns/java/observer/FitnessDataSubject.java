public interface FitnessDataSubject {
    void registerObserver(FitnessDataObserver o);
    void removeObserver(FitnessDataObserver o);
    void notifyObservers();
}