public class DecoratorDemo {
    public static void main(String[] args) {
        TextView plain = new PlainTextView("Hello, world!");

        System.out.print("Plain: ");
        plain.render();
        System.out.println();

        System.out.print("Bold: ");
        TextView bold = new BoldDecorator(plain);
        bold.render();
        System.out.println();

        System.out.print("Italic + Bold: ");
        TextView italicBold = new ItalicDecorator(bold);
        italicBold.render();
        System.out.println();

        System.out.print("Underline + Italic + Bold: ");
        TextView fullStyle = new UnderlineDecorator(italicBold);
        fullStyle.render();
        System.out.println();
    }
}