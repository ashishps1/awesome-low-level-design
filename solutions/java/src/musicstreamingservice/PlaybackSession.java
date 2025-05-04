package musicstreamingservice;

public class PlaybackSession {
    private Song currentSong;
    private boolean isPlaying = false;
    private int currentTime;

    public synchronized void play(Song song) {
        this.currentSong = song;
        this.isPlaying = true;
        currentTime = 0;
        System.out.println("Now playing: " + song.getTitle());
    }

    public synchronized void pause() {
        if (currentSong != null && isPlaying) {
            isPlaying = false;
            System.out.println("Paused: " + currentSong.getTitle());
        }
    }

    public void seekTo(int time) {
        currentTime = time;
        // Seek to the specified time in the song
        // ...
    }

    public synchronized Song getCurrentSong() {
        return currentSong;
    }

    public synchronized boolean isPlaying() {
        return isPlaying;
    }
}
