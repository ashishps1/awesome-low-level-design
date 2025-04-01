package atm

import (
	"errors"
	"fmt"
	"sync/atomic"
	"time"
)

type ATM struct {
	bankingService *BankingService
	cashDispenser  *CashDispenser
	txnCounter     int64
}

func NewATM(bankingService *BankingService, cashDispenser *CashDispenser) *ATM {
	return &ATM{
		bankingService: bankingService,
		cashDispenser:  cashDispenser,
	}
}

func (a *ATM) AuthenticateUser(card *Card) error {
	// Authentication logic would go here
	return nil
}

func (a *ATM) CheckBalance(accountNumber string) (float64, error) {
	account := a.bankingService.GetAccount(accountNumber)
	if account == nil {
		return 0, errors.New("account not found")
	}
	return account.GetBalance(), nil
}

func (a *ATM) WithdrawCash(accountNumber string, amount float64) error {
	account := a.bankingService.GetAccount(accountNumber)
	if account == nil {
		return errors.New("account not found")
	}

	transaction := NewWithdrawalTransaction(a.generateTransactionID(), account, amount)
	if err := a.bankingService.ProcessTransaction(transaction); err != nil {
		return err
	}

	return a.cashDispenser.DispenseCash(int(amount))
}

func (a *ATM) DepositCash(accountNumber string, amount float64) error {
	account := a.bankingService.GetAccount(accountNumber)
	if account == nil {
		return errors.New("account not found")
	}

	transaction := NewDepositTransaction(a.generateTransactionID(), account, amount)
	return a.bankingService.ProcessTransaction(transaction)
}

func (a *ATM) generateTransactionID() string {
	txnNumber := atomic.AddInt64(&a.txnCounter, 1)
	timestamp := time.Now().Format("20060102150405")
	return fmt.Sprintf("TXN%s%010d", timestamp, txnNumber)
}
