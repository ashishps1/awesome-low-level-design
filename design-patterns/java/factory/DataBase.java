import java.util.HashMap;

public class DataBase {
    private HashMap<String, String> customerList;

    public DataBase() {
        customerList = new HashMap<>();
    }

    public void addToDataBase(String customerId, String subscriptionType) {
        if(!customerList.containsKey(customerId))
            customerList.put(customerId, subscriptionType);
        System.out.println("Successfull Added to the DB");
    }

    public void removeFromDataBase(String customerId) {
        if(customerList.containsKey(customerId))
            customerList.remove(customerId);
        System.out.println("Successfully removed from the DB");
    }

    public void updateDataBase(String customerId, String subscriptionType) {
        if(!customerList.containsKey(customerId))
            System.out.println("Record not found");
        else {
            customerList.put(customerId, subscriptionType);
            System.out.println("Sucessfully update the DB");
        }    
            
    }
    

}
