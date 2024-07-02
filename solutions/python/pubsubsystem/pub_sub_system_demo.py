from concrete_subscriber import ConcreteSubscriber
from message import Message
from publisher import Publisher
from pub_sub_system import PubSubSystem

class PubSubSystemDemo:
    @staticmethod
    def run():
        pub_sub_system = PubSubSystem()

        # Create topics
        pub_sub_system.create_topic("Topic1")
        pub_sub_system.create_topic("Topic2")

        # Create subscribers
        subscriber1 = ConcreteSubscriber("Subscriber1")
        subscriber2 = ConcreteSubscriber("Subscriber2")
        subscriber3 = ConcreteSubscriber("Subscriber3")

        # Subscribe to topics
        pub_sub_system.subscribe("Topic1", subscriber1)
        pub_sub_system.subscribe("Topic1", subscriber2)
        pub_sub_system.subscribe("Topic2", subscriber2)
        pub_sub_system.subscribe("Topic2", subscriber3)

        # Create publishers
        publisher1 = Publisher(pub_sub_system.get_topics().get("Topic1"))
        publisher2 = Publisher(pub_sub_system.get_topics().get("Topic2"))

        # Publish messages
        publisher1.publish(Message("Message1 for Topic1"))
        publisher1.publish(Message("Message2 for Topic1"))
        publisher2.publish(Message("Message1 for Topic2"))

        # Unsubscribe from a topic
        pub_sub_system.unsubscribe("Topic1", subscriber2)

        # Publish more messages
        publisher1.publish(Message("Message3 for Topic1"))
        publisher2.publish(Message("Message2 for Topic2"))

        # Shutdown the system
        pub_sub_system.shutdown()

if __name__ == "__main__":
    PubSubSystemDemo.run()