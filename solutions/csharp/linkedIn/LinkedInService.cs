using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;

namespace LinkedInNamespace
{
    public class LinkedInService
    {
        private static LinkedInService _instance;
        private readonly ConcurrentDictionary<string, User> _users;
        private readonly ConcurrentDictionary<string, JobPosting> _jobPostings;
        private readonly ConcurrentDictionary<string, List<Notification>> _notifications;

        private LinkedInService()
        {
            _users = new ConcurrentDictionary<string, User>();
            _jobPostings = new ConcurrentDictionary<string, JobPosting>();
            _notifications = new ConcurrentDictionary<string, List<Notification>>();
        }

        public static LinkedInService GetInstance()
        {
            return _instance ??= new LinkedInService();
        }

        public void RegisterUser(User user)
        {
            _users[user.Id] = user;
        }

        public User LoginUser(string email, string password)
        {
            return _users.Values.FirstOrDefault(user => user.Email == email && user.Password == password);
        }

        public void UpdateUserProfile(User user)
        {
            _users[user.Id] = user;
        }

        public void SendConnectionRequest(User sender, User receiver)
        {
            var connection = new Connection(sender, DateTime.Now);
            receiver.Connections.Add(connection);
            var notification = new Notification(GenerateNotificationId(), receiver, NotificationType.ConnectionRequest,
                $"New connection request from {sender.Name}", DateTime.Now);
            AddNotification(receiver.Id, notification);
        }

        public void AcceptConnectionRequest(User user, User connectionUser)
        {
            user.Connections.Add(new Connection(connectionUser, DateTime.Now));
        }

        public List<User> SearchUsers(string keyword)
        {
            return _users.Values.Where(user => user.Name.Contains(keyword, StringComparison.OrdinalIgnoreCase)).ToList();
        }

        public void PostJobListing(JobPosting jobPosting)
        {
            _jobPostings[jobPosting.Id] = jobPosting;
            foreach (var user in _users.Values)
            {
                var notification = new Notification(GenerateNotificationId(), user, NotificationType.JobPosting,
                    $"New job posting: {jobPosting.Title}", DateTime.Now);
                AddNotification(user.Id, notification);
            }
        }

        public List<JobPosting> SearchJobPostings(string keyword)
        {
            return _jobPostings.Values.Where(posting =>
                    posting.Title.Contains(keyword, StringComparison.OrdinalIgnoreCase) ||
                    posting.Description.Contains(keyword, StringComparison.OrdinalIgnoreCase))
                .ToList();
        }

        public void SendMessage(User sender, User receiver, string content)
        {
            var message = new Message(GenerateMessageId(), sender, receiver, content, DateTime.Now);
            receiver.Inbox.Add(message);
            sender.SentMessages.Add(message);
            var notification = new Notification(GenerateNotificationId(), receiver, NotificationType.Message,
                $"New message from {sender.Name}", DateTime.Now);
            AddNotification(receiver.Id, notification);
        }

        private void AddNotification(string userId, Notification notification)
        {
            _notifications.AddOrUpdate(userId, new List<Notification> { notification },
                (key, existingList) =>
                {
                    existingList.Add(notification);
                    return existingList;
                });
        }

        public List<Notification> GetNotifications(string userId)
        {
            return _notifications.GetValueOrDefault(userId, new List<Notification>());
        }

        private string GenerateNotificationId()
        {
            return Guid.NewGuid().ToString();
        }

        private string GenerateMessageId()
        {
            return Guid.NewGuid().ToString();
        }
    }
}