package musicstreamingservice.state;

import musicstreamingservice.enums.PlayerStatus;
import musicstreamingservice.entities.Player;

public class PlayingState implements PlayerState {
    @Override
    public void play(Player player) { System.out.println("Already playing."); }

    @Override
    public void pause(Player player) {
        System.out.println("Pausing playback." + player);
        player.changeState(new PausedState());
        player.setStatus(PlayerStatus.PAUSED);
    }

    @Override
    public void stop(Player player) {
        System.out.println("Stopping playback.");
        player.changeState(new StoppedState());
        player.setStatus(PlayerStatus.STOPPED);
    }
}
