package fooddeliveryservice

import (
	"fmt"
	"sync"
	"time"
)

type FoodDeliveryService struct {
	customers      map[string]*Customer
	restaurants    map[string]*Restaurant
	orders         map[string]*Order
	deliveryAgents map[string]*DeliveryAgent
	mu             sync.RWMutex
}

var (
	instance *FoodDeliveryService
	once     sync.Once
)

func GetFoodDeliveryService() *FoodDeliveryService {
	once.Do(func() {
		instance = &FoodDeliveryService{
			customers:      make(map[string]*Customer),
			restaurants:    make(map[string]*Restaurant),
			orders:         make(map[string]*Order),
			deliveryAgents: make(map[string]*DeliveryAgent),
		}
	})
	return instance
}

func (s *FoodDeliveryService) RegisterCustomer(customer *Customer) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.customers[customer.ID] = customer
}

func (s *FoodDeliveryService) RegisterRestaurant(restaurant *Restaurant) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.restaurants[restaurant.ID] = restaurant
}

func (s *FoodDeliveryService) RegisterDeliveryAgent(agent *DeliveryAgent) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.deliveryAgents[agent.ID] = agent
}

func (s *FoodDeliveryService) GetAvailableRestaurants() []*Restaurant {
	s.mu.RLock()
	defer s.mu.RUnlock()
	restaurants := make([]*Restaurant, 0, len(s.restaurants))
	for _, restaurant := range s.restaurants {
		restaurants = append(restaurants, restaurant)
	}
	return restaurants
}

func (s *FoodDeliveryService) GetRestaurantMenu(restaurantID string) []*MenuItem {
	s.mu.RLock()
	restaurant := s.restaurants[restaurantID]
	s.mu.RUnlock()

	if restaurant != nil {
		return restaurant.GetMenu()
	}
	return nil
}

func (s *FoodDeliveryService) PlaceOrder(customerID, restaurantID string, items []*OrderItem) (*Order, error) {
	s.mu.Lock()
	defer s.mu.Unlock()

	customer := s.customers[customerID]
	restaurant := s.restaurants[restaurantID]

	if customer == nil {
		return nil, fmt.Errorf("customer not found")
	}
	if restaurant == nil {
		return nil, fmt.Errorf("restaurant not found")
	}

	orderID := fmt.Sprintf("ORD%d", time.Now().UnixNano())
	order := NewOrder(orderID, customer, restaurant)

	for _, item := range items {
		order.AddItem(item)
	}

	s.orders[order.ID] = order
	s.notifyRestaurant(order)
	fmt.Printf("Order placed: %s\n", order.ID)
	return order, nil
}

func (s *FoodDeliveryService) UpdateOrderStatus(orderID string, status OrderStatus) error {
	s.mu.Lock()
	defer s.mu.Unlock()

	order := s.orders[orderID]
	if order == nil {
		return fmt.Errorf("order not found")
	}

	order.SetStatus(status)
	s.notifyCustomer(order)

	if status == OrderStatusConfirmed {
		s.assignDeliveryAgent(order)
	}
	return nil
}

func (s *FoodDeliveryService) CancelOrder(orderID string) error {
	s.mu.Lock()
	defer s.mu.Unlock()

	order := s.orders[orderID]
	if order == nil {
		return fmt.Errorf("order not found")
	}

	if order.GetStatus() != OrderStatusPending {
		return fmt.Errorf("cannot cancel order in current status")
	}

	order.SetStatus(OrderStatusCancelled)
	s.notifyCustomer(order)
	s.notifyRestaurant(order)
	fmt.Printf("Order cancelled: %s\n", order.ID)
	return nil
}

func (s *FoodDeliveryService) notifyCustomer(order *Order) {
	// TODO: Implement customer notification
	fmt.Printf("Notifying customer about order %s status: %s\n",
		order.ID, order.GetStatus())
}

func (s *FoodDeliveryService) notifyRestaurant(order *Order) {
	// TODO: Implement restaurant notification
	fmt.Printf("Notifying restaurant about order %s\n", order.ID)
}

func (s *FoodDeliveryService) notifyDeliveryAgent(order *Order) {
	// TODO: Implement delivery agent notification
	fmt.Printf("Notifying delivery agent about order %s\n", order.ID)
}

func (s *FoodDeliveryService) assignDeliveryAgent(order *Order) {
	for _, agent := range s.deliveryAgents {
		if agent.IsAvailable() {
			agent.SetAvailable(false)
			order.AssignDeliveryAgent(agent)
			s.notifyDeliveryAgent(order)
			break
		}
	}
}
