import User from "./User";
import { VoteTypeEnum } from "./VoteTypeEnum";

export default class Vote {
  private voter: User;
  private type: VoteTypeEnum;

  constructor(voter: User, type: VoteTypeEnum) {
    this.voter = voter;
    this.type = type;
  }

  getVoter() {
    return this.voter;
  }

  getVoteType() {
    return this.type;
  }
}
