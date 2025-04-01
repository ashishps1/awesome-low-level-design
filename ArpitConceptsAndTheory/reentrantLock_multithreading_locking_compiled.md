# Java Concurrency and Transactional Concepts

## 1. Reentrant Locks

**Explanation:**
A `ReentrantLock` is part of `java.util.concurrent.locks` and provides more flexibility than `synchronized` blocks. It allows the same thread to acquire the lock multiple times without causing a deadlock. This is useful in recursive methods.

**Example Code:**
```java
import java.util.concurrent.locks.ReentrantLock;

public class ReentrantLockExample {
    private final ReentrantLock lock = new ReentrantLock();
    private int count = 0;

    public void increment() {
        lock.lock();
        try {
            count++;
            System.out.println(Thread.currentThread().getName() + " Count: " + count);
        } finally {
            lock.unlock();
        }
    }

    public static void main(String[] args) {
        ReentrantLockExample example = new ReentrantLockExample();
        Runnable task = example::increment;

        Thread t1 = new Thread(task, "Thread-1");
        Thread t2 = new Thread(task, "Thread-2");

        t1.start();
        t2.start();
    }
}
```

**Follow-up Questions:**
- What are the differences between `ReentrantLock` and `synchronized`?
- How do you handle fairness in `ReentrantLock`? (`new ReentrantLock(true)` for fair lock)
- What is `tryLock()` and when would you use it?

---

## 2. CountDownLatch

**Explanation:**
`CountDownLatch` is used to make a thread wait until a set of operations being performed by other threads are completed. It's initialized with a count, which decrements every time `countDown()` is called. When it reaches zero, the waiting threads are released.

**Example Code:**
```java
import java.util.concurrent.CountDownLatch;

public class CountDownLatchExample {
    public static void main(String[] args) throws InterruptedException {
        CountDownLatch latch = new CountDownLatch(3);

        Runnable task = () -> {
            System.out.println(Thread.currentThread().getName() + " finished.");
            latch.countDown();
        };

        new Thread(task, "Thread-1").start();
        new Thread(task, "Thread-2").start();
        new Thread(task, "Thread-3").start();

        latch.await(); // Main thread waits here
        System.out.println("All tasks are completed.");
    }
}
```

**Follow-up Questions:**
- How is `CountDownLatch` different from `CyclicBarrier`?
- Can `CountDownLatch` be reused? (No, for reuse, use `CyclicBarrier`)
- How do you handle timeouts in `await()`?

---

## 3. @Transactional Annotation

**Explanation:**
`@Transactional` in Spring manages transactions automatically. When applied to a method, Spring creates a transaction before the method execution and commits it after completion or rolls back on exceptions.

**Example Code:**
```java
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

@Service
public class TransactionalExampleService {

    @Autowired
    private UserRepository userRepository;

    @Transactional
    public void saveUser(User user) {
        userRepository.save(user);
        // Simulate an error to trigger rollback
        if (user.getName() == null) {
            throw new RuntimeException("Name cannot be null");
        }
    }
}
```

**Follow-up Questions:**
- What are the isolation levels in transactions?
- When does `@Transactional` not work as expected? (e.g., private methods, self-invocation)
- How do you handle read-only transactions? (`@Transactional(readOnly = true)`)
- How does `@Transactional(propagation = Propagation.REQUIRES_NEW)` work?

---

## 4. Asynchronous Processing

**Explanation:**
Asynchronous processing allows non-blocking execution. In Spring, `@Async` is used to run a method asynchronously. Requires `@EnableAsync` and an `Executor` bean.

**Example Code:**
```java
import org.springframework.scheduling.annotation.Async;
import org.springframework.scheduling.annotation.EnableAsync;
import org.springframework.stereotype.Service;
import java.util.concurrent.CompletableFuture;

@Service
@EnableAsync
public class AsyncExampleService {

    @Async
    public CompletableFuture<String> process() throws InterruptedException {
        Thread.sleep(1000);
        System.out.println("Processing in thread: " + Thread.currentThread().getName());
        return CompletableFuture.completedFuture("Task Completed");
    }
}
```

**Follow-up Questions:**
- What is the default thread pool for `@Async`?
- How do you handle exceptions in asynchronous methods? (`AsyncUncaughtExceptionHandler`)
- How do you configure custom executors in Spring?

---

## General Interview Tips
- Be prepared to write thread-safe code using locks and synchronization.
- Understand transactional behavior, especially around rollback scenarios.
- Explain scenarios where asynchronous processing improves performance and where it doesn't.
- Discuss the impact of multi-threading on database transactions (e.g., deadlocks, consistency issues).

