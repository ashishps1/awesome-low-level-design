from decimal import Decimal
from currency import Currency

class CurrencyConverter:
    exchange_rates = {
        Currency.USD: Decimal('1.00'),
        Currency.EUR: Decimal('0.85'),
        Currency.GBP: Decimal('0.72'),
        Currency.JPY: Decimal('110.00')
    }

    @staticmethod
    def convert(amount, source_currency, target_currency):
        source_rate = CurrencyConverter.exchange_rates[source_currency]
        target_rate = CurrencyConverter.exchange_rates[target_currency]
        return amount * source_rate / target_rate
