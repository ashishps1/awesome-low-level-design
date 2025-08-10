abstract class NoteDispenser : IDispenseChain
{
    private IDispenseChain nextChain;
    private readonly int noteValue;
    private int numNotes;
    private readonly object dispenserLock = new object();

    public NoteDispenser(int noteValue, int numNotes)
    {
        this.noteValue = noteValue;
        this.numNotes = numNotes;
    }

    public void SetNextChain(IDispenseChain nextChain)
    {
        this.nextChain = nextChain;
    }

    public void Dispense(int amount)
    {
        lock (dispenserLock)
        {
            if (amount >= noteValue)
            {
                int numToDispense = Math.Min(amount / noteValue, numNotes);
                int remainingAmount = amount - (numToDispense * noteValue);

                if (numToDispense > 0)
                {
                    Console.WriteLine($"Dispensing {numToDispense} x ${noteValue} note(s)");
                    numNotes -= numToDispense;
                }

                if (remainingAmount > 0 && nextChain != null)
                {
                    nextChain.Dispense(remainingAmount);
                }
            }
            else if (nextChain != null)
            {
                nextChain.Dispense(amount);
            }
        }
    }

    public bool CanDispense(int amount)
    {
        lock (dispenserLock)
        {
            if (amount < 0) return false;
            if (amount == 0) return true;

            int numToUse = Math.Min(amount / noteValue, numNotes);
            int remainingAmount = amount - (numToUse * noteValue);

            if (remainingAmount == 0) return true;
            if (nextChain != null)
            {
                return nextChain.CanDispense(remainingAmount);
            }
            return false;
        }
    }
}