class SortByPriority : TaskSortStrategy
{
    public override void Sort(List<Task> tasks)
    {
        // Higher priority comes first
        tasks.Sort((a, b) => b.GetPriority().CompareTo(a.GetPriority()));
    }
}