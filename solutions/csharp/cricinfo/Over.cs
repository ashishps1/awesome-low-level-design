using System;
using System.Collections.Generic;

namespace Cricinfo
{
    public class Over
    {
        private readonly int overNumber;
        private readonly List<Ball> balls;

        public Over(int overNumber)
        {
            this.overNumber = overNumber;
            this.balls = new List<Ball>();
        }

        public void AddBall(Ball ball)
        {
            this.balls.Add(ball);
        }

        public int GetOverNumber()
        {
            return overNumber;
        }

        public List<Ball> GetBalls()
        {
            return balls;
        }
    }
}