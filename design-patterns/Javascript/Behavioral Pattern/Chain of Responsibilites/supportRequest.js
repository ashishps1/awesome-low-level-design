// Creating a chain for attaining support team

class supportHandler {
  constructor(nextHandler) {
    this.nextHandler = nextHandler;
  }

  // Method to handle the request
  handleRequest(request, type) {
    if (this.nextHandler) {
      console.log("Passing to the next executive team to resolve your issue");
      this.nextHandler.handleRequest(request, type);
    } else {
      console.log("No further handlers available to process the request.");
    }
  }
}

// First level internet support team for connection
class InternetConnectionTeam extends supportHandler {
  handleRequest(request, type) {
    if (request === "internet" && type === "newConnection") {
      console.log("Your newConnection request is taken. Thank you! 🙂");
    } else if (request === "internet" && type === "problem") {
      console.log(
        "Seems you have an issue; we will redirect to the support team"
      );
      super.handleRequest(request, type); // Transferring to the next team
    } else {
      console.log(
        "Unknown request type in InternetConnectionTeam. Passing to next team."
      );
      super.handleRequest(request, type); // Transfer to the next team
    }
  }
}

// Second level internet support team for problem
class InternetSupportTeam extends supportHandler {
  handleRequest(request, type) {
    if (request === "internet" && type === "problem") {
      console.log("Your internet request is taken. Thank you! 🙂");
    } else {
      console.log(
        "Unknown request type in InternetSupportTeam. Passing to next team."
      );
      super.handleRequest(request, type); // Transferring to the next team
    }
  }
}

// Third level connection
class PhoneConnectionTeam extends supportHandler {
  handleRequest(request, type) {
    if (request === "phone" && type === "newConnection") {
      console.log("Your newConnection request is taken. Thank you! 🙂");
    } else if (request === "phone" && type === "problem") {
      console.log(
        "Seems you have an issue; we will redirect to the support team"
      );
      super.handleRequest(request, type); // Transferring to the next team
    } else {
      console.log(
        "Unknown request type in PhoneConnectionTeam. Passing to next team."
      );
      super.handleRequest(request, type); // Transferring to the next team
    }
  }
}

// Last level phone support team for problem
class PhoneSupportTeam extends supportHandler {
  handleRequest(request, type) {
    if (request === "phone" && type === "problem") {
      console.log("Your phone request is taken. Thank you! 🙂");
    } else {
      console.log(
        "Unknown request type in PhoneSupportTeam. This is the last support level."
      );
    }
  }
}

// Main module export
module.exports = {
  InternetConnectionTeam,
  InternetSupportTeam,
  PhoneConnectionTeam,
  PhoneSupportTeam,
};
