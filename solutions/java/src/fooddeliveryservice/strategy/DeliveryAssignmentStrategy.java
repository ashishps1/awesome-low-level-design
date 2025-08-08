package fooddeliveryservice.strategy;

import fooddeliveryservice.entity.DeliveryAgent;
import fooddeliveryservice.order.Order;

import java.util.List;
import java.util.Optional;

public interface DeliveryAssignmentStrategy {
    Optional<DeliveryAgent> findAgent(Order order, List<DeliveryAgent> agents);
}
