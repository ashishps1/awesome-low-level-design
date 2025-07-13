import LogFormatter from "../LogFormatter/LogFormatter";
import LogMessage from "../LogMessage";
import LogAppender from "./LogAppender";

export default class ConsoleLogAppender implements LogAppender {
  private formatter: LogFormatter;

  constructor(formatter: LogFormatter) {
    this.formatter = formatter;
  }

  append(logMessage: LogMessage) {
    console.log(this.formatter.format(logMessage));
  }
}
