package musicstreamingservice;

import java.util.concurrent.ExecutorService;

public class MusicStreamingService {
    private final MusicLibrary musicLibrary;
    private final UserManager userManager;
    private final MusicRecommender musicRecommender;

    public MusicStreamingService() {
        musicLibrary = MusicLibrary.getInstance();
        userManager = UserManager.getInstance();
        musicRecommender = MusicRecommender.getInstance();

    }

    public void start() {

    }
}
