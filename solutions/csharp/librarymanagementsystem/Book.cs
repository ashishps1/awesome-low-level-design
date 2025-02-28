namespace LibraryManagementSystem
{
    public class Book
    {
        public string Isbn { get; }
        public string Title { get; }
        public string Author { get; }
        public int PublicationYear { get; }
        public bool IsAvailable { get; set; }

        public Book(string isbn, string title, string author, int publicationYear)
        {
            Isbn = isbn;
            Title = title;
            Author = author;
            PublicationYear = publicationYear;
            IsAvailable = true;
        }
    }
}