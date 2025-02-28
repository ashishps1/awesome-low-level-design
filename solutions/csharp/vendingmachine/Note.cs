namespace VendingMachineApp
{
    public enum Note
    {
        One = 1,
        Five = 5,
        Ten = 10,
        Twenty = 20
    }

    public static class NoteExtensions
    {
        public static double GetValue(this Note note)
        {
            return (int)note;
        }
    }
}