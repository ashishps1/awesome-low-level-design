using System.Collections.Concurrent;

class FoodDeliveryService
{
    private static volatile FoodDeliveryService instance;
    private static readonly object lockObject = new object();
    private readonly ConcurrentDictionary<string, Customer> customers = new ConcurrentDictionary<string, Customer>();
    private readonly ConcurrentDictionary<string, Restaurant> restaurants = new ConcurrentDictionary<string, Restaurant>();
    private readonly ConcurrentDictionary<string, DeliveryAgent> deliveryAgents = new ConcurrentDictionary<string, DeliveryAgent>();
    private readonly ConcurrentDictionary<string, Order> orders = new ConcurrentDictionary<string, Order>();
    private IDeliveryAssignmentStrategy assignmentStrategy;

    private FoodDeliveryService() { }

    public static FoodDeliveryService GetInstance()
    {
        if (instance == null)
        {
            lock (lockObject)
            {
                if (instance == null)
                    instance = new FoodDeliveryService();
            }
        }
        return instance;
    }

    public void SetAssignmentStrategy(IDeliveryAssignmentStrategy assignmentStrategy)
    {
        this.assignmentStrategy = assignmentStrategy;
    }

    public Customer RegisterCustomer(string name, string phone, Address address)
    {
        Customer customer = new Customer(name, phone, address);
        customers.TryAdd(customer.GetId(), customer);
        return customer;
    }

    public Restaurant RegisterRestaurant(string name, Address address)
    {
        Restaurant restaurant = new Restaurant(name, address);
        restaurants.TryAdd(restaurant.GetId(), restaurant);
        return restaurant;
    }

    public DeliveryAgent RegisterDeliveryAgent(string name, string phone, Address initialLocation)
    {
        DeliveryAgent deliveryAgent = new DeliveryAgent(name, phone, initialLocation);
        deliveryAgents.TryAdd(deliveryAgent.GetId(), deliveryAgent);
        return deliveryAgent;
    }

    public Order PlaceOrder(string customerId, string restaurantId, List<OrderItem> items)
    {
        if (!customers.TryGetValue(customerId, out Customer customer) ||
            !restaurants.TryGetValue(restaurantId, out Restaurant restaurant))
        {
            throw new KeyNotFoundException("Customer or Restaurant not found.");
        }

        Order order = new Order(customer, restaurant, items);
        orders.TryAdd(order.GetId(), order);
        customer.AddOrderToHistory(order);
        Console.WriteLine($"Order {order.GetId()} placed by {customer.GetName()} at {restaurant.GetName()}.");
        order.SetStatus(OrderStatus.PENDING);
        return order;
    }

    public void UpdateOrderStatus(string orderId, OrderStatus newStatus)
    {
        if (!orders.TryGetValue(orderId, out Order order))
        {
            throw new KeyNotFoundException("Order not found.");
        }

        order.SetStatus(newStatus);

        if (newStatus == OrderStatus.READY_FOR_PICKUP)
        {
            AssignDelivery(order);
        }
    }

    public void CancelOrder(string orderId)
    {
        if (!orders.TryGetValue(orderId, out Order order))
        {
            Console.WriteLine($"ERROR: Order with ID {orderId} not found.");
            return;
        }

        if (order.Cancel())
        {
            Console.WriteLine($"SUCCESS: Order {orderId} has been successfully canceled.");
        }
        else
        {
            Console.WriteLine($"FAILED: Order {orderId} could not be canceled. Its status is: {order.GetStatus()}");
        }
    }

    private void AssignDelivery(Order order)
    {
        List<DeliveryAgent> availableAgents = deliveryAgents.Values.ToList();

        DeliveryAgent agent = assignmentStrategy.FindAgent(order, availableAgents);
        if (agent != null)
        {
            order.AssignDeliveryAgent(agent);
            double distance = agent.GetCurrentLocation().DistanceTo(order.GetRestaurant().GetAddress());
            Console.WriteLine($"Agent {agent.GetName()} (dist: {distance:F2}) assigned to order {order.GetId()}.");
            order.SetStatus(OrderStatus.OUT_FOR_DELIVERY);
        }
        else
        {
            Console.WriteLine($"No available delivery agents found for order {order.GetId()}");
        }
    }

    public List<Restaurant> SearchRestaurants(List<IRestaurantSearchStrategy> strategies)
    {
        List<Restaurant> results = restaurants.Values.ToList();

        foreach (var strategy in strategies)
        {
            results = strategy.Filter(results);
        }

        return results;
    }

    public Menu GetRestaurantMenu(string restaurantId)
    {
        if (!restaurants.TryGetValue(restaurantId, out Restaurant restaurant))
        {
            throw new KeyNotFoundException($"Restaurant with ID {restaurantId} not found.");
        }
        return restaurant.GetMenu();
    }
}