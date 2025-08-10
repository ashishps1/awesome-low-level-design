class SearchService
{
    public List<Song> SearchSongsByTitle(List<Song> songs, string query)
    {
        return songs.Where(s => s.GetTitle().ToLower().Contains(query.ToLower())).ToList();
    }

    public List<Artist> SearchArtistsByName(List<Artist> artists, string query)
    {
        return artists.Where(a => a.GetName().ToLower().Contains(query.ToLower())).ToList();
    }
}