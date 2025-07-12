import { LogLevelEnum } from "./LogLevel";

export default class LogMessage {
  private logLevel: LogLevelEnum;
  private message: string;
  private timestamp: number;

  constructor(logLevel: LogLevelEnum, message: string) {
    this.logLevel = logLevel;
    this.message = message;
    this.timestamp = Date.now();
  }

  getMessage() {
    return this.message;
  }

  getLogLevel() {
    return this.logLevel;
  }

  getTimeStamp() {
    return this.timestamp;
  }

  toString() {
    return "[" + this.logLevel + "] " + this.timestamp + " - " + this.message;
  }
}
