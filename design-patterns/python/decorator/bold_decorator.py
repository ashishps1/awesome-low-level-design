from .text_decorator import TextDecorator
from .text_view import TextView


class BoldDecorator(TextDecorator):
    """Concrete Decorator - Bold text formatting"""
    
    def __init__(self, text_view: TextView):
        super().__init__(text_view)
    
    def show(self) -> str:
        return f"<b>{self._text_view.show()}</b>"