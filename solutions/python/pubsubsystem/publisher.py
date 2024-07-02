class Publisher:
    def __init__(self, topic):
        self.topic = topic

    def publish(self, message):
        self.topic.publish(message)