from .text_view import TextView


class PlainTextView(TextView):
    """Concrete Component - Plain text display"""
    
    def __init__(self, text: str):
        self._text = text
    
    def show(self) -> str:
        return self._text