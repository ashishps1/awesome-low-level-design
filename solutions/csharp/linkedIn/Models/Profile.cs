class Profile
{
    private string summary;
    private readonly List<Experience> experiences = new List<Experience>();
    private readonly List<Education> educations = new List<Education>();

    public void SetSummary(string summary) { this.summary = summary; }
    public void AddExperience(Experience experience) { experiences.Add(experience); }
    public void AddEducation(Education education) { educations.Add(education); }

    public void Display()
    {
        Console.WriteLine($"  Summary: {(summary ?? "N/A")}");

        Console.WriteLine("  Experience:");
        if (!experiences.Any())
        {
            Console.WriteLine("    - None");
        }
        else
        {
            foreach (var exp in experiences)
            {
                Console.WriteLine($"    - {exp}");
            }
        }

        Console.WriteLine("  Education:");
        if (!educations.Any())
        {
            Console.WriteLine("    - None");
        }
        else
        {
            foreach (var edu in educations)
            {
                Console.WriteLine($"    - {edu}");
            }
        }
    }
}