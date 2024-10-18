namespace LinkedInNamespace
{
    public class Education
    {
        public string School { get; set; }
        public string Degree { get; set; }
        public string FieldOfStudy { get; set; }
        public string StartDate { get; set; }
        public string EndDate { get; set; }

        public Education(string school, string degree, string fieldOfStudy, string startDate, string endDate)
        {
            School = school;
            Degree = degree;
            FieldOfStudy = fieldOfStudy;
            StartDate = startDate;
            EndDate = endDate;
        }
    }
}