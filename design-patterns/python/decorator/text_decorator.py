from abc import ABC
from .text_view import TextView


class TextDecorator(TextView, ABC):
    """Base Decorator class"""
    
    def __init__(self, text_view: TextView):
        self._text_view = text_view
    
    def show(self) -> str:
        return self._text_view.show()