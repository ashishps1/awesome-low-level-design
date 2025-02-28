using System.Collections.Concurrent;

namespace MusicStreamingService
{
    public class UserManager
    {
        private static UserManager instance;
        private readonly ConcurrentDictionary<string, User> users;

        private UserManager()
        {
            users = new ConcurrentDictionary<string, User>();
        }

        public static UserManager GetInstance()
        {
            if (instance == null)
            {
                instance = new UserManager();
            }
            return instance;
        }

        public void RegisterUser(User user)
        {
            users[user.Id] = user;
        }

        public User LoginUser(string username, string password)
        {
            foreach (var user in users.Values)
            {
                if (user.Username == username && user.Password == password)
                {
                    return user;
                }
            }
            return null;
        }
    }
}