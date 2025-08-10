class MovieBookingService
{
    private static volatile MovieBookingService instance;
    private static readonly object syncRoot = new object();

    private readonly Dictionary<string, City> cities;
    private readonly Dictionary<string, Cinema> cinemas;
    private readonly Dictionary<string, Movie> movies;
    private readonly Dictionary<string, User> users;
    private readonly Dictionary<string, Show> shows;

    private readonly SeatLockManager seatLockManager;
    private readonly BookingManager bookingManager;

    private MovieBookingService()
    {
        this.cities = new Dictionary<string, City>();
        this.cinemas = new Dictionary<string, Cinema>();
        this.movies = new Dictionary<string, Movie>();
        this.users = new Dictionary<string, User>();
        this.shows = new Dictionary<string, Show>();

        this.seatLockManager = new SeatLockManager();
        this.bookingManager = new BookingManager(seatLockManager);
    }

    public static MovieBookingService GetInstance()
    {
        if (instance == null)
        {
            lock (syncRoot)
            {
                if (instance == null)
                {
                    instance = new MovieBookingService();
                }
            }
        }
        return instance;
    }

    public BookingManager GetBookingManager()
    {
        return bookingManager;
    }

    public City AddCity(string id, string name)
    {
        var city = new City(id, name);
        cities[city.GetId()] = city;
        return city;
    }

    public Cinema AddCinema(string id, string name, string cityId, List<Screen> screens)
    {
        var city = cities[cityId];
        var cinema = new Cinema(id, name, city, screens);
        cinemas[cinema.GetId()] = cinema;
        return cinema;
    }

    public void AddMovie(Movie movie)
    {
        movies[movie.GetId()] = movie;
    }

    public Show AddShow(string id, Movie movie, Screen screen, DateTime startTime, IPricingStrategy pricingStrategy)
    {
        var show = new Show(id, movie, screen, startTime, pricingStrategy);
        shows[show.GetId()] = show;
        return show;
    }

    public User CreateUser(string name, string email)
    {
        var user = new User(name, email);
        users[user.GetId()] = user;
        return user;
    }

    public Booking BookTickets(string userId, string showId, List<Seat> desiredSeats, IPaymentStrategy paymentStrategy)
    {
        return bookingManager.CreateBooking(
            users[userId],
            shows[showId],
            desiredSeats,
            paymentStrategy
        );
    }

    public List<Show> FindShows(string movieTitle, string cityName)
    {
        var result = new List<Show>();
        foreach (var show in shows.Values)
        {
            if (show.GetMovie().GetTitle().Equals(movieTitle, StringComparison.OrdinalIgnoreCase))
            {
                var cinema = FindCinemaForShow(show);
                if (cinema != null && cinema.GetCity().GetName().Equals(cityName, StringComparison.OrdinalIgnoreCase))
                {
                    result.Add(show);
                }
            }
        }
        return result;
    }

    private Cinema FindCinemaForShow(Show show)
    {
        return cinemas.Values.FirstOrDefault(cinema => cinema.GetScreens().Contains(show.GetScreen()));
    }

    public void Shutdown()
    {
        seatLockManager.Shutdown();
        Console.WriteLine("MovieTicketBookingSystem has been shut down.");
    }
}