package digitalwallet;

import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.HashMap;
import java.util.Map;

public class CurrencyConverter {
    private static final Map<Currency, BigDecimal> exchangeRates = new HashMap<>();

    static {
        // Initialize exchange rates
        exchangeRates.put(Currency.USD, BigDecimal.ONE);
        exchangeRates.put(Currency.EUR, new BigDecimal("0.85"));
        exchangeRates.put(Currency.GBP, new BigDecimal("0.72"));
        exchangeRates.put(Currency.JPY, new BigDecimal("110.00"));
        // Add more exchange rates as needed
    }

    public static BigDecimal convert(BigDecimal amount, Currency sourceCurrency, Currency targetCurrency) {
        BigDecimal sourceRate = exchangeRates.get(sourceCurrency);
        BigDecimal targetRate = exchangeRates.get(targetCurrency);
        return amount.multiply(sourceRate).divide(targetRate, RoundingMode.HALF_UP);
    }
}
