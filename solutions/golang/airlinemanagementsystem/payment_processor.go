package airlinemanagementsystem

import "sync"

type PaymentProcessor struct {
	mu sync.Mutex
}

var (
	paymentProcessor *PaymentProcessor
	paymentOnce      sync.Once
)

func GetPaymentProcessor() *PaymentProcessor {
	paymentOnce.Do(func() {
		paymentProcessor = &PaymentProcessor{}
	})
	return paymentProcessor
}

func (p *PaymentProcessor) ProcessPayment(payment *Payment) {
	p.mu.Lock()
	defer p.mu.Unlock()
	payment.ProcessPayment()
}
