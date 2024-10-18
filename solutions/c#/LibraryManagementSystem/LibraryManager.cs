using System;
using System.Collections.Generic;
using System.Linq;

namespace LibraryManagementSystem
{
    public class LibraryManager
    {
        private static LibraryManager instance;
        private readonly Dictionary<string, Book> catalog;
        private readonly Dictionary<string, Member> members;
        private readonly int MAX_BOOKS_PER_MEMBER = 5;
        private readonly int LOAN_DURATION_DAYS = 14;

        private LibraryManager()
        {
            catalog = new Dictionary<string, Book>();
            members = new Dictionary<string, Member>();
        }

        public static LibraryManager GetInstance()
        {
            if (instance == null)
            {
                instance = new LibraryManager();
            }
            return instance;
        }

        public void AddBook(Book book)
        {
            catalog[book.Isbn] = book;
        }

        public void RemoveBook(string isbn)
        {
            catalog.Remove(isbn);
        }

        public Book GetBook(string isbn)
        {
            catalog.TryGetValue(isbn, out Book book);
            return book;
        }

        public void RegisterMember(Member member)
        {
            members[member.MemberId] = member;
        }

        public void UnregisterMember(string memberId)
        {
            members.Remove(memberId);
        }

        public Member GetMember(string memberId)
        {
            members.TryGetValue(memberId, out Member member);
            return member;
        }

        public void BorrowBook(string memberId, string isbn)
        {
            Member member = GetMember(memberId);
            Book book = GetBook(isbn);

            if (member != null && book != null && book.IsAvailable)
            {
                if (member.BorrowedBooks.Count < MAX_BOOKS_PER_MEMBER)
                {
                    member.BorrowBook(book);
                    book.IsAvailable = false;
                    Console.WriteLine($"Book borrowed: {book.Title} by {member.Name}");
                }
                else
                {
                    Console.WriteLine($"Member {member.Name} has reached the maximum number of borrowed books.");
                }
            }
            else
            {
                Console.WriteLine("Book or member not found, or book is not available.");
            }
        }

        public void ReturnBook(string memberId, string isbn)
        {
            Member member = GetMember(memberId);
            Book book = GetBook(isbn);

            if (member != null && book != null)
            {
                member.ReturnBook(book);
                book.IsAvailable = true;
                Console.WriteLine($"Book returned: {book.Title} by {member.Name}");
            }
            else
            {
                Console.WriteLine("Book or member not found.");
            }
        }

        public List<Book> SearchBooks(string keyword)
        {
            return catalog.Values
                .Where(book => book.Title.Contains(keyword, StringComparison.OrdinalIgnoreCase) ||
                               book.Author.Contains(keyword, StringComparison.OrdinalIgnoreCase))
                .ToList();
        }
    }
}