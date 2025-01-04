const Phone = require("./context");

const {Ringing} = require("./state");

const phone = new Phone();

phone.alert(); // Output: Phone is idle.

phone.answer(); // Output: No incoming call to answer.
phone.setState(new Ringing());
phone.alert(); // Output: Phone is ringing...

phone.answer(); // Output: Answering the call.
phone.alert(); // Output: Phone is in a call.

phone.hangup(); // Output: Hanging up the call.
phone.alert(); // Output: Phone is idle.
