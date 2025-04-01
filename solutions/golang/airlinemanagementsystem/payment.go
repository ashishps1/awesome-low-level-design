package airlinemanagementsystem

import "sync"

type Payment struct {
	PaymentID     string
	PaymentMethod string
	Amount        float64
	status        PaymentStatus
	mu            sync.RWMutex
}

func NewPayment(paymentID, paymentMethod string, amount float64) *Payment {
	return &Payment{
		PaymentID:     paymentID,
		PaymentMethod: paymentMethod,
		Amount:        amount,
		status:        PaymentStatusPending,
	}
}

func (p *Payment) ProcessPayment() {
	p.mu.Lock()
	defer p.mu.Unlock()
	p.status = PaymentStatusCompleted
}
