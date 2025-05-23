from .text_decorator import TextDecorator
from .text_view import TextView


class UnderlineDecorator(TextDecorator):
    """Concrete Decorator - Underline text formatting"""
    
    def __init__(self, text_view: TextView):
        super().__init__(text_view)
    
    def show(self) -> str:
        return f"<u>{self._text_view.show()}</u>"