using System;

namespace Observer
{
    public class LiveActivityDisplay : IFitnessDataObserver
    {
        public void Update(FitnessData data)
        {
            Console.WriteLine($"LiveActivityDisplay: Steps: {data.Steps}, " +
                            $"Active Minutes: {data.ActiveMinutes}, " +
                            $"Calories: {data.Calories}");
        }
    }
} 