using System;

namespace ChessGame
{
    public class InvalidMoveException : Exception
    {
        public InvalidMoveException(string message) : base(message) { }
    }
}