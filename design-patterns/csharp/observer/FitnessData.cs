using System;
using System.Collections.Generic;

namespace Observer
{
    public class FitnessData : IFitnessDataSubject
    {
        private int steps;
        private int activeMinutes;
        private int calories;

        private readonly List<IFitnessDataObserver> observers = new List<IFitnessDataObserver>();

        public void RegisterObserver(IFitnessDataObserver observer)
        {
            observers.Add(observer);
        }

        public void RemoveObserver(IFitnessDataObserver observer)
        {
            observers.Remove(observer);
        }

        public void NotifyObservers()
        {
            foreach (var observer in observers)
            {
                observer.Update(this);
            }
        }

        public void NewFitnessDataPushed(int steps, int activeMinutes, int calories)
        {
            this.steps = steps;
            this.activeMinutes = activeMinutes;
            this.calories = calories;

            Console.WriteLine($"\nFitnessData: New data received — Steps: {steps}, " +
                            $"Active Minutes: {activeMinutes}, Calories: {calories}");
            NotifyObservers();
        }

        public void DailyReset()
        {
            this.steps = 0;
            this.activeMinutes = 0;
            this.calories = 0;
            Console.WriteLine("\nFitnessData: Daily reset performed.");
            NotifyObservers();
        }

        // Properties
        public int Steps => steps;
        public int ActiveMinutes => activeMinutes;
        public int Calories => calories;
    }
} 