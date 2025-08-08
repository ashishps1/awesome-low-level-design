package hotelmanagementsystem.specification;

public abstract class AbstractSpecification<T> implements Specification<T> {
    public Specification<T> and(Specification<T> other) {
        return new AndSpecification<>(this, other);
    }
}
