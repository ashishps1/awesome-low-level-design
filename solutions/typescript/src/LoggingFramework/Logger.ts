import LogAppender from "./Appender/LogAppender";
import { isAsSevereAs, LogLevelEnum } from "./LogLevel";
import LogMessage from "./LogMessage";

export default class Logger {
  private minLevel: LogLevelEnum;
  private appenders: LogAppender[];

  public constructor(minLevel: LogLevelEnum, appenders: LogAppender[]) {
    this.minLevel = minLevel;
    this.appenders = appenders;
  }

  log(level: LogLevelEnum, msg: string) {
    if (!isAsSevereAs( level,this.minLevel)) return;
    const message = new LogMessage(level, msg);
    this.appenders.forEach((a) => a.append(message));
  }

  setMinLevel(minLevel: LogLevelEnum) {
    this.minLevel = minLevel;
  }

  debug(message: string) {
    this.log(LogLevelEnum.DEBUG, message);
  }
  info(message: string) {
    this.log(LogLevelEnum.INFO, message);
  }
  warn(message: string) {
    this.log(LogLevelEnum.WARN, message);
  }
  error(message: string) {
    this.log(LogLevelEnum.ERROR, message);
  }
  fatal(message: string) {
    this.log(LogLevelEnum.FATAL, message);
  }
}
