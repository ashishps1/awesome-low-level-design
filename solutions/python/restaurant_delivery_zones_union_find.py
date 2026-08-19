"""
Restaurant Delivery Zones using Union-Find (Disjoint Set Union)
This implementation tracks restaurant openings in a city grid and manages delivery zones
using the Union-Find data structure for efficient connected component tracking.
"""

class CityGrid:
    """
    City Grid with restaurant tracking and delivery zone management
    
    Time Complexity Summary:
    - __init__: O(rows * cols) for initializing the grid and parent arrays
    - open_restaurant: O(α(n)) amortized, where α is inverse Ackermann (nearly constant)
    - count_open_restaurants: O(1)
    - block_has_open_restaurants: O(1)
    - count_delivery_zones: O(1)
    
    Space Complexity: O(rows * cols) for storing grid state and union-find structure
    """
    
    def __init__(self, rows, cols):
        """
        Initialize the city grid
        
        Time Complexity: O(rows * cols)
        Space Complexity: O(rows * cols)
        
        Args:
            rows: Number of rows in the grid
            cols: Number of columns in the grid
        """
        self.rows = rows
        self.cols = cols

        self.cnt = [[0] * cols for _ in range(rows)]     # restaurants per block
        self.active = [[False] * cols for _ in range(rows)]

        n = rows * cols
        self.parent = list(range(n))
        self.rank = [0] * n

        self.total_open = 0   # total restaurants opened (can be > active blocks)
        self.zones = 0        # number of connected components among active blocks

    def _id(self, r, c):
        """
        Convert 2D grid coordinates to 1D array index
        
        Time Complexity: O(1)
        Space Complexity: O(1)
        """
        return r * self.cols + c

    def _find(self, x):
        """
        Find the root/representative of the set containing x (with path compression)
        
        Time Complexity: O(α(n)) amortized, where α is inverse Ackermann function
        Space Complexity: O(1)
        """
        while self.parent[x] != x:
            self.parent[x] = self.parent[self.parent[x]]  # path compression
            x = self.parent[x]
        return x

    def _union(self, a, b):
        """
        Unite the sets containing a and b (union by rank)
        
        Time Complexity: O(α(n)) amortized
        Space Complexity: O(1)
        
        How it works:
        1. Find roots of both elements
        2. If already in same set, return False (no merge needed)
        3. Attach smaller rank tree under larger rank tree (keeps tree balanced)
        4. If ranks equal, increase rank of new root by 1
        
        Returns:
            True if a and b were in different sets (merge happened), False otherwise
        """
        root_a = self._find(a)
        root_b = self._find(b)
        
        # Already in same set - no merge needed
        if root_a == root_b:
            return False
        
        # Attach smaller rank tree under larger rank tree
        if self.rank[root_a] < self.rank[root_b]:
            self.parent[root_a] = root_b
        elif self.rank[root_a] > self.rank[root_b]:
            self.parent[root_b] = root_a
        else:
            # Equal ranks - make one root and increase its rank
            self.parent[root_b] = root_a
            self.rank[root_a] += 1
        
        return True

    def open_restaurant(self, r, c):
        """
        Opens ONE restaurant at position (r, c)
        
        Time Complexity: O(α(n)) amortized - dominated by union-find operations
        Space Complexity: O(1)
        
        Args:
            r: Row index
            c: Column index
        """
        if not (0 <= r < self.rows and 0 <= c < self.cols):
            return  # or raise ValueError

        self.cnt[r][c] += 1
        self.total_open += 1

        # If this block was already active, zones do not change
        if self.cnt[r][c] > 1:
            return

        # First restaurant in this block -> activate cell
        self.active[r][c] = True
        self.zones += 1  # new component initially

        cur = self._id(r, c)
        for dr, dc in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            nr, nc = r + dr, c + dc
            if 0 <= nr < self.rows and 0 <= nc < self.cols and self.active[nr][nc]:
                if self._union(cur, self._id(nr, nc)):
                    self.zones -= 1  # merged two zones

    def count_open_restaurants(self):
        """
        Get total count of open restaurants across all blocks
        
        Time Complexity: O(1)
        Space Complexity: O(1)
        
        Returns:
            Total number of open restaurants
        """
        return self.total_open

    def block_has_open_restaurants(self, r, c):
        """
        Check if a specific block has any open restaurants
        
        Time Complexity: O(1)
        Space Complexity: O(1)
        
        Args:
            r: Row index
            c: Column index
        
        Returns:
            True if block has at least one open restaurant, False otherwise
        """
        if not (0 <= r < self.rows and 0 <= c < self.cols):
            return False
        return self.cnt[r][c] > 0

    def count_delivery_zones(self):
        """
        Get the number of connected delivery zones
        
        Time Complexity: O(1)
        Space Complexity: O(1)
        
        Returns:
            Number of connected components (delivery zones)
        """
        return self.zones


