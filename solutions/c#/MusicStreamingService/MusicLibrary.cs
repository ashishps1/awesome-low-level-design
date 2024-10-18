using System.Collections.Concurrent;
using System.Collections.Generic;

namespace MusicStreamingService
{
    public class MusicLibrary
    {
        private static MusicLibrary instance;
        private readonly ConcurrentDictionary<string, Song> songs;
        private readonly ConcurrentDictionary<string, Album> albums;
        private readonly ConcurrentDictionary<string, Artist> artists;

        private MusicLibrary()
        {
            songs = new ConcurrentDictionary<string, Song>();
            albums = new ConcurrentDictionary<string, Album>();
            artists = new ConcurrentDictionary<string, Artist>();
        }

        public static MusicLibrary GetInstance()
        {
            if (instance == null)
            {
                instance = new MusicLibrary();
            }
            return instance;
        }

        public void AddSong(Song song)
        {
            songs[song.Id] = song;
        }

        public void AddAlbum(Album album)
        {
            albums[album.Id] = album;
            foreach (var song in album.Songs)
            {
                AddSong(song);
            }
        }

        public void AddArtist(Artist artist)
        {
            artists[artist.Id] = artist;
            foreach (var album in artist.Albums)
            {
                AddAlbum(album);
            }
        }

        public Song GetSong(string songId)
        {
            return songs.TryGetValue(songId, out var song) ? song : null;
        }

        public Album GetAlbum(string albumId)
        {
            return albums.TryGetValue(albumId, out var album) ? album : null;
        }

        public Artist GetArtist(string artistId)
        {
            return artists.TryGetValue(artistId, out var artist) ? artist : null;
        }

        public List<Song> SearchSongs(string query)
        {
            var matchingSongs = new List<Song>();
            foreach (var song in songs.Values)
            {
                if (song.Title.Contains(query) || song.Artist.Contains(query) || song.Album.Contains(query))
                {
                    matchingSongs.Add(song);
                }
            }
            return matchingSongs;
        }
    }
}