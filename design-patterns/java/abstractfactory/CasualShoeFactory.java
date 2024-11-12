public class CasualShoeFactory implements ShoeFactory {

    @Override
    public Sole createShoeSole() {
        return new ThinSole();
    }

    @Override
    public ShoeLace createShoeLace() {
        return new TapeShoeLace();
    }
    
}
