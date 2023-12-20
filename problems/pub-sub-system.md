# Designing a Pub-Sub System in Java

This blog explores the design and implementation of a basic Publish-Subscribe (Pub-Sub) system using Java, following object-oriented design principles.

The Pub-Sub model is a widely used pattern in messaging systems, allowing for scalable and decoupled communication. This guide outlines the design and implementation of such a system.

## Understanding the Requirements
The system will enable:
- Publishers to send messages to topics.
- Subscribers to receive messages from topics they are subscribed to.
- Scalability and decoupling between publishers and subscribers.

## Core Use Cases
- **Subscribing to Topics**: Users can subscribe to topics of interest.
- **Publishing Messages**: Publishers can send messages to topics.
- **Receiving Messages**: Subscribers receive messages from their subscribed topics.

## UML and Class Diagrams
- **Publisher Class**: Responsible for publishing messages.
- **Subscriber Interface**: Interface for subscribers to receive messages.
- **Topic Class**: Represents a topic in the system.
- **PubSubService Class**: Manages the publication and subscription logic.

## Java Implementation
```java
public class Topic {
    private String name;

    public Topic(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}
```
```java
public class Message {
    private String content;
    private Topic topic;

    public Message(String content, Topic topic) {
        this.content = content;
        this.topic = topic;
    }

    public String getContent() {
        return content;
    }

    public Topic getTopic() {
        return topic;
    }
}
```
```java
public interface Subscriber {
    void receive(Message message);
}

public class Publisher {
    public void publish(Message message, PubSubService service) {
        service.addMessageToQueue(message);
    }
}
```
```java
import java.util.*;

public class PubSubService {
    private Queue<Message> messageQueue = new LinkedList<>();
    private Map<String, List<Subscriber>> subscribersTopicMap = new HashMap<>();

    public void addMessageToQueue(Message message) {
        messageQueue.add(message);
    }

    public void addSubscriber(String topicName, Subscriber subscriber) {
        if (!subscribersTopicMap.containsKey(topicName)) {
            subscribersTopicMap.put(topicName, new ArrayList<>());
        }
        subscribersTopicMap.get(topicName).add(subscriber);
    }

    public void removeSubscriber(String topicName, Subscriber subscriber) {
        if (subscribersTopicMap.containsKey(topicName)) {
            subscribersTopicMap.get(topicName).remove(subscriber);
        }
    }

    public void broadcast() {
        while (!messageQueue.isEmpty()) {
            Message message = messageQueue.poll();
            String topicName = message.getTopic().getName();
            List<Subscriber> subscribersOfTopic = subscribersTopicMap.getOrDefault(topicName, new ArrayList<>());
            for (Subscriber subscriber : subscribersOfTopic) {
                subscriber.receive(message);
            }
        }
    }
}
```

