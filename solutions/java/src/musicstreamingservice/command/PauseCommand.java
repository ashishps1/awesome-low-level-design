package musicstreamingservice.command;

import musicstreamingservice.entities.Player;

public class PauseCommand implements Command {
    private final Player player;

    public PauseCommand(Player player) { this.player = player; }

    @Override
    public void execute() { player.clickPause(); }
}
