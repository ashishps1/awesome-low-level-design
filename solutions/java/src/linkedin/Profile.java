package linkedin;

import java.util.List;

public class Profile {
    private String profilePictureUrl;
    private String headline;
    private String summary;
    private List<Experience> experiences;
    private List<Education> educations;
    private List<Skill> skills;

    public void setSummary(String summary) {
        this.summary = summary;
    }

    public void setHeadline(String headline) {
        this.headline = headline;
    }

    public String getProfilePictureUrl() {
        return profilePictureUrl;
    }

    public String getHeadline() {
        return headline;
    }

    public String getSummary() {
        return summary;
    }

    public List<Experience> getExperiences() {
        return experiences;
    }

    public List<Education> getEducations() {
        return educations;
    }

    public List<Skill> getSkills() {
        return skills;
    }
}
