class SortByDueDate : TaskSortStrategy
{
    public override void Sort(List<Task> tasks)
    {
        tasks.Sort((a, b) => string.Compare(a.GetDueDate(), b.GetDueDate(), StringComparison.Ordinal));
    }
}