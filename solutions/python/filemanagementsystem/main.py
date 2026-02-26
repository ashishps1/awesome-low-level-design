"""
File System Implementation using Trie Data Structure
This implementation supports adding files/directories, searching, and listing files
with autocomplete functionality.
"""

class FileSystemNode:
    """
    Node for the File System Trie
    Each node represents a character in a file/directory path
    """
    def __init__(self):
        self.children = {}  # Dictionary to store child nodes
        self.is_file = False  # True if this node marks end of a file path
        self.is_directory = False  # True if this node marks end of a directory path
        self.content = ""  # Store file content (optional)
        self.metadata = {}  # Store metadata like size, permissions, etc.


class FileSystemTrie:
    """
    File System implementation using Trie data structure
    Supports operations like adding files/directories, searching, and autocomplete
    """
    
    def __init__(self):
        self.root = FileSystemNode()
    
    
    def add_file(self, path: str, content: str = "") -> bool:
        """
        Add a file to the file system
        
        Time Complexity: O(n) where n is the length of the path
        Space Complexity: O(n) for storing the path in the trie
        
        Args:
            path: Full path of the file (e.g., "/home/user/file.txt")
            content: Optional content of the file
        
        Returns:
            True if file was added successfully, False otherwise
        """
        if not path or path[0] != '/':
            return False
        
        curr = self.root
        path = path[1:]  # Remove leading '/'
        
        for char in path:
            if char not in curr.children:
                curr.children[char] = FileSystemNode()
            curr = curr.children[char]
        
        curr.is_file = True
        curr.content = content
        return True
    
    
    def add_directory(self, path: str) -> bool:
        """
        Add a directory to the file system
        
        Time Complexity: O(n) where n is the length of the path
        Space Complexity: O(n) for storing the path in the trie
        
        Args:
            path: Full path of the directory (e.g., "/home/user/documents")
        
        Returns:
            True if directory was added successfully, False otherwise
        """
        if not path or path[0] != '/':
            return False
        
        curr = self.root
        path = path[1:]  # Remove leading '/'
        
        for char in path:
            if char not in curr.children:
                curr.children[char] = FileSystemNode()
            curr = curr.children[char]
        
        curr.is_directory = True
        return True
    
    
    def search_file(self, path: str) -> bool:
        """
        Check if a file exists in the file system
        
        Time Complexity: O(n) where n is the length of the path
        Space Complexity: O(1) - no extra space used
        
        Args:
            path: Full path of the file to search
        
        Returns:
            True if file exists, False otherwise
        """
        if not path or path[0] != '/':
            return False
        
        curr = self.root
        path = path[1:]
        
        for char in path:
            if char not in curr.children:
                return False
            curr = curr.children[char]
        
        return curr.is_file
    
    
    def search_directory(self, path: str) -> bool:
        """
        Check if a directory exists in the file system
        
        Time Complexity: O(n) where n is the length of the path
        Space Complexity: O(1) - no extra space used
        
        Args:
            path: Full path of the directory to search
        
        Returns:
            True if directory exists, False otherwise
        """
        if not path or path[0] != '/':
            return False
        
        curr = self.root
        path = path[1:]
        
        for char in path:
            if char not in curr.children:
                return False
            curr = curr.children[char]
        
        return curr.is_directory
    
    
    def path_exists(self, path: str) -> bool:
        """
        Check if a path (file or directory) exists
        
        Time Complexity: O(n) where n is the length of the path
        Space Complexity: O(1) - no extra space used
        
        Args:
            path: Full path to check
        
        Returns:
            True if path exists (as file or directory), False otherwise
        """
        if not path or path[0] != '/':
            return False
        
        curr = self.root
        path = path[1:]
        
        for char in path:
            if char not in curr.children:
                return False
            curr = curr.children[char]
        
        return curr.is_file or curr.is_directory
    
    
    def starts_with_prefix(self, prefix: str) -> bool:
        """
        Check if any path starts with the given prefix
        
        Time Complexity: O(n) where n is the length of the prefix
        Space Complexity: O(1) - no extra space used
        
        Args:
            prefix: Prefix to search for
        
        Returns:
            True if any path starts with prefix, False otherwise
        """
        if not prefix or prefix[0] != '/':
            return False
        
        curr = self.root
        prefix = prefix[1:]
        
        for char in prefix:
            if char not in curr.children:
                return False
            curr = curr.children[char]
        
        return True
    
    
    def autocomplete(self, prefix: str, limit: int = 10) -> list:
        """
        Get all paths that start with the given prefix (autocomplete functionality)
        
        Time Complexity: O(n + m*k) where n is prefix length, m is number of results, 
                         k is average path length
        Space Complexity: O(m*k) for storing the results
        
        Args:
            prefix: Prefix to search for
            limit: Maximum number of results to return
        
        Returns:
            List of paths that start with the prefix
        """
        if not prefix or prefix[0] != '/':
            return []
        
        curr = self.root
        prefix = prefix[1:]
        
        # Navigate to the prefix node
        for char in prefix:
            if char not in curr.children:
                return []
            curr = curr.children[char]
        
        # DFS to find all paths from this node
        results = []
        self._dfs_collect_paths(curr, "/" + prefix, results, limit)
        return results
    
    
    def _dfs_collect_paths(self, node: FileSystemNode, current_path: str, 
                           results: list, limit: int) -> None:
        """
        Helper function for DFS traversal to collect all paths
        
        Time Complexity: O(n*k) where n is number of nodes, k is path length
        Space Complexity: O(h) for recursion stack, where h is height of trie
        """
        if len(results) >= limit:
            return
        
        if node.is_file or node.is_directory:
            type_marker = " (file)" if node.is_file else " (dir)"
            results.append(current_path + type_marker)
        
        for char, child_node in node.children.items():
            self._dfs_collect_paths(child_node, current_path + char, results, limit)
    
    
    def list_directory(self, path: str) -> list:
        """
        List all files and directories directly under the given path
        
        Time Complexity: O(n + m) where n is path length, m is number of direct children
        Space Complexity: O(m) for storing the results
        
        Args:
            path: Directory path to list
        
        Returns:
            List of immediate children (files and directories)
        """
        if not path or path[0] != '/':
            return []
        
        curr = self.root
        path = path[1:]
        
        # Navigate to the directory node
        for char in path:
            if char not in curr.children:
                return []
            curr = curr.children[char]
        
        # Collect immediate children
        results = []
        self._collect_immediate_children(curr, "", results)
        return results
    
    
    def _collect_immediate_children(self, node: FileSystemNode, 
                                     current_segment: str, results: list) -> None:
        """
        Helper to collect immediate children of a directory
        
        Time Complexity: O(m*k) where m is number of children, k is segment length
        Space Complexity: O(1) excluding results storage
        """
        for char, child_node in node.children.items():
            new_segment = current_segment + char
            
            # Check if this is a complete entry (ends with / or is file)
            if child_node.is_file:
                results.append(new_segment + " (file)")
            elif child_node.is_directory:
                results.append(new_segment + " (dir)")
            else:
                # Continue building the segment name
                self._collect_immediate_children(child_node, new_segment, results)
    
    
    def delete_file(self, path: str) -> bool:
        """
        Delete a file from the file system
        
        Time Complexity: O(n) where n is the length of the path
        Space Complexity: O(1) - no extra space used
        
        Args:
            path: Full path of the file to delete
        
        Returns:
            True if file was deleted, False if not found
        """
        if not path or path[0] != '/':
            return False
        
        curr = self.root
        path = path[1:]
        
        for char in path:
            if char not in curr.children:
                return False
            curr = curr.children[char]
        
        if curr.is_file:
            curr.is_file = False
            curr.content = ""
            return True
        return False
    
    
    def get_file_content(self, path: str) -> str:
        """
        Retrieve the content of a file
        
        Time Complexity: O(n) where n is the length of the path
        Space Complexity: O(1) - no extra space used
        
        Args:
            path: Full path of the file
        
        Returns:
            Content of the file, or empty string if not found
        """
        if not path or path[0] != '/':
            return ""
        
        curr = self.root
        path = path[1:]
        
        for char in path:
            if char not in curr.children:
                return ""
            curr = curr.children[char]
        
        if curr.is_file:
            return curr.content
        return ""


