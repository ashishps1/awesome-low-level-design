// Client code to handle users registration and messages communication

const User = require("./user");
const ChatRoom = require("./mediator");

// Object for chatRoom (mediator)
const chatRoom = new ChatRoom();

// Objects for users
const user1 = new User("User1", chatRoom);
const user2 = new User("User2", chatRoom);
const user3 = new User("User3", chatRoom);


// Register users with chatRoom
chatRoom.register(user1);
chatRoom.register(user2);
chatRoom.register(user3);

// Send message
user1.send("Hello everyone!");
user2.send("Hi User1!");
user3.send("Hi User2!");