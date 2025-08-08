package movieticketbookingsystem.observer;

import movieticketbookingsystem.entities.Movie;
import movieticketbookingsystem.entities.User;

public class UserObserver implements MovieObserver {
    private final User user;

    public UserObserver(User user) {
        this.user = user;
    }

    @Override
    public void update(Movie movie) {
        System.out.printf("Notification for %s (%s): Movie '%s' is now available for booking!%n",
                user.getName(), user.getId(), movie.getTitle());
    }
}
