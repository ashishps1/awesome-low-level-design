// Abstract Mediator
class Mediator {
  register(user) {
    throw new Error("Method 'register()' must be implemented");
  }

  send(message, user) {
    throw new Error("Method 'send()' must be implemented");
  }
}

// Concrete Mediator
class ChatRoom extends Mediator {
  constructor() {
    super();
    this.users = [];
  }

  register(user) {
    this.users.push(user);
  }

  send(message, from) {
    this.users.forEach((user) => {
      if (user !== from) {
        // send senderMessage only to other users
        user.receive(message, from);
      }
    });
  }
}

module.exports = ChatRoom;
