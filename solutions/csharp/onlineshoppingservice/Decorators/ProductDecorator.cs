abstract class ProductDecorator : Product
{
    protected Product decoratedProduct;

    public ProductDecorator(Product product)
    {
        decoratedProduct = product;
    }

    public override string GetId() { return decoratedProduct.GetId(); }
    public override string GetName() { return decoratedProduct.GetName(); }
    public override double GetPrice() { return decoratedProduct.GetPrice(); }
    public override string GetDescription() { return decoratedProduct.GetDescription(); }
    public override ProductCategory GetCategory() { return decoratedProduct.GetCategory(); }
}