import User from "./User";
import { v4 as uuidv4 } from "uuid";

export default class ActivityLog {
    private logId: string;
    private action: string;
    private performedBy: User;
    private timestamp: Date;

    constructor(action: string, performedBy: User) {
        this.logId = uuidv4();
        this.action = action;
        this.performedBy = performedBy;
        this.timestamp = new Date();
    }
}
