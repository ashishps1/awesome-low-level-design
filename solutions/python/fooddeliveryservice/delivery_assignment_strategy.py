from abc import ABC, abstractmethod
from typing import List, Optional
from order import Order
from delivery_agent import DeliveryAgent
from address import Address

class DeliveryAssignmentStrategy(ABC):
    @abstractmethod
    def find_agent(self, order: Order, agents: List[DeliveryAgent]) -> Optional[DeliveryAgent]:
        pass

class NearestAvailableAgentStrategy(DeliveryAssignmentStrategy):
    def find_agent(self, order: Order, available_agents: List[DeliveryAgent]) -> Optional[DeliveryAgent]:
        restaurant_address = order.get_restaurant().get_address()
        customer_address = order.get_customer().get_address()

        available_agents_filtered = [agent for agent in available_agents if agent.is_available_agent()]
        
        if not available_agents_filtered:
            return None

        min_distance = float('inf')
        best_agent = None

        for agent in available_agents_filtered:
            total_distance = self.calculate_total_distance(agent, restaurant_address, customer_address)
            if total_distance < min_distance:
                min_distance = total_distance
                best_agent = agent

        return best_agent

    def calculate_total_distance(self, agent: DeliveryAgent, restaurant_address: Address, customer_address: Address) -> float:
        agent_to_restaurant_dist = agent.get_current_location().distance_to(restaurant_address)
        restaurant_to_customer_dist = restaurant_address.distance_to(customer_address)
        return agent_to_restaurant_dist + restaurant_to_customer_dist