using System;

namespace Observer
{
    public class ProgressLogger : IFitnessDataObserver
    {
        public void Update(FitnessData data)
        {
            Console.WriteLine($"ProgressLogger: Logging progress — " +
                            $"Steps: {data.Steps}, " +
                            $"Active Minutes: {data.ActiveMinutes}, " +
                            $"Calories: {data.Calories}");
        }
    }
} 