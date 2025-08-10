class Experience
{
    private readonly string title;
    private readonly string company;
    private readonly string startDate;
    private readonly string endDate; // null for current job

    public Experience(string title, string company, string startDate, string endDate)
    {
        this.title = title;
        this.company = company;
        this.startDate = startDate;
        this.endDate = endDate;
    }

    public override string ToString()
    {
        string end = string.IsNullOrEmpty(endDate) ? "Present" : endDate;
        return $"{title} at {company} ({startDate} to {end})";
    }
}