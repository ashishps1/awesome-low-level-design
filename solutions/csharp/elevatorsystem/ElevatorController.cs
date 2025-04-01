using System;
using System.Collections.Generic;
using System.Threading;

namespace ElevatorSystem
{
    public class ElevatorController
    {
        private readonly List<Elevator> elevators;

        public ElevatorController(int numElevators, int capacity)
        {
            elevators = new List<Elevator>();
            for (int i = 0; i < numElevators; i++)
            {
                Elevator elevator = new Elevator(i + 1, capacity);
                elevators.Add(elevator);
                new Thread(elevator.Run).Start(); // Start elevator thread
            }
        }

        public void RequestElevator(int sourceFloor, int destinationFloor)
        {
            Elevator optimalElevator = FindOptimalElevator(sourceFloor);
            if (optimalElevator != null)
            {
                optimalElevator.AddRequest(new Request(sourceFloor, destinationFloor));
            }
        }

        private Elevator FindOptimalElevator(int sourceFloor)
        {
            Elevator optimalElevator = null;
            int minDistance = int.MaxValue;

            foreach (Elevator elevator in elevators)
            {
                int distance = Math.Abs(sourceFloor - elevator.CurrentFloor);
                if (distance < minDistance)
                {
                    minDistance = distance;
                    optimalElevator = elevator;
                }
            }

            return optimalElevator;
        }
    }
}