class RemoteControlWithUndo {
    private List<Command> commands = new ArrayList<>();
    private List<Command> undoCommands = new ArrayList<>();

    public void addCommand(Command command) {
        commands.add(command);
    }

    public void executeCommands() {
        for (Command command : commands) {
            command.execute();
            undoCommands.add(command);
        }
        commands.clear();
    }

    public void undoLastCommand() {
        if (!undoCommands.isEmpty()) {
            Command lastCommand = undoCommands.remove(undoCommands.size() - 1);
            lastCommand.undo();
        }
    }
}