import { v4 as uuidv4 } from "uuid";
import User from "./User";
import Question from "./Question";
import Comment from "./Comment";
import Vote from "./Vote";
import Votable from "./Votable";
import Commentable from "./Commentable";
import { VoteTypeEnum } from "./VoteTypeEnum";
import { ReputationTypeEnum } from "./ReputationType";

export default class Answer implements Votable, Commentable {
  private id: string;
  private content: string;
  private author: User;
  private question: Question;
  private isAccepted: boolean;
  private creationDate: Date;
  private comments: Comment[];
  private votes: Vote[];

  constructor(author: User, question: Question, content: string) {
    this.id = uuidv4();
    this.author = author;
    this.question = question;
    this.content = content;
    this.creationDate = new Date();
    this.votes = [];
    this.comments = [];
    this.isAccepted = false;
  }

  vote(voter: User, type: VoteTypeEnum) {
    this.votes = this.votes.filter(
      (v) => v.getVoter().getUserId() != voter.getUserId(),
    );
    this.votes.push(new Vote(voter, type));
    this.author.updateReputation(
      type == VoteTypeEnum.UPVOTE
        ? ReputationTypeEnum.ANSWER_UPVOTE
        : ReputationTypeEnum.ANSWER_DOWNVOTE,
    );
  }

  getVoteCount() {
    return this.votes.reduce((sum, vote) => sum + vote.getVoteType(), 0);
  }

  addComment(comment: Comment) {
    this.comments.push(comment);
  }

  getComments() {
    return this.comments;
  }

  getQuestion() {
    return this.question;
  }

  markAsAccepted() {
    if (this.isAccepted) {
      throw new Error("This answer is already accepted");
    }
    this.isAccepted = true;
    this.author.updateReputation(ReputationTypeEnum.ANSWER_ACCEPTED);
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
  getIsAccepted() {
    return this.isAccepted;
  }
}
