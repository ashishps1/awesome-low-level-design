using System.Collections.Generic;

namespace LibraryManagementSystem
{
    public class Member
    {
        public string MemberId { get; }
        public string Name { get; }
        public string ContactInfo { get; }
        public List<Book> BorrowedBooks { get; }

        public Member(string memberId, string name, string contactInfo)
        {
            MemberId = memberId;
            Name = name;
            ContactInfo = contactInfo;
            BorrowedBooks = new List<Book>();
        }

        public void BorrowBook(Book book)
        {
            BorrowedBooks.Add(book);
        }

        public void ReturnBook(Book book)
        {
            BorrowedBooks.Remove(book);
        }
    }
}