import time
import threading
from threading import Lock, RLock
from collections import deque

# Token Bucket
class TokenBucket:
    def __init__(self, capacity, refill_rate):
        self.capacity = capacity
        self.tokens = capacity
        self.refill_rate = refill_rate
        self.last_refill_time = time.time()
        self.lock = Lock()

    def refill(self):
        now = time.time()
        new_tokens = int((now - self.last_refill_time) * self.refill_rate)
        if new_tokens > 0:
            self.tokens = min(self.capacity, self.tokens + new_tokens)
            self.last_refill_time = now

    def allow_request(self):
        with self.lock:
            self.refill()
            if self.tokens > 0:
                self.tokens -= 1
                return True
            return False

# Leaky Bucket
class LeakyBucket:
    def __init__(self, capacity, leak_rate):
        self.capacity = capacity
        self.leak_rate = leak_rate
        self.requests = deque()
        self.lock = Lock()

    def allow_request(self):
        with self.lock:
            now = time.time()
            while self.requests and now - self.requests[0] >= 1.0 / self.leak_rate:
                self.requests.popleft()
            if len(self.requests) < self.capacity:
                self.requests.append(now)
                return True
            return False

# Fixed Window Counter
class FixedWindowCounter:
    def __init__(self, limit, window_size):
        self.limit = limit
        self.count = 0
        self.window_size = window_size
        self.window_start = time.time()
        self.lock = Lock()

    def allow_request(self):
        with self.lock:
            now = time.time()
            if now - self.window_start >= self.window_size:
                self.count = 0
                self.window_start = now
            if self.count < self.limit:
                self.count += 1
                return True
            return False

# Sliding Window Log
class SlidingWindowLog:
    def __init__(self, limit, window_size):
        self.limit = limit
        self.window_size = window_size
        self.requests = deque()
        self.lock = Lock()

    def allow_request(self):
        with self.lock:
            now = time.time()
            while self.requests and now - self.requests[0] >= self.window_size:
                self.requests.popleft()
            if len(self.requests) < self.limit:
                self.requests.append(now)
                return True
            return False

# Sliding Window Counter
class SlidingWindowCounter:
    def __init__(self, limit, window_size, num_buckets=10):
        self.limit = limit
        self.window_size = window_size
        self.num_buckets = num_buckets
        self.buckets = [0] * num_buckets
        self.current_bucket = 0
        self.start_time = time.time()
        self.lock = Lock()

    def get_current_time_in_seconds(self):
        return int(time.time())

    def shift_window(self):
        with self.lock:
            current_time = self.get_current_time_in_seconds()
            elapsed_buckets = (current_time % self.window_size) // (self.window_size // self.num_buckets)
            if elapsed_buckets != self.current_bucket:
                i = (self.current_bucket + 1) % self.num_buckets
                while i != (elapsed_buckets + 1) % self.num_buckets:
                    self.buckets[i] = 0
                    i = (i + 1) % self.num_buckets
                self.current_bucket = elapsed_buckets

    def allow_request(self):
        self.shift_window()
        with self.lock:
            if sum(self.buckets) >= self.limit:
                return False
            self.buckets[self.current_bucket] += 1
            return True

# Multithreaded Sliding Window Counter
class MultithreadedSlidingWindowCounter:
    def __init__(self, limit, window_size, num_buckets=10):
        self.limit = limit
        self.window_size = window_size
        self.num_buckets = num_buckets
        self.buckets = [0] * num_buckets
        self.current_bucket = 0
        self.start_time = time.time()
        self.rw_lock = RLock()

    def get_current_time_in_seconds(self):
        return int(time.time())

    def shift_window(self):
        with self.rw_lock:
            current_time = self.get_current_time_in_seconds()
            elapsed_buckets = (current_time % self.window_size) // (self.window_size // self.num_buckets)
            if elapsed_buckets != self.current_bucket:
                i = (self.current_bucket + 1) % self.num_buckets
                while i != (elapsed_buckets + 1) % self.num_buckets:
                    self.buckets[i] = 0
                    i = (i + 1) % self.num_buckets
                self.current_bucket = elapsed_buckets

    def allow_request(self):
        self.shift_window()
        with self.rw_lock:
            if sum(self.buckets) >= self.limit:
                return False
            self.buckets[self.current_bucket] += 1
            return True

# Test function
def test_rate_limiter(limiter, name):
    print(f"\nTesting {name} Rate Limiter:")
    for i in range(10):
        result = "✅ Allowed" if limiter.allow_request() else "❌ Blocked"
        print(f"Request {i+1}: {result}")
        time.sleep(0.2)

# Multithreaded test
def simulate_requests(limiter, thread_id):
    for i in range(5):
        result = "✅ Allowed" if limiter.allow_request() else "❌ Blocked"
        print(f"Thread {thread_id}: Request {i+1}: {result}")
        time.sleep(0.5)

# Main function
if __name__ == "__main__":
    # Initialize rate limiters with different configurations
    tb = TokenBucket(5, 2)  # 5 initial tokens, refills at 2 tokens/second
    lb = LeakyBucket(5, 1)  # 5 requests capacity, processes 1 request/second
    fw = FixedWindowCounter(5, 1)  # 5 requests per 1-second window
    swl = SlidingWindowLog(5, 10)  # 5 requests per 10-second sliding window
    swc = SlidingWindowCounter(5, 10)  # 5 requests per 10-second window with 10 buckets
    mt_swc = MultithreadedSlidingWindowCounter(10, 10)  # 10 requests per 10-second window, thread-safe

    # Expected output for Token Bucket:
    # First 5 requests will be allowed (initial tokens)
    # Then with 0.2s between requests and refill rate of 2/s, expect ~0.4 tokens per interval
    # So roughly every other request after the first 5 should be allowed
    test_rate_limiter(tb, "Token Bucket")

    # Expected output for Leaky Bucket:
    # First 5 requests will be allowed (up to capacity)
    # Then only 1 request per second is allowed (our leak rate)
    # With requests every 0.2s, most requests after initial 5 should be blocked
    test_rate_limiter(lb, "Leaky Bucket")

    # Expected output for Fixed Window:
    # First 5 requests in the 1-second window will be allowed
    # All subsequent requests in that window will be blocked
    # If test runs over 1 second, window resets and allows 5 more
    test_rate_limiter(fw, "Fixed Window Counter")

    # Expected output for Sliding Window Log:
    # First 5 requests will be allowed, then all blocked
    # Since window is 10s and test runs ~2s, we won't see enough sliding to allow more
    test_rate_limiter(swl, "Sliding Window Log")

    # Expected output for Sliding Window Counter:
    # Similar to Sliding Window Log, first 5 allowed then rest blocked
    # The 10-second window won't slide enough during our short test
    test_rate_limiter(swc, "Sliding Window Counter")

    # Expected output for Multithreaded test:
    # With limit of 10 and 15 total requests (3 threads x 5 requests each)
    # First 10 requests across all threads should be allowed
    # Last 5 requests should be blocked, regardless of which thread they're from
    print("\nTesting Multithreaded Sliding Window Counter:")
    threads = []
    for i in range(1, 4):
        t = threading.Thread(target=simulate_requests, args=(mt_swc, i))
        threads.append(t)
        t.start()
    for t in threads:
        t.join()
