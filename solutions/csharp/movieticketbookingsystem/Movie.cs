namespace MovieTicketBookingSystem
{
    public class Movie
    {
        public string Id { get; }
        public string Title { get; }
        public string Description { get; }
        public int DurationInMinutes { get; }

        public Movie(string id, string title, string description, int durationInMinutes)
        {
            Id = id;
            Title = title;
            Description = description;
            DurationInMinutes = durationInMinutes;
        }
    }
}