package digitalwallet

import (
	"math/big"
	"sync"
)

type CurrencyConverter struct {
	exchangeRates map[Currency]*big.Float
	mu            sync.RWMutex
}

var (
	currencyConverter *CurrencyConverter
	converterOnce     sync.Once
)

func GetCurrencyConverter() *CurrencyConverter {
	converterOnce.Do(func() {
		currencyConverter = &CurrencyConverter{
			exchangeRates: make(map[Currency]*big.Float),
		}
		currencyConverter.initializeRates()
	})
	return currencyConverter
}

func (cc *CurrencyConverter) initializeRates() {
	cc.mu.Lock()
	defer cc.mu.Unlock()

	one := big.NewFloat(1)
	cc.exchangeRates[USD] = one
	cc.exchangeRates[EUR] = big.NewFloat(0.85)
	cc.exchangeRates[GBP] = big.NewFloat(0.72)
	cc.exchangeRates[JPY] = big.NewFloat(110.00)
}

func (cc *CurrencyConverter) Convert(amount *big.Float, sourceCurrency, targetCurrency Currency) *big.Float {
	cc.mu.RLock()
	defer cc.mu.RUnlock()

	sourceRate := cc.exchangeRates[sourceCurrency]
	targetRate := cc.exchangeRates[targetCurrency]

	result := new(big.Float).Mul(amount, sourceRate)
	return new(big.Float).Quo(result, targetRate)
}
