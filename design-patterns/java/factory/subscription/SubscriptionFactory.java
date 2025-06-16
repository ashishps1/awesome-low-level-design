public class SubscriptionFactory {
    private final DataBase dataBase;

    public SubscriptionFactory(DataBase dataBase){
        this.dataBase = dataBase;
    }
    public Subscription getSubscription(String subscriptionType){

        return switch (subscriptionType) {
            case "gold" -> new Gold(dataBase);
            case "silver" -> new Silver(dataBase);
            case "platinum" -> new Platinum(dataBase);
            case "royalGold" -> new RoyalGold(dataBase);
            default -> throw new IllegalArgumentException("Unknown subcription type");
        };

    }
}
