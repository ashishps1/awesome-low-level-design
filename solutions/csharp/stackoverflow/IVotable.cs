namespace StackOverflow
{
    public interface IVotable
    {
        void Vote(User user, int value);
        int GetVoteCount();
    }
}