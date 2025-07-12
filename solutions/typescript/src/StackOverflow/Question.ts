import Answer from "./Answer";
import User from "./User";
import Vote from "./Vote";
import { VoteTypeEnum } from "./VoteTypeEnum";
import Comment from "./Comment";
import Tag from "./Tag";
import { v4 as uuidv4 } from "uuid";
import { ReputationTypeEnum } from "./ReputationType";

export default class Question {
  private id: string;
  private title: string;
  private content: string;
  private author: User;
  private creationDate: Date;
  private answers: Answer[];
  private comments: Comment[];
  private tags: Tag[];
  private votes: Vote[];
  private acceptedAnswer: Answer | null;

  constructor(author: User, title: string, content: string, tags: Tag[]) {
    this.id = uuidv4();
    this.author = author;
    this.title = title;
    this.content = content;
    this.creationDate = new Date();
    this.answers = [];
    this.votes = [];
    this.comments = [];
    this.tags = tags;
    this.acceptedAnswer = null;
  }

  addAnswer(answer: Answer) {
    this.answers.push(answer);
  }

  acceptAnswer(answer: Answer) {
    this.acceptedAnswer = answer;
  }

  vote(voter: User, type: VoteTypeEnum) {
    this.votes = this.votes.filter(
      (v) => v.getVoter().getUserId() != voter.getUserId(),
    );

    this.votes.push(new Vote(voter, type));
    this.author.updateReputation(
      type == VoteTypeEnum.UPVOTE
        ? ReputationTypeEnum.QUESTION_UPVOTE
        : ReputationTypeEnum.QUESTION_DOWNVOTE,
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

  getId() {
    return this.id;
  }
  getAuthor() {
    return this.author;
  }
  getTitle() {
    return this.title;
  }
  getContent() {
    return this.content;
  }
  getTags() {
    return this.tags;
  }
}
