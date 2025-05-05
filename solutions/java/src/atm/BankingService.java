package atm;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class BankingService {
    private final Map<String, Account> accounts = new ConcurrentHashMap<>();
    private final Map<String, Card> cards = new ConcurrentHashMap<>();

    public void createAccount(String accountNumber, double initialBalance) {
        accounts.put(accountNumber, new Account(accountNumber, initialBalance));
    }

    public Account getAccount(String accountNumber) {
        return accounts.get(accountNumber);
    }

    public void processTransaction(Transaction transaction) {
        transaction.execute();
    }

    public void linkCardToAccount(String cardNumber, String pin, String accountNumber) {
        if (accounts.containsKey(accountNumber)) {
            cards.put(cardNumber, new Card(cardNumber, pin));
        }
    }

    public Card getCard(String cardNumber) {
        return cards.get(cardNumber);
    }

    public boolean authenticate(String cardNumber, String pin) {
        Card card = cards.get(cardNumber);
        return card != null && card.getPin().equals(pin);
    }
}
