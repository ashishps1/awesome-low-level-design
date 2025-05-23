import threading


class ThreadSafeSingleton:
    """Thread-safe singleton using lock"""
    
    _instance = None
    _lock = threading.Lock()
    
    def __new__(cls):
        if cls._instance is None:
            with cls._lock:
                if cls._instance is None:
                    cls._instance = super().__new__(cls)
                    print("ThreadSafeSingleton instance created")
        return cls._instance
    
    def get_message(self) -> str:
        return "Hello from ThreadSafeSingleton!"