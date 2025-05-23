from .email_notification_creator import EmailNotificationCreator
from .sms_notification_creator import SMSNotificationCreator
from .push_notification_creator import PushNotificationCreator
from .simple_notification_factory import SimpleNotificationFactory
from .notification_service_naive import NotificationServiceNaive


def factory_method_demo():
    """Demonstrate Factory Method Pattern"""
    print("=== Factory Method Pattern Demo ===")
    
    # Send Email
    creator = EmailNotificationCreator()
    creator.send("Welcome to our platform!")
    
    # Send SMS
    creator = SMSNotificationCreator()
    creator.send("Your OTP is 123456")
    
    # Send Push Notification
    creator = PushNotificationCreator()
    creator.send("You have a new follower!")


def simple_factory_demo():
    """Demonstrate Simple Factory Pattern"""
    print("\n=== Simple Factory Pattern Demo ===")
    
    # Using simple factory
    factory = SimpleNotificationFactory()
    
    email_notification = factory.create_notification("EMAIL")
    email_notification.send("Welcome via Simple Factory!")
    
    sms_notification = factory.create_notification("SMS")
    sms_notification.send("OTP via Simple Factory: 789012")
    
    push_notification = factory.create_notification("PUSH")
    push_notification.send("Push via Simple Factory!")


def naive_implementation_demo():
    """Demonstrate naive implementation (what to avoid)"""
    print("\n=== Naive Implementation Demo ===")
    
    service = NotificationServiceNaive()
    service.send_notification("EMAIL", "Email via naive service")
    service.send_notification("SMS", "SMS via naive service")
    service.send_notification("PUSH", "Push via naive service")


if __name__ == "__main__":
    factory_method_demo()
    simple_factory_demo()
    naive_implementation_demo()