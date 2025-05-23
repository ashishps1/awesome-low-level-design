class LazySingleton:
    """Lazy initialization singleton - not thread-safe"""
    
    _instance = None
    
    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            print("LazySingleton instance created")
        return cls._instance
    
    def get_message(self) -> str:
        return "Hello from LazySingleton!"