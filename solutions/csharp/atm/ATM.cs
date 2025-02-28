using System;
using System.Threading;
using System.Globalization;

namespace ATM
{
    public class ATM
    {
        private readonly BankingService bankingService;
        private readonly CashDispenser cashDispenser;
        private static long transactionCounter = 0;

        public ATM(BankingService bankingService, CashDispenser cashDispenser)
        {
            this.bankingService = bankingService;
            this.cashDispenser = cashDispenser;
        }

        public void AuthenticateUser(Card card)
        {
            // User authentication logic
            // ...
        }

        public double CheckBalance(string accountNumber)
        {
            var account = bankingService.GetAccount(accountNumber);
            return account?.Balance ?? 0;
        }

        public void WithdrawCash(string accountNumber, double amount)
        {
            var account = bankingService.GetAccount(accountNumber);
            var transaction = new WithdrawalTransaction(GenerateTransactionId(), account, amount);
            bankingService.ProcessTransaction(transaction);
            cashDispenser.DispenseCash((int)amount);
        }

        public void DepositCash(string accountNumber, double amount)
        {
            var account = bankingService.GetAccount(accountNumber);
            var transaction = new DepositTransaction(GenerateTransactionId(), account, amount);
            bankingService.ProcessTransaction(transaction);
        }

        private string GenerateTransactionId()
        {
            var transactionNumber = Interlocked.Increment(ref transactionCounter);
            var timestamp = DateTime.Now.ToString("yyyyMMddHHmmss", CultureInfo.InvariantCulture);
            return $"TXN{timestamp}{transactionNumber:D10}";
        }
    }
}