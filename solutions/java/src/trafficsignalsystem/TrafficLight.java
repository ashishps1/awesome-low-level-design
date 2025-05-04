package trafficsignalsystem;

public class TrafficLight {
    private SignalState currentSignalState;

    public TrafficLight() {
        this.currentSignalState = SignalState.RED;
    }

    public synchronized void changeSignal(SignalState newSignalState) {
        currentSignalState = newSignalState;
        notifyObservers();
    }

    public SignalState getCurrentSignal() {
        return currentSignalState;
    }

    private void notifyObservers() {
        // Notify observers (e.g., roads) about the signal change
        // ...
    }
}
