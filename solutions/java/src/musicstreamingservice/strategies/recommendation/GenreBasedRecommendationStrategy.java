package musicstreamingservice.strategies.recommendation;

import musicstreamingservice.entities.Song;

import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

public class GenreBasedRecommendationStrategy implements RecommendationStrategy {
    // In a real system, songs would have genres. We simulate this.
    @Override
    public List<Song> recommend(List<Song> allSongs) {
        System.out.println("Generating genre-based recommendations (simulated)...");
        List<Song> shuffled = new java.util.ArrayList<>(allSongs);
        Collections.shuffle(shuffled);
        return shuffled.stream().limit(5).collect(Collectors.toList());
    }
}
