import User from "./User";
import { VoteTypeEnum } from "./VoteTypeEnum";

export default interface Votable {
    vote(voter: User, type: VoteTypeEnum): void;
    getVoteCount(): number;
}
