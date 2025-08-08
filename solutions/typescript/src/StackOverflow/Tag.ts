import { v4 as uuidv4 } from "uuid";

export default class Tag {
    private id: string;
    private name: string;

    constructor(name: string) {
        this.id = uuidv4();
        this.name = name;
    }

    getId() {
        return this.id;
    }
    getName() {
        return this.name;
    }
}
