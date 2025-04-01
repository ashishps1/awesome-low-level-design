package loggingframework.logappender;

import loggingframework.LogMessage;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class DatabaseAppender implements LogAppender {
    private final String jdbcUrl;
    private final String username;
    private final String password;

    public DatabaseAppender(String jdbcUrl, String username, String password) {
        this.jdbcUrl = jdbcUrl;
        this.username = username;
        this.password = password;
    }

    @Override
    public void append(LogMessage logMessage) {
        try (Connection connection = DriverManager.getConnection(jdbcUrl, username, password);
             PreparedStatement statement = connection.prepareStatement("INSERT INTO logs (level, message, timestamp) VALUES (?, ?, ?)")) {
            statement.setString(1, logMessage.getLevel().toString());
            statement.setString(2, logMessage.getMessage());
            statement.setLong(3, logMessage.getTimestamp());
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