# Example usage and testing
if __name__ == "__main__":
    print("=== Restaurant Delivery Zones Demo ===\n")
    
    # Create a 5x5 city grid
    city = CityGrid(5, 5)
    print(f"Created a {city.rows}x{city.cols} city grid\n")
    
    # Open some restaurants
    print("Opening restaurants:")
    city.open_restaurant(0, 0)
    print(f"✓ Opened restaurant at (0, 0)")
    print(f"  Total restaurants: {city.count_open_restaurants()}")
    print(f"  Delivery zones: {city.count_delivery_zones()}\n")
    
    city.open_restaurant(0, 1)
    print(f"✓ Opened restaurant at (0, 1) - adjacent to (0, 0)")
    print(f"  Total restaurants: {city.count_open_restaurants()}")
    print(f"  Delivery zones: {city.count_delivery_zones()} (merged into 1 zone)\n")
    
    city.open_restaurant(0, 2)
    print(f"✓ Opened restaurant at (0, 2) - adjacent to (0, 1)")
    print(f"  Total restaurants: {city.count_open_restaurants()}")
    print(f"  Delivery zones: {city.count_delivery_zones()}\n")
    
    city.open_restaurant(2, 2)
    print(f"✓ Opened restaurant at (2, 2) - separate location")
    print(f"  Total restaurants: {city.count_open_restaurants()}")
    print(f"  Delivery zones: {city.count_delivery_zones()} (new separate zone)\n")
    
    city.open_restaurant(4, 4)
    print(f"✓ Opened restaurant at (4, 4) - another separate location")
    print(f"  Total restaurants: {city.count_open_restaurants()}")
    print(f"  Delivery zones: {city.count_delivery_zones()}\n")
    
    # Open adjacent restaurant to merge zones
    city.open_restaurant(1, 2)
    print(f"✓ Opened restaurant at (1, 2) - connects to zone at (0, 2)")
    print(f"  Total restaurants: {city.count_open_restaurants()}")
    print(f"  Delivery zones: {city.count_delivery_zones()}\n")
    
    city.open_restaurant(2, 2)  # Second restaurant in same block
    print(f"✓ Opened another restaurant at (2, 2) - same block as before")
    print(f"  Total restaurants: {city.count_open_restaurants()}")
    print(f"  Delivery zones: {city.count_delivery_zones()} (no change in zones)\n")
    
    # Check specific blocks
    print("Block status checks:")
    print(f"Block (0, 0) has restaurants: {city.block_has_open_restaurants(0, 0)}")
    print(f"Block (2, 2) has restaurants: {city.block_has_open_restaurants(2, 2)}")
    print(f"Block (3, 3) has restaurants: {city.block_has_open_restaurants(3, 3)}")
    print()
    
    # Demonstrate zone merging
    print("Merging zones by connecting (1, 2) and (2, 2):")
    # They should already be connected if we add (2, 1)
    city.open_restaurant(2, 1)
    print(f"✓ Opened restaurant at (2, 1)")
    print(f"  Total restaurants: {city.count_open_restaurants()}")
    print(f"  Delivery zones: {city.count_delivery_zones()}\n")
    
    # Final summary
    print("=== Final Summary ===")
    print(f"Total restaurants opened: {city.count_open_restaurants()}")
    print(f"Total delivery zones: {city.count_delivery_zones()}")
    print()
    
    # Visualize the grid
    print("Grid Visualization (* = has restaurant, - = empty):")
    for r in range(city.rows):
        row_str = ""
        for c in range(city.cols):
            if city.block_has_open_restaurants(r, c):
                row_str += f"*({city.cnt[r][c]}) "
            else:
                row_str += "-   "
        print(f"Row {r}: {row_str}")
    print("\n(Numbers in parentheses show restaurant count per block)\n")
    
    print("\n=== Complexity Summary ===")
    print("Initialize grid: O(rows × cols) time, O(rows × cols) space")
    print("Open restaurant: O(α(n)) amortized time, O(1) space")
    print("Count restaurants: O(1) time, O(1) space")
    print("Check block: O(1) time, O(1) space")
    print("Count zones: O(1) time, O(1) space")
    print("\nwhere α(n) is the inverse Ackermann function (practically constant)")
