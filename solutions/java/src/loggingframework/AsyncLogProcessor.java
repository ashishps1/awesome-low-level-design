package loggingframework;

import loggingframework.entities.LogMessage;
import loggingframework.strategies.appender.LogAppender;

import java.util.List;
import java.util.concurrent.*;

class AsyncLogProcessor {
    private final ExecutorService executor;

    public AsyncLogProcessor() {
        this.executor = Executors.newSingleThreadExecutor(runnable -> {
            Thread thread = new Thread(runnable, "AsyncLogProcessor");
            thread.setDaemon(true); // Don't prevent JVM exit
            return thread;
        });
    }

    public void process(LogMessage logMessage, List<LogAppender> appenders) {
        if (executor.isShutdown()) {
            System.err.println("Logger is shut down. Cannot process log message.");
            return;
        }

        // Submit a new task to the executor.
        executor.submit(() -> {
            for (LogAppender appender : appenders) {
                appender.append(logMessage);
            }
        });
    }

    public void stop() {
        // Disable new tasks from being submitted
        executor.shutdown();
        try {
            if (!executor.awaitTermination(2, TimeUnit.SECONDS)) {
                System.err.println("Logger executor did not terminate in the specified time.");
                // Forcibly shut down any still-running tasks.
                executor.shutdownNow();
            }
        } catch (InterruptedException e) {
            executor.shutdownNow();
            // Preserve interrupt status
            Thread.currentThread().interrupt();
        }
    }
}
