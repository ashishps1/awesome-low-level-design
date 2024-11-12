import java.util.HashMap;

public class RoyalGold implements Subscription {

    DataBase dataBase;

    public RoyalGold(DataBase dataBase) {
        this.dataBase = dataBase;
    }

    @Override
    public String subscriptionType() {
        return this.getClass().getName();
    }

    @Override
    public boolean addSubscription(Customer customer) {
        System.out.println("Customer Added to the RoyalGold List" );
        dataBase.addToDataBase(customer.customerId, "RoyalGold");
        return true;
    }

    @Override
    public boolean removeSubscription(Customer customer) {
        dataBase.removeFromDataBase(customer.customerId);
        System.out.println("Customer removed to the RoyalGold List" );
        return true;
    }

    @Override
    public boolean updateSubscription(Customer customer) {
        dataBase.updateDataBase(customer.customerId, "RoyalGold");
        System.out.println("Customer Updated to the RoyalGold List" );
        return true;
    }

}
