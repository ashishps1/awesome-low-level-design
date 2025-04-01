
public class Customer {
    public String customerId;
    public Subscription subscription = null;

    public Customer(String customerId) {
        this.customerId = customerId;
    }

    public void SubscribePlan(Subscription subscription) {
        this.subscription = subscription;
        this.subscription.addSubscription(this);
    }

    public void unSubscribePlan() {
        subscription.removeSubscription(this);
    }
    
    public void updateSubcribePlan(Subscription newSubscription) {
        subscription.removeSubscription(this);
        this.subscription = newSubscription;
        this.subscription.addSubscription(this);
    }

}
