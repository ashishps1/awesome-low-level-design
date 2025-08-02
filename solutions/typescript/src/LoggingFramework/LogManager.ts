import ConsoleLogAppender from "./Appender/ConsoleLogAppender";
import FileLogAppender from "./Appender/FileLogAppender";
import LogAppender from "./Appender/LogAppender";
import SimpleLogFormatter from "./LogFormatter/SimpleLogFormatter";
import Logger from "./Logger";
import { LogLevelEnum } from "./LogLevel";

export default class LogManager {
    private static logger: Logger;

    static getLogger() {
        if (this.logger == null) {
            this.logger = new LogManager.LoggerBuilder()
                .setLevel(LogLevelEnum.DEBUG)
                .addAppender(new ConsoleLogAppender(new SimpleLogFormatter()))
                .addAppender(
                    new FileLogAppender("log.txt", new SimpleLogFormatter()),
                )
                .build();
        }
        return this.logger;
    }

    static LoggerBuilder = class {
        private level: LogLevelEnum = LogLevelEnum.INFO;
        private appenders: LogAppender[] = [];

        setLevel(level: LogLevelEnum): this {
            this.level = level;
            return this;
        }

        addAppender(appender: LogAppender): this {
            this.appenders.push(appender);
            return this;
        }

        build(): Logger {
            return new Logger(this.level, this.appenders);
        }
    };
}
