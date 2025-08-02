import { v4 as uuidv4 } from "uuid";

export default class User {
  private userId: string;
  private name: string;
  private email: string;
  private reputation: number;

  constructor(name: string, email: string) {
    this.userId = uuidv4();
    this.name = name;
    this.email = email;
    this.reputation = 0;
  }

  updateReputation(value: number) {
    this.reputation += value;
    if (this.reputation < 0) {
      this.reputation = 0;
    }
  }

  getUserId() {
    return this.userId;
  }
  getName() {
    return this.name;
  }
  getReputation() {
    return this.reputation;
  }
  getEmail() {
    return this.email;
  }
}
