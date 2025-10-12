package musicstreamingservice.state;

import musicstreamingservice.enums.PlayerStatus;
import musicstreamingservice.entities.Player;

public class StoppedState implements PlayerState {
    @Override
    public void play(Player player) {
        if (player.hasQueue()) {
            System.out.println("Starting playback.");
            player.changeState(new PlayingState());
            player.setStatus(PlayerStatus.PLAYING);
            player.playCurrentSongInQueue();
        } else {
            System.out.println("Queue is empty. Load songs to play.");
        }
    }

    @Override
    public void pause(Player player) { System.out.println("Cannot pause. Player is stopped."); }

    @Override
    public void stop(Player player) { System.out.println("Already stopped."); }
}
