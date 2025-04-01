public class Application {
    static public DataBase dataBase;

    public static void main(String[] arg) {
        dataBase = new DataBase();
        Customer customer1 = new Customer("1");
        Customer customer2 = new Customer("2");
        Customer customer3 = new Customer("3");

        customer1.SubscribePlan(new Gold(dataBase));
        customer2.SubscribePlan(new Platinum(dataBase));
        customer1.updateSubcribePlan(new RoyalGold(dataBase));
        customer2.unSubscribePlan();
    

    }
}
