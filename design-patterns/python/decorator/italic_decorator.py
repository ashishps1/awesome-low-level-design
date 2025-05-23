from .text_decorator import TextDecorator
from .text_view import TextView


class ItalicDecorator(TextDecorator):
    """Concrete Decorator - Italic text formatting"""
    
    def __init__(self, text_view: TextView):
        super().__init__(text_view)
    
    def show(self) -> str:
        return f"<i>{self._text_view.show()}</i>"