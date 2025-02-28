using System.Collections.Generic;

namespace MusicStreamingService
{
    public class Album
    {
        public string Id { get; }
        public string Title { get; }
        public string Artist { get; }
        public List<Song> Songs { get; }

        public Album(string id, string title, string artist, List<Song> songs)
        {
            Id = id;
            Title = title;
            Artist = artist;
            Songs = songs;
        }
    }
}