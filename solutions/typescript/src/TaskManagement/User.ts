import { v4 as uuidv4 } from "uuid";

export default class User {
  private id: string;
  private name: string;
  private email: string;

  constructor(name: string, email: string) {
    this.id = uuidv4();
    this.name = name;
    this.email = email;
  }

  getName() {
    return this.name;
  }

  getId() {
    return this.id;
  }

  getEmail() {
    return this.email;
  }
}
