using System;
//using System.Data.SqlClient;

namespace LoggingFramework
{
    public class DatabaseAppender : LogAppender
    {
        private readonly string _connectionString;

        public DatabaseAppender(string connectionString)
        {
            _connectionString = connectionString;
        }

        public void Append(LogMessage logMessage)
        {
            // try
            // {
            //     using (var connection = new SqlConnection(_connectionString))
            //     {
            //         connection.Open();
            //         var command = new SqlCommand("INSERT INTO logs (level, message, timestamp) VALUES (@level, @message, @timestamp)", connection);
            //         command.Parameters.AddWithValue("@level", logMessage.Level.ToString());
            //         command.Parameters.AddWithValue("@message", logMessage.Message);
            //         command.Parameters.AddWithValue("@timestamp", logMessage.Timestamp);
            //         command.ExecuteNonQuery();
            //     }
            // }
            // catch (SqlException ex)
            // {
            //     Console.WriteLine("DatabaseAppender error: " + ex.Message);
            // }
        }
    }
}