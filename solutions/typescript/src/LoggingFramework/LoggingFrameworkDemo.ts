import { LogLevelEnum } from "./LogLevel";
import LogManager from "./LogManager";

export default class LogginFrameworkDemo {
  static run() {
    const logger = LogManager.getLogger();

    // Logging with default configuration
    // Should log debug and above log levels
    logger.info("This is an information message");
    logger.warn("This is a warning message");
    logger.error("This is an error message");

    // Changing log level
    logger.setMinLevel(LogLevelEnum.WARN);

    // Should only log warn and above
    logger.debug("This is a debug message");
    logger.info("This is an information message");
    logger.warn("This is a warning message");
  }
}
