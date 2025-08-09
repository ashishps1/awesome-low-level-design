from pub_sub_service import PubSubService
from subscriber import NewsSubscriber, AlertSubscriber
from message import Message
import time

class PubSubDemo:
    @staticmethod  
    def main():
        pub_sub_service = PubSubService.get_instance()

        # --- Create Subscribers ---
        sports_fan1 = NewsSubscriber("SportsFan1")
        sports_fan2 = NewsSubscriber("SportsFan2")
        techie1 = NewsSubscriber("Techie1")
        all_news_reader = NewsSubscriber("AllNewsReader")
        system_admin = AlertSubscriber("SystemAdmin")

        # --- Create Topics and Subscriptions ---
        SPORTS_TOPIC = "SPORTS"
        TECH_TOPIC = "TECH"
        WEATHER_TOPIC = "WEATHER"

        pub_sub_service.create_topic(SPORTS_TOPIC)
        pub_sub_service.create_topic(TECH_TOPIC)
        pub_sub_service.create_topic(WEATHER_TOPIC)

        pub_sub_service.subscribe(SPORTS_TOPIC, sports_fan1)
        pub_sub_service.subscribe(SPORTS_TOPIC, sports_fan2)
        pub_sub_service.subscribe(SPORTS_TOPIC, all_news_reader)
        pub_sub_service.subscribe(SPORTS_TOPIC, system_admin)

        pub_sub_service.subscribe(TECH_TOPIC, techie1)
        pub_sub_service.subscribe(TECH_TOPIC, all_news_reader)

        print("\n--- Publishing Messages ---")

        # --- Publish to SPORTS topic ---
        pub_sub_service.publish(SPORTS_TOPIC, Message("Team A wins the championship!"))
        # Expected: SportsFan1, SportsFan2, AllNewsReader, SystemAdmin receive this.

        # --- Publish to TECH topic ---
        pub_sub_service.publish(TECH_TOPIC, Message("New AI model released."))
        # Expected: Techie1, AllNewsReader receive this.

        # --- Publish to WEATHER topic (no subscribers) ---
        pub_sub_service.publish(WEATHER_TOPIC, Message("Sunny with a high of 75°F."))
        # Expected: Message is dropped.

        # Allow some time for async messages to be processed
        time.sleep(0.5)

        print("\n--- Unsubscribing a user and re-publishing ---")

        # SportsFan2 gets tired of sports news
        pub_sub_service.unsubscribe(SPORTS_TOPIC, sports_fan2)

        # Publish another message to SPORTS
        pub_sub_service.publish(SPORTS_TOPIC, Message("Major player traded to Team B."))
        # Expected: SportsFan1, AllNewsReader, SystemAdmin receive this. SportsFan2 does NOT.

        # Give messages time to be delivered
        time.sleep(0.5)

        # --- Shutdown the service ---
        pub_sub_service.shutdown()

if __name__ == "__main__":
    PubSubDemo.main()