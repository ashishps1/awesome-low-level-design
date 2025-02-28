using System;
using System.Collections.Generic;

namespace LinkedInNamespace
{
    public class JobPosting
    {
        public string Id { get; }
        public string Title { get; }
        public string Description { get; }
        public List<string> Requirements { get; }
        public string Location { get; }
        public DateTime PostDate { get; }

        public JobPosting(string id, string title, string description, List<string> requirements, string location, DateTime postDate)
        {
            Id = id;
            Title = title;
            Description = description;
            Requirements = requirements;
            Location = location;
            PostDate = postDate;
        }
    }
}