from .plain_text_view import PlainTextView
from .bold_decorator import BoldDecorator
from .italic_decorator import ItalicDecorator
from .underline_decorator import UnderlineDecorator


def decorator_demo():
    """Demonstrate Decorator pattern with text formatting"""
    print("=== Decorator Pattern Demo ===")
    
    # Create plain text
    plain_text = PlainTextView("Hello, World!")
    print(f"Plain text: {plain_text.show()}")
    
    # Apply single decorators
    print("\n--- Single Decorators ---")
    bold_text = BoldDecorator(PlainTextView("Bold text"))
    italic_text = ItalicDecorator(PlainTextView("Italic text"))
    underline_text = UnderlineDecorator(PlainTextView("Underlined text"))
    
    print(f"Bold: {bold_text.show()}")
    print(f"Italic: {italic_text.show()}")
    print(f"Underline: {underline_text.show()}")
    
    # Apply multiple decorators (decoration chaining)
    print("\n--- Multiple Decorators ---")
    bold_italic = ItalicDecorator(BoldDecorator(PlainTextView("Bold and Italic")))
    print(f"Bold + Italic: {bold_italic.show()}")
    
    bold_underline = UnderlineDecorator(BoldDecorator(PlainTextView("Bold and Underlined")))
    print(f"Bold + Underline: {bold_underline.show()}")
    
    all_formatted = UnderlineDecorator(
        ItalicDecorator(
            BoldDecorator(
                PlainTextView("All formatted text")
            )
        )
    )
    print(f"Bold + Italic + Underline: {all_formatted.show()}")
    
    # Different order of decoration
    print("\n--- Different Decoration Order ---")
    order1 = BoldDecorator(ItalicDecorator(PlainTextView("Order 1")))
    order2 = ItalicDecorator(BoldDecorator(PlainTextView("Order 2")))
    
    print(f"Italic then Bold: {order1.show()}")
    print(f"Bold then Italic: {order2.show()}")


if __name__ == "__main__":
    decorator_demo()