using System.Collections.Generic;

namespace OnlineShopping
{
    public class ShoppingCart
    {
        private readonly Dictionary<string, OrderItem> _items;

        public ShoppingCart()
        {
            _items = new Dictionary<string, OrderItem>();
        }

        public void AddItem(Product product, int quantity)
        {
            if (_items.ContainsKey(product.Id))
            {
                var existingItem = _items[product.Id];
                _items[product.Id] = new OrderItem(product, existingItem.Quantity + quantity);
            }
            else
            {
                _items[product.Id] = new OrderItem(product, quantity);
            }
        }

        public void RemoveItem(string productId)
        {
            _items.Remove(productId);
        }

        public void UpdateItemQuantity(string productId, int quantity)
        {
            if (_items.ContainsKey(productId))
            {
                var item = _items[productId];
                _items[productId] = new OrderItem(item.Product, quantity);
            }
        }

        public List<OrderItem> GetItems()
        {
            return new List<OrderItem>(_items.Values);
        }

        public void Clear()
        {
            _items.Clear();
        }
    }
}