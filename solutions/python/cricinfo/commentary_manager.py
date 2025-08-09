import random
from enums import WicketType, ExtraType

class CommentaryManager:
    _instance = None

    def __init__(self):
        self.random = random.Random()
        self.commentary_templates = {}
        self.initialize_templates()

    @classmethod
    def get_instance(cls):
        if cls._instance is None:
            cls._instance = CommentaryManager()
        return cls._instance

    def initialize_templates(self):
        self.commentary_templates["RUNS_0"] = [
            "%s defends solidly.",
            "No run, good fielding by the cover fielder.",
            "A dot ball to end the over.",
            "Pushed to mid-on, but no run."
        ]
        self.commentary_templates["RUNS_1"] = [
            "Tucked away to the leg side for a single.",
            "Quick single taken by %s.",
            "Pushed to long-on for one."
        ]
        self.commentary_templates["RUNS_2"] = [
            "Two runs taken!",
            "Quick double taken by %s.",
            "Pushed to mid-on for two."
        ]
        self.commentary_templates["RUNS_4"] = [
            "FOUR! %s smashes it through the covers!",
            "Beautiful shot! That's a boundary.",
            "Finds the gap perfectly. Four runs."
        ]
        self.commentary_templates["RUNS_6"] = [
            "SIX! That's out of the park!",
            "%s sends it sailing over the ropes!",
            "Massive hit! It's a maximum."
        ]

        self.commentary_templates[f"WICKET_{WicketType.BOWLED.value}"] = [
            "BOWLED HIM! %s misses completely and the stumps are shattered!",
            "Cleaned up! A perfect yorker from %s."
        ]
        self.commentary_templates[f"WICKET_{WicketType.CAUGHT.value}"] = [
            "CAUGHT! %s skies it and the fielder takes a comfortable catch.",
            "Out! A brilliant catch in the deep by %s."
        ]
        self.commentary_templates[f"WICKET_{WicketType.LBW.value}"] = [
            "LBW! That one kept low and struck %s right in front.",
            "%s completely misjudged the line and pays the price."
        ]
        self.commentary_templates[f"WICKET_{WicketType.STUMPED.value}"] = [
            "STUMPED! %s misses it, and the keeper does the rest!",
            "Gone! Lightning-fast work by the keeper to stump %s."
        ]

        self.commentary_templates[f"EXTRA_{ExtraType.WIDE.value}"] = [
            "That's a wide. The umpire signals an extra run.",
            "Too far down the leg side, that'll be a wide."
        ]
        self.commentary_templates[f"EXTRA_{ExtraType.NO_BALL.value}"] = [
            "No ball! %s has overstepped. It's a free hit.",
            "It's a no-ball for overstepping."
        ]

    def generate_commentary(self, ball):
        key = self.get_event_key(ball)
        templates = self.commentary_templates.get(key, ["Just a standard delivery."])
        
        template = self.random.choice(templates)
        
        batsman_name = ball.get_faced_by().get_name() if ball.get_faced_by() else ""
        bowler_name = ball.get_bowled_by().get_name() if ball.get_bowled_by() else ""
        
        try:
            return template % batsman_name
        except:
            return template.replace("%s", batsman_name)

    def get_event_key(self, ball):
        if ball.is_wicket():
            return f"WICKET_{ball.get_wicket().get_wicket_type().value}"
        if ball.get_extra_type():
            return f"EXTRA_{ball.get_extra_type().value}"
        if 0 <= ball.get_runs_scored() <= 6:
            return f"RUNS_{ball.get_runs_scored()}"
        return "DEFAULT"