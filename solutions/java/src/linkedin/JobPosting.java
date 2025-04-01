package linkedin;

import java.sql.Timestamp;
import java.util.List;

public class JobPosting {
    private final String id;
    private final String title;
    private final String description;
    private final List<String> requirements;
    private final String location;
    private final Timestamp postDate;

    public JobPosting(String id, String title, String description, List<String> requirements, String location, Timestamp postDate) {
        this.id = id;
        this.title = title;
        this.description = description;
        this.requirements = requirements;
        this.location = location;
        this.postDate = postDate;
    }

    public String getId() {
        return id;
    }

    public String getTitle() {
        return title;
    }

    public String getDescription() {
        return description;
    }

    public List<String> getRequirements() {
        return requirements;
    }

    public String getLocation() {
        return location;
    }

    public Timestamp getPostDate() {
        return postDate;
    }
}
