using System;
using System.Collections.Generic;

namespace DigitalWallet
{
    public class User
    {
        private readonly string id;
        private readonly string name;
        private readonly string email;
        private readonly string password;
        private readonly List<Account> accounts;

        public User(string id, string name, string email, string password)
        {
            this.id = id;
            this.name = name;
            this.email = email;
            this.password = password;
            this.accounts = new List<Account>();
        }

        public void AddAccount(Account account)
        {
            accounts.Add(account);
        }

        public void RemoveAccount(Account account)
        {
            accounts.Remove(account);
        }

        public string GetId()
        {
            return id;
        }
    }
}