public class FactoryApplication {
    static public DataBase dataBase;

    public static void main(String[] arg) {
        dataBase = new DataBase();
        SubscriptionFactory factory = new SubscriptionFactory(dataBase);
        Customer customer1 = new Customer("1");
        Customer customer2 = new Customer("2");
        Customer customer3 = new Customer("3");


        customer1.SubscribePlan(factory.getSubscription("gold"));
        customer2.SubscribePlan(factory.getSubscription("silver"));
        customer1.updateSubcribePlan(factory.getSubscription("royalGold"));
        customer2.unSubscribePlan();
        customer3.SubscribePlan(factory.getSubscription("platinum"));


    }
}
