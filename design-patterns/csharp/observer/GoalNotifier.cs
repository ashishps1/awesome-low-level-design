using System;

namespace Observer
{
    public class GoalNotifier : IFitnessDataObserver
    {
        private const int STEPS_GOAL = 10000;
        private const int ACTIVE_MINUTES_GOAL = 30;
        private const int CALORIES_GOAL = 500;

        public void Update(FitnessData data)
        {
            if (data.Steps >= STEPS_GOAL)
            {
                Console.WriteLine($"GoalNotifier: Congratulations! You've reached your daily steps goal of {STEPS_GOAL} steps!");
            }

            if (data.ActiveMinutes >= ACTIVE_MINUTES_GOAL)
            {
                Console.WriteLine($"GoalNotifier: Great job! You've achieved your active minutes goal of {ACTIVE_MINUTES_GOAL} minutes!");
            }

            if (data.Calories >= CALORIES_GOAL)
            {
                Console.WriteLine($"GoalNotifier: Amazing! You've burned {CALORIES_GOAL} calories today!");
            }
        }
    }
} 