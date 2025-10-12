package onlineshoppingservice.decorator;

import onlineshoppingservice.enums.ProductCategory;
import onlineshoppingservice.models.Product;

public abstract class ProductDecorator extends Product {
    protected Product decoratedProduct;

    public ProductDecorator(Product product) {
        this.decoratedProduct = product;
    }

    @Override public String getId() { return decoratedProduct.getId(); }

    @Override public String getName() { return decoratedProduct.getName(); }

    @Override public double getPrice() { return decoratedProduct.getPrice(); }

    @Override public String getDescription() { return decoratedProduct.getDescription(); }

    @Override public ProductCategory getCategory() { return decoratedProduct.getCategory(); }
}
