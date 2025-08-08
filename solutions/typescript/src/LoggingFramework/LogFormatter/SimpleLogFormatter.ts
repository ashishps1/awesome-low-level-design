import LogMessage from "../LogMessage";
import LogFormatter from "./LogFormatter";

export default class SimpleLogFormatter implements LogFormatter {
  format(message: LogMessage): string {
    return `[${message.getTimeStamp()}] - [${message.getLogLevel()}] - [${message.getMessage()}]`;
  }
}
