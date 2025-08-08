package pubsubsystem;

import pubsubsystem.entities.Message;
import pubsubsystem.subscriber.AlertSubscriber;
import pubsubsystem.subscriber.NewsSubscriber;
import pubsubsystem.subscriber.Subscriber;

public class PubSubDemo {
    public static void main(String[] args) throws InterruptedException {
        PubSubService pubSubService = PubSubService.getInstance();

        // --- Create Subscribers ---
        Subscriber sportsFan1 = new NewsSubscriber("SportsFan1");
        Subscriber sportsFan2 = new NewsSubscriber("SportsFan2");
        Subscriber techie1 = new NewsSubscriber("Techie1");
        Subscriber allNewsReader = new NewsSubscriber("AllNewsReader");
        Subscriber systemAdmin = new AlertSubscriber("SystemAdmin");

        // --- Create Topics and Subscriptions ---
        final String SPORTS_TOPIC = "SPORTS";
        final String TECH_TOPIC = "TECH";
        final String WEATHER_TOPIC = "WEATHER";

        pubSubService.createTopic(SPORTS_TOPIC);
        pubSubService.createTopic(TECH_TOPIC);
        pubSubService.createTopic(WEATHER_TOPIC);

        pubSubService.subscribe(SPORTS_TOPIC, sportsFan1);
        pubSubService.subscribe(SPORTS_TOPIC, sportsFan2);
        pubSubService.subscribe(SPORTS_TOPIC, allNewsReader);
        pubSubService.subscribe(SPORTS_TOPIC, systemAdmin);

        pubSubService.subscribe(TECH_TOPIC, techie1);
        pubSubService.subscribe(TECH_TOPIC, allNewsReader);

        System.out.println("\n--- Publishing Messages ---");

        // --- Publish to SPORTS topic ---
        pubSubService.publish(SPORTS_TOPIC, new Message("Team A wins the championship!"));
        // Expected: SportsFan1, SportsFan2, AllNewsReader, SystemAdmin receive this.

        // --- Publish to TECH topic ---
        pubSubService.publish(TECH_TOPIC, new Message("New AI model released."));
        // Expected: Techie1, AllNewsReader receive this.

        // --- Publish to WEATHER topic (no subscribers) ---
        pubSubService.publish(WEATHER_TOPIC, new Message("Sunny with a high of 75°F."));
        // Expected: Message is dropped.

        // Allow some time for async messages to be processed
        Thread.sleep(500);

        System.out.println("\n--- Unsubscribing a user and re-publishing ---");

        // SportsFan2 gets tired of sports news
        pubSubService.unsubscribe(SPORTS_TOPIC, sportsFan2);

        // Publish another message to SPORTS
        pubSubService.publish(SPORTS_TOPIC, new Message("Major player traded to Team B."));
        // Expected: SportsFan1, AllNewsReader, SystemAdmin receive this. SportsFan2 does NOT.

        // Give messages time to be delivered
        Thread.sleep(500);

        // --- Shutdown the service ---
        pubSubService.shutdown();
    }
}
