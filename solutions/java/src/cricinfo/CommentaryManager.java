package cricinfo;

import cricinfo.enums.ExtraType;
import cricinfo.enums.WicketType;
import cricinfo.entity.Ball;

import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.concurrent.ConcurrentHashMap;

public class CommentaryManager {
    private static volatile CommentaryManager instance;
    private final Random random = new Random();

    private final Map<String, List<String>> commentaryTemplates = new ConcurrentHashMap<>();

    private CommentaryManager() {
        initializeTemplates();
    }

    public static CommentaryManager getInstance() {
        if (instance == null) {
            synchronized (CommentaryManager.class) {
                if (instance == null) {
                    instance = new CommentaryManager();
                }
            }
        }
        return instance;
    }

    private void initializeTemplates() {
        // Templates for runs
        commentaryTemplates.put("RUNS_0", List.of(
                "%s defends solidly.",
                "No run, good fielding by the cover fielder.",
                "A dot ball to end the over.",
                "Pushed to mid-on, but no run."
        ));
        commentaryTemplates.put("RUNS_1", List.of(
                "Tucked away to the leg side for a single.",
                "Quick single taken by %s.",
                "Pushed to long-on for one."
        ));
        commentaryTemplates.put("RUNS_2", List.of(
                "Two runs taken!",
                "Quick double taken by %s.",
                "Pushed to mid-on for two."
        ));
        commentaryTemplates.put("RUNS_4", List.of(
                "FOUR! %s smashes it through the covers!",
                "Beautiful shot! That's a boundary.",
                "Finds the gap perfectly. Four runs."
        ));
        commentaryTemplates.put("RUNS_6", List.of(
                "SIX! That's out of the park!",
                "%s sends it sailing over the ropes!",
                "Massive hit! It's a maximum."
        ));

        // Templates for wickets
        commentaryTemplates.put("WICKET_" + WicketType.BOWLED, List.of(
                "BOWLED HIM! %s misses completely and the stumps are shattered!",
                "Cleaned up! A perfect yorker from %s."
        ));
        commentaryTemplates.put("WICKET_" + WicketType.CAUGHT, List.of(
                "CAUGHT! %s skies it and the fielder takes a comfortable catch.",
                "Out! A brilliant catch in the deep by %s."
        ));
        commentaryTemplates.put("WICKET_" + WicketType.LBW, List.of(
                "LBW! That one kept low and struck %s right in front.",
                "%s completely misjudged the line and pays the price."
        ));

        commentaryTemplates.put("WICKET_" + WicketType.STUMPED, List.of(
                "STUMPED! %s misses it, and the keeper does the rest!",
                "Gone! Lightning-fast work by the keeper to stump %s."
        ));

        // Templates for extras
        commentaryTemplates.put("EXTRA_" + ExtraType.WIDE, List.of(
                "That's a wide. The umpire signals an extra run.",
                "Too far down the leg side, that'll be a wide."
        ));
        commentaryTemplates.put("EXTRA_" + ExtraType.NO_BALL, List.of(
                "No ball! %s has overstepped. It's a free hit.",
                "It's a no-ball for overstepping."
        ));
    }

    public String generateCommentary(Ball ball) {
        String key = getEventKey(ball);
        List<String> templates = commentaryTemplates.getOrDefault(key, List.of("Just a standard delivery."));

        String template = templates.get(random.nextInt(templates.size()));

        // Format the commentary with player names
        String batsmanName = ball.getFacedBy() != null ? ball.getFacedBy().getName() : "";
        String bowlerName = ball.getBowledBy() != null ? ball.getBowledBy().getName() : "";

        // This handles cases where a template might have more or fewer placeholders
        // and avoids exceptions.
        return String.format(template.replace("%s", "%1$s"), batsmanName, bowlerName);
    }

    private String getEventKey(Ball ball) {
        if (ball.isWicket()) {
            return "WICKET_" + ball.getWicket().getWicketType().toString();
        }
        if (ball.getExtraType() != null) {
            return "EXTRA_" + ball.getExtraType().toString();
        }
        if (ball.getRunsScored() >= 0 && ball.getRunsScored() <= 6) {
            switch(ball.getRunsScored()) {
                case 0: return "RUNS_0";
                case 1: return "RUNS_1";
                case 2: return "RUNS_2";
                case 3: return "RUNS_3";
                case 4: return "RUNS_4";
                case 6: return "RUNS_6";
            }
        }
        return "DEFAULT"; // Fallback key
    }
}
