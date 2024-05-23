package pubsubsystem;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class PubSubSystem {
    private final Map<String, Topic> topics = new ConcurrentHashMap<>();
    private final ExecutorService executorService = Executors.newFixedThreadPool(10);

    public void createTopic(String topicName) {
        topics.putIfAbsent(topicName, new Topic(topicName));
    }

    public void subscribe(String topicName, Subscriber subscriber) {
        Topic topic = topics.get(topicName);
        if (topic != null) {
            topic.addSubscriber(subscriber);
        }
    }

    public void unsubscribe(String topicName, Subscriber subscriber) {
        Topic topic = topics.get(topicName);
        if (topic != null) {
            topic.removeSubscriber(subscriber);
        }
    }

    public void publish(String topicName, Message message) {
        Topic topic = topics.get(topicName);
        if (topic != null) {
            executorService.submit(() -> topic.publish(message));
        }
    }

    public void shutdown() {
        executorService.shutdown();
    }

    public Map<String, Topic> getTopics() {
        return topics;
    }
}
