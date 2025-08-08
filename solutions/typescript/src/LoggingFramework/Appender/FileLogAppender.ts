import * as fs from "fs";
import * as path from "path";
import LogAppender from "./LogAppender";
import LogMessage from "../LogMessage";
import LogFormatter from "../LogFormatter/LogFormatter";

export default class FileLogAppender implements LogAppender {
  private writer!: fs.WriteStream;
  private formatter: LogFormatter;

  constructor(filePath: string, formatter: LogFormatter) {
    this.formatter = formatter;
    const dir = path.dirname(filePath);

    if (!fs.existsSync(dir)) {
      fs.mkdirSync(dir, { recursive: true });
    }

    try {
      this.writer = fs.createWriteStream(filePath, { flags: "a" });
    } catch (e) {
      console.error("Failed to create writer for file logs, exception:", e);
    }
  }

  public append(logMessage: LogMessage): void {
    try {
      const formattedMessage = this.formatter.format(logMessage);
      this.writer.write(formattedMessage + "\n");
    } catch (e) {
      console.error("Failed to write logs to file, exception:", e);
    }
  }
}
