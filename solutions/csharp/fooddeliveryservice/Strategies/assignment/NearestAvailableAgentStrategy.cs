class NearestAvailableAgentStrategy : IDeliveryAssignmentStrategy
{
    public DeliveryAgent FindAgent(Order order, List<DeliveryAgent> availableAgents)
    {
        Address restaurantAddress = order.GetRestaurant().GetAddress();
        Address customerAddress = order.GetCustomer().GetAddress();

        return availableAgents
            .Where(agent => agent.IsAvailableAgent())
            .OrderBy(agent => CalculateTotalDistance(agent, restaurantAddress, customerAddress))
            .FirstOrDefault();
    }

    private double CalculateTotalDistance(DeliveryAgent agent, Address restaurantAddress, Address customerAddress)
    {
        double agentToRestaurantDist = agent.GetCurrentLocation().DistanceTo(restaurantAddress);
        double restaurantToCustomerDist = restaurantAddress.DistanceTo(customerAddress);
        return agentToRestaurantDist + restaurantToCustomerDist;
    }
}