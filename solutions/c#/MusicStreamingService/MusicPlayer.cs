namespace MusicStreamingService
{
    public class MusicPlayer
    {
        private Song currentSong;
        private bool isPlaying;
        private int currentTime;

        public void PlaySong(Song song)
        {
            currentSong = song;
            isPlaying = true;
            currentTime = 0;
            // Start playing the song logic
        }

        public void PauseSong()
        {
            isPlaying = false;
            // Pause logic
        }

        public void SeekTo(int time)
        {
            currentTime = time;
            // Seek logic
        }
    }
}