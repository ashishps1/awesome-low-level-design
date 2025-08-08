package trafficsignalcontrolsystem.states.intersection;

import trafficsignalcontrolsystem.IntersectionController;

public interface IntersectionState {
    void handle(IntersectionController context) throws InterruptedException;
}
