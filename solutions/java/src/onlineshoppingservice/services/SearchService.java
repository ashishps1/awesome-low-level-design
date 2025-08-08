package onlineshoppingservice.services;

import onlineshoppingservice.enums.ProductCategory;
import onlineshoppingservice.models.Product;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class SearchService {
    private final Collection<Product> productCatalog;

    public SearchService(Collection<Product> productCatalog) { this.productCatalog = productCatalog; }

    public List<Product> searchByName(String name) {
        List<Product> result = new ArrayList<>();
        productCatalog.stream()
            .filter(p -> p.getName().toLowerCase().contains(name.toLowerCase()))
            .forEach(result::add);
        return result;
    }

    public List<Product> searchByCategory(ProductCategory category) {
        List<Product> result = new ArrayList<>();
        productCatalog.stream()
            .filter(p -> p.getCategory() == category)
            .forEach(result::add);
        return result;
    }
}