# Example usage and testing
if __name__ == "__main__":
    fs = FileSystemTrie()
    
    print("=== File System Trie Demo ===\n")
    
    # Add some directories
    print("Adding directories:")
    fs.add_directory("/home")
    fs.add_directory("/home/user")
    fs.add_directory("/home/user/documents")
    fs.add_directory("/home/user/downloads")
    print("✓ Added /home, /home/user, /home/user/documents, /home/user/downloads\n")
    
    # Add some files
    print("Adding files:")
    fs.add_file("/home/user/file1.txt", "Hello World!")
    fs.add_file("/home/user/file2.py", "print('Python')")
    fs.add_file("/home/user/documents/doc1.txt", "Document content")
    fs.add_file("/home/user/downloads/image.jpg")
    print("✓ Added multiple files with content\n")
    
    # Search operations
    print("Search operations:")
    print(f"File '/home/user/file1.txt' exists: {fs.search_file('/home/user/file1.txt')}")
    print(f"File '/home/user/nonexistent.txt' exists: {fs.search_file('/home/user/nonexistent.txt')}")
    print(f"Directory '/home/user' exists: {fs.search_directory('/home/user')}")
    print(f"Path '/home/user/file1.txt' exists: {fs.path_exists('/home/user/file1.txt')}")
    print()
    
    # Prefix search
    print("Prefix search:")
    print(f"Paths starting with '/home/user': {fs.starts_with_prefix('/home/user')}")
    print(f"Paths starting with '/etc': {fs.starts_with_prefix('/etc')}")
    print()
    
    # Autocomplete
    print("Autocomplete for '/home/user/':")
    suggestions = fs.autocomplete("/home/user/", limit=10)
    for suggestion in suggestions:
        print(f"  - {suggestion}")
    print()
    
    # List directory
    print("Listing '/home/user/' directory:")
    contents = fs.list_directory("/home/user/")
    for item in contents:
        print(f"  - {item}")
    print()
    
    # Get file content
    print("File content:")
    content = fs.get_file_content("/home/user/file1.txt")
    print(f"Content of '/home/user/file1.txt': {content}")
    print()
    
    # Delete file
    print("Deleting file:")
    deleted = fs.delete_file("/home/user/file1.txt")
    print(f"Deleted '/home/user/file1.txt': {deleted}")
    print(f"File still exists: {fs.search_file('/home/user/file1.txt')}")
    print()
    
    print("\n=== Complexity Summary ===")
    print("Insert (add_file/add_directory): Time O(n), Space O(n)")
    print("Search (search_file/search_directory): Time O(n), Space O(1)")
    print("Prefix Search (starts_with_prefix): Time O(n), Space O(1)")
    print("Autocomplete: Time O(n + m*k), Space O(m*k)")
    print("List Directory: Time O(n + m), Space O(m)")
    print("Delete: Time O(n), Space O(1)")
    print("\nwhere n = path length, m = number of results, k = average path length")
