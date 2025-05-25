public class ShoeManufacture {

    static ShoeFactory shoeFactory;
    public static Shoe produceShoe(String shoeType)
    {
        if(shoeType == "Formal")
        {
            shoeFactory = new FormalShoeFactory();
        }
        if(shoeType == "Sports")
        {
            shoeFactory = new SportsShoeFactory();
        }
        if(shoeType == "Casual")
        {
            shoeFactory = new CasualShoeFactory();
        }
        return new Shoe(shoeFactory.createShoeSole(), shoeFactory.createShoeLace());
    }
    public static void main(String[] args) {
        Shoe formalShoe = produceShoe("Formal");
        Shoe sportaShoe = produceShoe("Sports");
        Shoe casualShoe = produceShoe("Casual");

        formalShoe.displayBuildShoe();
        sportaShoe.displayBuildShoe();
        casualShoe.displayBuildShoe();



    }
    
}
