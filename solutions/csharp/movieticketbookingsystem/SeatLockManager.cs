class SeatLockManager
{
    private readonly Dictionary<Show, Dictionary<Seat, string>> lockedSeats = new Dictionary<Show, Dictionary<Seat, string>>();
    private readonly object lockObj = new object();
    private const int LOCK_TIMEOUT_MS = 500; // 0.5 seconds

    public void LockSeats(Show show, List<Seat> seats, string userId)
    {
        lock (lockObj)
        {
            // Check if any of the requested seats are already locked or booked
            foreach (var seat in seats)
            {
                if (seat.GetStatus() != SeatStatus.AVAILABLE)
                {
                    Console.WriteLine($"Seat {seat.GetId()} is not available.");
                    return;
                }
            }

            // Lock the seats
            foreach (var seat in seats)
            {
                seat.SetStatus(SeatStatus.LOCKED);
            }

            if (!lockedSeats.ContainsKey(show))
            {
                lockedSeats[show] = new Dictionary<Seat, string>();
            }

            foreach (var seat in seats)
            {
                lockedSeats[show][seat] = userId;
            }

            // Schedule a task to unlock the seats after a timeout
            Task.Delay(LOCK_TIMEOUT_MS).ContinueWith(_ => UnlockSeats(show, seats, userId));

            Console.WriteLine($"Locked seats: {string.Join(", ", seats.Select(s => s.GetId()))} for user {userId}");
        }
    }

    public void UnlockSeats(Show show, List<Seat> seats, string userId)
    {
        lock (lockObj)
        {
            if (lockedSeats.TryGetValue(show, out var showLocks))
            {
                foreach (var seat in seats)
                {
                    if (showLocks.TryGetValue(seat, out var lockedUserId) && lockedUserId == userId)
                    {
                        showLocks.Remove(seat);
                        if (seat.GetStatus() == SeatStatus.LOCKED)
                        {
                            seat.SetStatus(SeatStatus.AVAILABLE);
                            Console.WriteLine($"Unlocked seat: {seat.GetId()} due to timeout.");
                        }
                        else
                        {
                            Console.WriteLine($"Unlocked seat: {seat.GetId()} due to booking completion.");
                        }
                    }
                }

                if (!showLocks.Any())
                {
                    lockedSeats.Remove(show);
                }
            }
        }
    }

    public void Shutdown()
    {
        Console.WriteLine("Shutting down SeatLockProvider scheduler.");
    }
}