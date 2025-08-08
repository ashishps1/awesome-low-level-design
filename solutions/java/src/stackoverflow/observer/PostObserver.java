package stackoverflow.observer;

import stackoverflow.entities.Event;

public interface PostObserver {
    void onPostEvent(Event event);
}
