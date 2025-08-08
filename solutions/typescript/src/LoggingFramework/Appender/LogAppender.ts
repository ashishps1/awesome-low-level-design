import LogMessage from "../LogMessage";

export default interface LogAppender {
  append(logMessage: LogMessage): void;
}
