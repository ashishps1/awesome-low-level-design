import java.util.HashMap;

public class Silver implements Subscription {

    DataBase dataBase;

    public Silver(DataBase dataBase) {
        this.dataBase = dataBase;
    }

    @Override
    public String subscriptionType() {
        return this.getClass().getName();
    }

    @Override
    public boolean addSubscription(Customer customer) {
        System.out.println("Customer Added to the Silver List" );
        dataBase.addToDataBase(customer.customerId, "Silver");
        return true;
    }

    @Override
    public boolean removeSubscription(Customer customer) {
        dataBase.removeFromDataBase(customer.customerId);
        System.out.println("Customer removed to the Silver List" );
        return true;
    }

    @Override
    public boolean updateSubscription(Customer customer) {
        dataBase.updateDataBase(customer.customerId, "Silver");
        System.out.println("Customer Updated to the Silver List" );
        return true;
    }

}
