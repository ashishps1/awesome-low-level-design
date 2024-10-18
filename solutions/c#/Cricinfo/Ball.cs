namespace Cricinfo
{
    public class Ball
    {
        private readonly int ballNumber;
        private readonly string bowler;
        private readonly string batsman;
        private readonly string result;

        public Ball(int ballNumber, string bowler, string batsman, string result)
        {
            this.ballNumber = ballNumber;
            this.bowler = bowler;
            this.batsman = batsman;
            this.result = result;
        }

        public int GetBallNumber()
        {
            return ballNumber;
        }

        public string GetBatsman()
        {
            return batsman;
        }

        public string GetBowler()
        {
            return bowler;
        }

        public string GetResult()
        {
            return result;
        }
    }
}