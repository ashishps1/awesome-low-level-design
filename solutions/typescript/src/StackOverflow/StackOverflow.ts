import Answer from "./Answer";
import Comment from "./Comment";
import Commentable from "./Commentable";
import Question from "./Question";
import Tag from "./Tag";
import User from "./User";
import Votable from "./Votable";
import { VoteTypeEnum } from "./VoteTypeEnum";

export default class StackOverflow {
  private static instance: StackOverflow;
  private users: Map<String, User>;
  private questions: Map<String, Question>;
  private answers: Map<String, Answer>;
  private tags: Map<String, Tag>;

  private constructor() {
    this.users = new Map();
    this.questions = new Map();
    this.answers = new Map();
    this.tags = new Map();
  }

  static getInstance() {
    if (StackOverflow.instance == null) {
      StackOverflow.instance = new StackOverflow();
    }
    return StackOverflow.instance;
  }

  createUser(username: string, email: string) {
    const user = new User(username, email);
    this.users.set(user.getUserId(), user);
    return user;
  }

  postQuestion(
    userId: string,
    title: string,
    content: string,
    questionTags: string[],
  ) {
    const author = this.getUser(userId);

    const tagList = [];
    for (const qTag of questionTags) {
      let tag = this.tags.get(qTag); // Check if tag already exists
      if (!tag) {
        tag = new Tag(qTag); // Create new Tag if not found
      }
      tagList.push(tag);
      this.tags.set(tag.getId(), tag);
    }
    const question = new Question(author, title, content, tagList);
    this.questions.set(question.getId(), question);
    return question;
  }

  postAnswer(userId: string, questionId: string, content: string) {
    const author = this.getUser(userId);
    const question = this.questions.get(questionId);
    if (!question) throw new Error("Question Does Not Exist");

    const answer = new Answer(author, question, content);
    question.addAnswer(answer);
    this.answers.set(answer.getId(), answer);
    return answer;
  }

  getUser(userId: string) {
    const user = this.users.get(userId);
    if (!user) throw new Error("User Does Not Exist");

    return user;
  }

  addComment(userId: string, commentable: Commentable, content: string) {
    const author = this.getUser(userId);
    const comment = new Comment(author, content);
    commentable.addComment(new Comment(author, content));
    return comment;
  }

  vote(userId: string, votable: Votable, voteType: VoteTypeEnum) {
    const user = this.getUser(userId);
    votable.vote(user, voteType);
  }

  acceptAnswer(answerId: string) {
    const answer = this.answers.get(answerId);
    if (!answer) throw new Error("Answer Not Found");

    const question = answer.getQuestion();
    answer.markAsAccepted();
    question.acceptAnswer(answer);
  }

  searchQuestions(query: string) {
    const lowerQuery = query.toLowerCase();

    return [...this.questions.values()].filter(
      (q) =>
        q.getTitle().toLowerCase().includes(lowerQuery) ||
        q.getContent().toLowerCase().includes(lowerQuery) ||
        q.getTags().some((t) => t.getName().toLowerCase() === lowerQuery),
    );
  }

  getQuestionsByUser(userId: string) {
    return [...this.questions.values()].filter(
      (q) => q.getAuthor().getUserId() === userId,
    );
  }
}
