class Education
{
    private readonly string school;
    private readonly string degree;
    private readonly int startYear;
    private readonly int endYear;

    public Education(string school, string degree, int startYear, int endYear)
    {
        this.school = school;
        this.degree = degree;
        this.startYear = startYear;
        this.endYear = endYear;
    }

    public override string ToString()
    {
        return $"{degree}, {school} ({startYear} - {endYear})";
    }
}