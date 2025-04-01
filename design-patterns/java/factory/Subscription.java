
public interface Subscription {
     public String subscriptionType();
     public boolean addSubscription(Customer customer);
     public boolean removeSubscription(Customer customer);
     public boolean updateSubscription(Customer customer);

}
