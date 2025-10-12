package stackoverflow.strategy;

import stackoverflow.entities.Question;

import java.util.List;
import java.util.stream.Collectors;

public class KeywordSearchStrategy implements SearchStrategy {
    private final String keyword;

    public KeywordSearchStrategy(String keyword) {
        this.keyword = keyword.toLowerCase();
    }

    @Override
    public List<Question> filter(List<Question> questions) {
        return questions.stream()
                .filter(q -> q.getTitle().toLowerCase().contains(keyword) ||
                        q.getBody().toLowerCase().contains(keyword))
                .collect(Collectors.toList());
    }
}
