package musicstreamingservice.state;

import musicstreamingservice.enums.PlayerStatus;
import musicstreamingservice.entities.Player;

public class PausedState implements PlayerState {
    @Override
    public void play(Player player) {
        System.out.println("Resuming playback.");
        player.changeState(new PlayingState());
        player.setStatus(PlayerStatus.PLAYING);
    }

    @Override
    public void pause(Player player) { System.out.println("Already paused."); }

    @Override
    public void stop(Player player) {
        System.out.println("Stopping playback from paused state.");
        player.changeState(new StoppedState());
        player.setStatus(PlayerStatus.STOPPED);
    }
}
