class EagerSingleton:
    """Eager initialization singleton - instance created at class loading time"""
    
    _instance = None
    
    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance._initialized = False
        return cls._instance
    
    def __init__(self):
        if self._initialized:
            return
        print("EagerSingleton instance created")
        self._initialized = True
    
    def get_message(self) -> str:
        return "Hello from EagerSingleton!"


# Create instance at module load time (similar to Java static initialization)
_eager_instance = EagerSingleton()