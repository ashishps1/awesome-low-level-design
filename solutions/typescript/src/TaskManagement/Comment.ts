import User from "./User";
import { v4 as uuidv4 } from "uuid";

export default class Comment {
    private id: string;
    private content: string;
    private author: User;
    private timestamp: Date;

    constructor(content: string, author: User) {
        this.id = uuidv4();
        this.content = content;
        this.author = author;
        this.timestamp = new Date();
    }

    getAuthor() {
        return this.author;
    }
}
