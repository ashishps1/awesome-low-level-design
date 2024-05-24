package movieticketbookingsystem;

import java.util.List;

public class Theater {
    private final String id;
    private final String name;
    private final String location;
    private final List<Show> shows;

    public Theater(String id, String name, String location, List<Show> shows) {
        this.id = id;
        this.name = name;
        this.location = location;
        this.shows = shows;
    }
}
