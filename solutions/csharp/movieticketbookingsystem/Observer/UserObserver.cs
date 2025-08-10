class UserObserver : IMovieObserver
{
    private readonly User user;

    public UserObserver(User user)
    {
        this.user = user;
    }

    public void Update(Movie movie)
    {
        Console.WriteLine($"Notification for {user.GetName()} ({user.GetId()}): Movie '{movie.GetTitle()}' is now available for booking!");
    }
}