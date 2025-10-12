import Comment from "./Comment";

export default interface Commentable {
    addComment(comment: Comment): void;
    getComments(): Comment[];
}
