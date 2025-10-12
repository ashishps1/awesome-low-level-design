from log_manager import LogManager
from log_level import LogLevel
from log_appender import ConsoleAppender
import time

class LoggingFrameworkDemo:
    @staticmethod
    def main():
        # --- 1. Initial Configuration ---
        log_manager = LogManager.get_instance()
        root_logger = log_manager.get_root_logger()
        root_logger.set_level(LogLevel.INFO)  # Set global minimum level to INFO

        # Add a console appender to the root logger
        root_logger.add_appender(ConsoleAppender())

        print("--- Initial Logging Demo ---")
        main_logger = log_manager.get_logger("com.example.Main")
        main_logger.info("Application starting up.")
        main_logger.debug("This is a debug message, it should NOT appear.")  # Below root level
        main_logger.warn("This is a warning message.")

        # --- 2. Hierarchy and Additivity Demo ---
        print("\n--- Logger Hierarchy Demo ---")
        db_logger = log_manager.get_logger("com.example.db")
        # db_logger inherits level and appenders from root
        db_logger.info("Database connection pool initializing.")

        # Let's create a more specific logger and override its level
        service_logger = log_manager.get_logger("com.example.service.UserService")
        service_logger.set_level(LogLevel.DEBUG)  # More verbose logging for this specific service
        service_logger.info("User service starting.")
        service_logger.debug("This debug message SHOULD now appear for the service logger.")

        # --- 3. Dynamic Configuration Change ---
        print("\n--- Dynamic Configuration Demo ---")
        print("Changing root log level to DEBUG...")
        root_logger.set_level(LogLevel.DEBUG)
        main_logger.debug("This debug message should now be visible.")

        try:
            time.sleep(0.5)
            log_manager.shutdown()
        except Exception as e:
            print("Caught exception")

if __name__ == "__main__":
    LoggingFrameworkDemo.main()