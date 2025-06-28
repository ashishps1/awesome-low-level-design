package atm;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Scanner;
import java.util.concurrent.atomic.AtomicLong;

public class ATM {
    private final BankingService bankingService;
    private final CashDispenser cashDispenser;
    private static final AtomicLong transactionCounter = new AtomicLong(0);

    public ATM(BankingService bankingService, CashDispenser cashDispenser) {
        this.bankingService = bankingService;
        this.cashDispenser = cashDispenser;
    }

    public void authenticateUser(Card card) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter PIN for card " + card.getCardNumber() + ": ");
        String enteredPin = scanner.nextLine();

        boolean isAuthenticated = bankingService.authenticate(card.getCardNumber(), enteredPin);
        if (isAuthenticated) {
            System.out.println("Authentication successful.");
        } else {
            System.out.println("Authentication failed.");
        }
    }

    public double checkBalance(String accountNumber) {
        Account account = bankingService.getAccount(accountNumber);
        return account.getBalance();
    }

    public void withdrawCash(String accountNumber, double amount) {
        Account account = bankingService.getAccount(accountNumber);
        // Check if sufficient balance is available
        if (account != null && account.getBalance() < amount) {
            System.out.println("Error: Insufficient balance.");
            return;
        }
        Transaction transaction = new WithdrawalTransaction(generateTransactionId(), account, amount);
        bankingService.processTransaction(transaction);
        cashDispenser.dispenseCash((int) amount);
    }

    public void depositCash(String accountNumber, double amount) {
        Account account = bankingService.getAccount(accountNumber);
        Transaction transaction = new DepositTransaction(generateTransactionId(), account, amount);
        bankingService.processTransaction(transaction);
    }

    private String generateTransactionId() {
        // Generate a unique transaction ID
        long transactionNumber = transactionCounter.incrementAndGet();
        String timestamp = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyyMMddHHmmss"));
        return "TXN" + timestamp + String.format("%010d", transactionNumber);
    }
}
