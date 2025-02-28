using System;

namespace ElevatorSystem
{
    public class ElevatorSystemDemo
    {
        public static void Run()
        {
            ElevatorController controller = new ElevatorController(3, 5);

            controller.RequestElevator(5, 10);
            controller.RequestElevator(3, 7);
            controller.RequestElevator(8, 2);
            controller.RequestElevator(1, 9);
        }
    }
}