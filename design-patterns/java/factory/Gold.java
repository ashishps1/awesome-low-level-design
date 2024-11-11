import java.util.HashMap;

public class Gold implements Subscription {

    DataBase dataBase;

    public Gold(DataBase dataBase) {
        this.dataBase = dataBase;
    }

    @Override
    public String subscriptionType() {
        return this.getClass().getName();
    }

    @Override
    public boolean addSubscription(Customer customer) {
        System.out.println("Customer"+ customer.customerId+ "Added to the Gold List" );
        dataBase.addToDataBase(customer.customerId, "Gold");
        return true;
    }

    @Override
    public boolean removeSubscription(Customer customer) {
        dataBase.removeFromDataBase(customer.customerId);
        System.out.println("Customer "+ customer.customerId +" removed to the Gold List" );
        return true;
    }

    @Override
    public boolean updateSubscription(Customer customer) {
        dataBase.updateDataBase(customer.customerId, "Gold");
        System.out.println("Customer "+ customer.customerId+" Updated to the Gold List" );
        return true;
    }

}
