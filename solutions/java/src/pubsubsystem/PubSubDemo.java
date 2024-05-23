package pubsubsystem;

public class PubSubDemo {
    public static void run() {
        PubSubSystem pubSubSystem = new PubSubSystem();

        // Create topics
        pubSubSystem.createTopic("Topic1");
        pubSubSystem.createTopic("Topic2");

        // Create subscribers
        Subscriber subscriber1 = new ConcreteSubscriber("Subscriber1");
        Subscriber subscriber2 = new ConcreteSubscriber("Subscriber2");
        Subscriber subscriber3 = new ConcreteSubscriber("Subscriber3");

        // Subscribe to topics
        pubSubSystem.subscribe("Topic1", subscriber1);
        pubSubSystem.subscribe("Topic1", subscriber2);
        pubSubSystem.subscribe("Topic2", subscriber2);
        pubSubSystem.subscribe("Topic2", subscriber3);

        // Create publishers
        Publisher publisher1 = new Publisher(pubSubSystem.getTopics().get("Topic1"));
        Publisher publisher2 = new Publisher(pubSubSystem.getTopics().get("Topic2"));

        // Publish messages
        publisher1.publish(new Message("Message1 for Topic1"));
        publisher1.publish(new Message("Message2 for Topic1"));
        publisher2.publish(new Message("Message1 for Topic2"));

        // Unsubscribe from a topic
        pubSubSystem.unsubscribe("Topic1", subscriber2);

        // Publish more messages
        publisher1.publish(new Message("Message3 for Topic1"));
        publisher2.publish(new Message("Message2 for Topic2"));

        // Shutdown the system
        pubSubSystem.shutdown();
    }
}
