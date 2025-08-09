import threading
import uuid
from abc import ABC
from datetime import datetime
from typing import Dict, List, Optional, Set, TYPE_CHECKING

from enums import VoteType, EventType
from user import User
from tag import Tag

if TYPE_CHECKING:
    from event import Event
    from post_observer import PostObserver


class Content(ABC):
    def __init__(self, content_id: str, body: str, author: User):
        self.id = content_id
        self.body = body
        self.author = author
        self.creation_time = datetime.now()

    def get_id(self) -> str:
        return self.id

    def get_body(self) -> str:
        return self.body

    def get_author(self) -> User:
        return self.author


class Post(Content):
    def __init__(self, post_id: str, body: str, author: User):
        super().__init__(post_id, body, author)
        self.vote_count = 0
        self.voters: Dict[str, VoteType] = {}
        self.comments: List['Comment'] = []
        self.observers: List['PostObserver'] = []
        self._lock = threading.Lock()

    def add_observer(self, observer: 'PostObserver'):
        self.observers.append(observer)

    def notify_observers(self, event: 'Event'):
        for observer in self.observers:
            observer.on_post_event(event)

    def vote(self, user: User, vote_type: VoteType):
        with self._lock:
            user_id = user.get_id()
            if self.voters.get(user_id) == vote_type:
                return  # Already voted

            score_change = 0
            if user_id in self.voters:  # User is changing their vote
                score_change = 2 if vote_type == VoteType.UPVOTE else -2
            else:  # New vote
                score_change = 1 if vote_type == VoteType.UPVOTE else -1

            self.voters[user_id] = vote_type
            self.vote_count += score_change

            # Import here to avoid circular dependency
            from event import Event
            
            if isinstance(self, Question):
                event_type = EventType.UPVOTE_QUESTION if vote_type == VoteType.UPVOTE else EventType.DOWNVOTE_QUESTION
            else:
                event_type = EventType.UPVOTE_ANSWER if vote_type == VoteType.UPVOTE else EventType.DOWNVOTE_ANSWER

            self.notify_observers(Event(event_type, user, self))

    def get_vote_count(self) -> int:
        return self.vote_count

    def add_comment(self, comment: 'Comment'):
        self.comments.append(comment)

    def get_comments(self) -> List['Comment']:
        return self.comments


class Question(Post):
    def __init__(self, title: str, body: str, author: User, tags: Set[Tag]):
        super().__init__(str(uuid.uuid4()), body, author)
        self.title = title
        self.tags = tags
        self.answers: List['Answer'] = []
        self.accepted_answer: Optional['Answer'] = None

    def add_answer(self, answer: 'Answer'):
        self.answers.append(answer)

    def accept_answer(self, answer: 'Answer'):
        with self._lock:
            # Only the question author can accept an answer, and it shouldn't be their own answer
            if (self.author.get_id() != answer.get_author().get_id() and 
                self.accepted_answer is None):
                self.accepted_answer = answer
                answer.set_accepted(True)
                
                # Import here to avoid circular dependency
                from event import Event
                self.notify_observers(Event(EventType.ACCEPT_ANSWER, answer.get_author(), answer))

    def get_title(self) -> str:
        return self.title

    def get_tags(self) -> Set[Tag]:
        return self.tags

    def get_answers(self) -> List['Answer']:
        return self.answers

    def get_accepted_answer(self) -> Optional['Answer']:
        return self.accepted_answer


class Answer(Post):
    def __init__(self, body: str, author: User):
        super().__init__(str(uuid.uuid4()), body, author)
        self.is_accepted = False

    def set_accepted(self, accepted: bool):
        self.is_accepted = accepted

    def is_accepted_answer(self) -> bool:
        return self.is_accepted


class Comment(Content):
    def __init__(self, body: str, author: User):
        super().__init__(str(uuid.uuid4()), body, author)