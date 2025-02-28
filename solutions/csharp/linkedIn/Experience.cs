namespace LinkedInNamespace
{
    public class Experience
    {
        public string Title { get; set; }
        public string Company { get; set; }
        public string StartDate { get; set; }
        public string EndDate { get; set; }
        public string Description { get; set; }

        public Experience(string title, string company, string startDate, string endDate, string description)
        {
            Title = title;
            Company = company;
            StartDate = startDate;
            EndDate = endDate;
            Description = description;
        }
    }
}