import User from "./User";
import { v4 as uuidv4 } from "uuid";

export default class Comment {
  private id: string;
  private content: string;
  private author: User;
  private creationDate: Date;

  constructor(author: User, content: string) {
    this.id = uuidv4();
    this.author = author;
    this.content = content;
    this.creationDate = new Date();
  }

  getId() {
    return this.id;
  }
  getAuthor() {
    return this.author;
  }
  getContent() {
    return this.content;
  }
}
