import java.util.Map;
import java.util.HashMap;

public class CharacterFlyweightFactory {
    private static final Map<String, CharacterFlyweight> flyweightCache = new HashMap<>();

    public static CharacterFlyweight getFlyweight(char symbol, String fontFamily, int fontSize, String color) {
        String key = String.format("%s-%d-%s", symbol, fontSize, color);
        if (!flyweightCache.containsKey(key)) {
            flyweightCache.put(key, new CharacterGlyph(symbol, fontFamily, fontSize, color));
        }
        return flyweightCache.get(key);
    }

    public int getFlyweightCount() {
        return flyweightCache.size();
    }
}
