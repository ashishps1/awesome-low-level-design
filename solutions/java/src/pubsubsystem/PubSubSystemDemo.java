package pubsubsystem;

public class PubSubSystemDemo {
    public static void run() {
        // Create Broker
        Broker broker = new Broker();

        // Create Topics
        broker.createTopic("topic1");
        broker.createTopic("topic2");

        // Create publishers
        Publisher publisher1 = new Publisher("publisher1", broker);
        Publisher publisher2 = new Publisher("publisher2", broker);

        // Create subscribers
        Subscriber subscriber1 = new PrintSubscriber("PrintSubscriber1");
        Subscriber subscriber2 = new PrintSubscriber("PrintSubscriber2");
        Subscriber subscriber3 = new LoggingSubscriber("LoggingSubscriber3");

        // Subscribe to topics
        broker.subscribe("topic1", subscriber1);
        broker.subscribe("topic1", subscriber2);
        broker.subscribe("topic2", subscriber3);

        // Publish messages
        publisher1.publish("topic1", "Message1 for Topic1");
        publisher1.publish("topic1", "Message2 for Topic1");
        publisher1.publish("topic2", "Message1 for Topic2");

        // Unsubscribe from a topic
        broker.unsubscribe("topic1", subscriber2);

        // Publish more messages
        publisher1.publish("topic1", "Message3 for Topic1");
        publisher2.publish("topic2", "Message2 for Topic2");

        try {
            Thread.sleep(100); // Allow async delivery
            Dispatcher.shutdown();
        } catch (InterruptedException e) {
            System.out.println("Interrupted exception");
        }
    }
}
