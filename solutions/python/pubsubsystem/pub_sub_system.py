from concurrent.futures import ThreadPoolExecutor
from topic import Topic

class PubSubSystem:
    def __init__(self):
        self.topics = {}
        self.executor_service = ThreadPoolExecutor(max_workers=10)

    def create_topic(self, topic_name):
        self.topics.setdefault(topic_name, Topic(topic_name))

    def subscribe(self, topic_name, subscriber):
        topic = self.topics.get(topic_name)
        if topic:
            topic.add_subscriber(subscriber)

    def unsubscribe(self, topic_name, subscriber):
        topic = self.topics.get(topic_name)
        if topic:
            topic.remove_subscriber(subscriber)

    def publish(self, topic_name, message):
        topic = self.topics.get(topic_name)
        if topic:
            self.executor_service.submit(topic.publish, message)

    def shutdown(self):
        self.executor_service.shutdown()

    def get_topics(self):
        return self.topics