package fooddeliveryservice.strategy;

import fooddeliveryservice.entity.Address;
import fooddeliveryservice.entity.DeliveryAgent;
import fooddeliveryservice.order.Order;

import java.util.Comparator;
import java.util.List;
import java.util.Optional;

public class NearestAvailableAgentStrategy implements DeliveryAssignmentStrategy {
    @Override
    public Optional<DeliveryAgent> findAgent(Order order, List<DeliveryAgent> availableAgents) {
        Address restaurantAddress = order.getRestaurant().getAddress();
        Address customerAddress = order.getCustomer().getAddress();

        // Find the agent with the minimum total travel distance (Agent -> Restaurant -> Customer)
        return availableAgents.stream()
                .filter(DeliveryAgent::isAvailable)
                .min(Comparator.comparingDouble(agent -> calculateTotalDistance(agent, restaurantAddress, customerAddress)));
    }

    private double calculateTotalDistance(DeliveryAgent agent, Address restaurantAddress, Address customerAddress) {
        double agentToRestaurantDist = agent.getCurrentLocation().distanceTo(restaurantAddress);
        double restaurantToCustomerDist = restaurantAddress.distanceTo(customerAddress);
        return agentToRestaurantDist + restaurantToCustomerDist;
    }
}