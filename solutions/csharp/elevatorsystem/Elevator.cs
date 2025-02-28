using System;
using System.Collections.Generic;
using System.Threading;

namespace ElevatorSystem
{
    public class Elevator
    {
        private readonly int id;
        private readonly int capacity;
        private int currentFloor;
        private Direction currentDirection;
        private readonly List<Request> requests;

        public Elevator(int id, int capacity)
        {
            this.id = id;
            this.capacity = capacity;
            this.currentFloor = 1;
            this.currentDirection = Direction.UP;
            this.requests = new List<Request>();
        }

        public void AddRequest(Request request)
        {
            lock (requests)
            {
                if (requests.Count < capacity)
                {
                    requests.Add(request);
                    Console.WriteLine("Elevator " + id + " added request: Source " + request.SourceFloor + " -> Destination " + request.DestinationFloor);
                    Monitor.PulseAll(requests); // Notify waiting threads
                }
            }
        }

        public Request GetNextRequest()
        {
            lock (requests)
            {
                while (requests.Count == 0)
                {
                    try
                    {
                        Monitor.Wait(requests); // Wait for a new request
                    }
                    catch (ThreadInterruptedException e)
                    {
                        Console.WriteLine(e);
                    }
                }

                Request nextRequest = requests[0];
                requests.RemoveAt(0);
                return nextRequest;
            }
        }

        public void ProcessRequests()
        {
            while (true)
            {
                while (requests.Count > 0)
                {
                    Request request = GetNextRequest();
                    ProcessRequest(request);
                }

                lock (requests)
                {
                    try
                    {
                        Monitor.Wait(requests); // Wait for new requests
                    }
                    catch (ThreadInterruptedException e)
                    {
                        Console.WriteLine(e);
                    }
                }
            }
        }

        private void ProcessRequest(Request request)
        {
            int startFloor = currentFloor;
            int endFloor = request.DestinationFloor;

            if (startFloor < endFloor)
            {
                currentDirection = Direction.UP;
                for (int i = startFloor; i <= endFloor; i++)
                {
                    currentFloor = i;
                    Console.WriteLine("Elevator " + id + " reached floor " + currentFloor);
                    Thread.Sleep(1000); // Simulating elevator movement
                }
            }
            else if (startFloor > endFloor)
            {
                currentDirection = Direction.DOWN;
                for (int i = startFloor; i >= endFloor; i--)
                {
                    currentFloor = i;
                    Console.WriteLine("Elevator " + id + " reached floor " + currentFloor);
                    Thread.Sleep(1000); // Simulating elevator movement
                }
            }
        }

        public void Run()
        {
            ProcessRequests();
        }

        public int CurrentFloor
        {
            get { return currentFloor; }
        }
    }
}