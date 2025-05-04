package loggingframework;

public class DefaultFormatter implements LogFormatter{
    @Override
    public String format(LogMessage msg) {
        return String.format("[%s] [%s] [%s] %s",
                msg.getTimestamp(), msg.getThreadName(), msg.getLevel(), msg.getMessage());
    }
}
