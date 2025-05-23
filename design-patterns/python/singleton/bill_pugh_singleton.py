class BillPughSingleton:
    """Bill Pugh singleton using inner class (Python equivalent using descriptor)"""
    
    class _SingletonHelper:
        def __init__(self):
            print("BillPughSingleton instance created")
            self.message = "Hello from BillPughSingleton!"
        
        def get_message(self) -> str:
            return self.message
    
    _instance = None
    
    @classmethod
    def get_instance(cls):
        if cls._instance is None:
            cls._instance = cls._SingletonHelper()
        return cls._instance