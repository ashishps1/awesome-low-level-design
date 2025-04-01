public class SportsShoeFactory implements ShoeFactory {

    @Override
    public Sole createShoeSole() {
        return new BumpySole();
    }

    @Override
    public ShoeLace createShoeLace() {
        return new RoundShoeLace();
     }
    
}
