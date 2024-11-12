import java.util.HashMap;

public class Platinum implements Subscription {

    DataBase dataBase;

    public Platinum(DataBase dataBase) {
        this.dataBase = dataBase;
    }

    @Override
    public String subscriptionType() {
        return this.getClass().getName();
    }

    @Override
    public boolean addSubscription(Customer customer) {
        System.out.println("Customer Added to the Platinum List" );
        dataBase.addToDataBase(customer.customerId, "Platinum");
        return true;
    }

    @Override
    public boolean removeSubscription(Customer customer) {
        dataBase.removeFromDataBase(customer.customerId);
        System.out.println("Customer removed to the Platinum List" );
        return true;
    }

    @Override
    public boolean updateSubscription(Customer customer) {
        dataBase.updateDataBase(customer.customerId, "Platinum");
        System.out.println("Customer Updated to the Platinum List" );
        return true;
    }

}
