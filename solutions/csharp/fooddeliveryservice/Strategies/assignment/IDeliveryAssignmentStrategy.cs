interface IDeliveryAssignmentStrategy
{
    DeliveryAgent FindAgent(Order order, List<DeliveryAgent> agents);
}