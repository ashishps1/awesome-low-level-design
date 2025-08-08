package stackoverflow.strategy;

import stackoverflow.entities.Question;

import java.util.List;

public interface SearchStrategy {
    List<Question> filter(List<Question> questions);
}
