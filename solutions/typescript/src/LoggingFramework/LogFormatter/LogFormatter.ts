import LogMessage from "../LogMessage";

export default interface LogFormatter {
  format(message: LogMessage): string;
}
