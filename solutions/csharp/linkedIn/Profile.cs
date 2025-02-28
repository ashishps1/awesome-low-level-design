using System.Collections.Generic;

namespace LinkedInNamespace
{
    public class Profile
    {
        public string ProfilePicture { get; set; }
        public string Headline { get; set; }
        public string Summary { get; set; }
        public List<Experience> Experiences { get; set; }
        public List<Education> Educations { get; set; }
        public List<Skill> Skills { get; set; }

        public void SetSummary(string summary)
        {
            Summary = summary;
        }

        public void SetHeadline(string headline)
        {
            Headline = headline;
        }
    }
}