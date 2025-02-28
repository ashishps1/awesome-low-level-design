namespace MusicStreamingService
{
    public class Song
    {
        public string Id { get; }
        public string Title { get; }
        public string Artist { get; }
        public string Album { get; }
        public int Duration { get; }

        public Song(string id, string title, string artist, string album, int duration)
        {
            Id = id;
            Title = title;
            Artist = artist;
            Album = album;
            Duration = duration;
        }
    }
}