from enum import Enum


class EnumSingleton(Enum):
    """Enum-based singleton - most robust approach"""
    
    INSTANCE = "singleton_instance"
    
    def __init__(self, value):
        print("EnumSingleton instance created")
        self.value = value
    
    def get_message(self) -> str:
        return "Hello from EnumSingleton!"
    
    @classmethod
    def get_instance(cls):
        return cls.INSTANCE