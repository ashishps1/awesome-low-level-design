using System.Collections.Generic;

namespace MusicStreamingService
{
    public class User
    {
        public string Id { get; }
        public string Username { get; }
        public string Password { get; }
        public List<Playlist> Playlists { get; }

        public User(string id, string username, string password)
        {
            Id = id;
            Username = username;
            Password = password;
            Playlists = new List<Playlist>();
        }

        public void AddPlaylist(Playlist playlist)
        {
            Playlists.Add(playlist);
        }

        public void RemovePlaylist(Playlist playlist)
        {
            Playlists.Remove(playlist);
        }
    }
}