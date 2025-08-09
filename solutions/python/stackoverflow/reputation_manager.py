from post_observer import PostObserver
from event import Event
from enums import EventType

class ReputationManager(PostObserver):
    QUESTION_UPVOTE_REP = 5
    ANSWER_UPVOTE_REP = 10
    ACCEPTED_ANSWER_REP = 15
    DOWNVOTE_REP_PENALTY = -1  # Penalty for the voter
    POST_DOWNVOTED_REP_PENALTY = -2  # Penalty for the post author

    def on_post_event(self, event: Event):
        post_author = event.get_target_post().get_author()
        
        if event.get_type() == EventType.UPVOTE_QUESTION:
            post_author.update_reputation(self.QUESTION_UPVOTE_REP)
        elif event.get_type() == EventType.DOWNVOTE_QUESTION:
            post_author.update_reputation(self.DOWNVOTE_REP_PENALTY)
            event.get_actor().update_reputation(self.POST_DOWNVOTED_REP_PENALTY)  # voter penalty
        elif event.get_type() == EventType.UPVOTE_ANSWER:
            post_author.update_reputation(self.ANSWER_UPVOTE_REP)
        elif event.get_type() == EventType.DOWNVOTE_ANSWER:
            post_author.update_reputation(self.DOWNVOTE_REP_PENALTY)
            event.get_actor().update_reputation(self.POST_DOWNVOTED_REP_PENALTY)
        elif event.get_type() == EventType.ACCEPT_ANSWER:
            post_author.update_reputation(self.ACCEPTED_ANSWER_REP)