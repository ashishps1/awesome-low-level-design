using System;

namespace LinkedInNamespace
{
    public class Connection
    {
        public User User { get; }
        public DateTime ConnectionDate { get; }

        public Connection(User user, DateTime connectionDate)
        {
            User = user;
            ConnectionDate = connectionDate;
        }
    }
}