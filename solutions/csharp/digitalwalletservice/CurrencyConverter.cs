using System;
using System.Collections.Generic;
using System.Numerics;

namespace DigitalWallet
{
    public class CurrencyConverter
    {
        private static readonly Dictionary<Currency, decimal> exchangeRates = new Dictionary<Currency, decimal>
        {
            { Currency.USD, 1.00M },
            { Currency.EUR, 0.85M },
            { Currency.GBP, 0.72M },
            { Currency.JPY, 110.00M }
        };

        public static decimal Convert(decimal amount, Currency sourceCurrency, Currency targetCurrency)
        {
            decimal sourceRate = exchangeRates[sourceCurrency];
            decimal targetRate = exchangeRates[targetCurrency];
            return amount * sourceRate / targetRate;
        }
    }
}