using System.Collections.Generic;

namespace MusicStreamingService
{
    public class Artist
    {
        public string Id { get; }
        public string Name { get; }
        public List<Album> Albums { get; }

        public Artist(string id, string name, List<Album> albums)
        {
            Id = id;
            Name = name;
            Albums = albums;
        }
    }
}