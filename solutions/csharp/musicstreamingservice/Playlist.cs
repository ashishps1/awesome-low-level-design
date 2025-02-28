using System.Collections.Generic;

namespace MusicStreamingService
{
    public class Playlist
    {
        public string Id { get; }
        public string Name { get; }
        public User Owner { get; }
        public List<Song> Songs { get; }

        public Playlist(string id, string name, User owner)
        {
            Id = id;
            Name = name;
            Owner = owner;
            Songs = new List<Song>();
        }

        public void AddSong(Song song)
        {
            Songs.Add(song);
        }

        public void RemoveSong(Song song)
        {
            Songs.Remove(song);
        }
    }
}