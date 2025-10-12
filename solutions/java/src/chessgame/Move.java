package chessgame;

public class Move {
    private final Cell start;
    private final Cell end;

    public Move(Cell start, Cell end) {
        this.start = start;
        this.end = end;
    }

    public Cell getStart() { return start; }

    public Cell getEnd() { return end; }
}
