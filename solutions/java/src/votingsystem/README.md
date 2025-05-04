# Voting System (LLD)

## Problem Statement

Design and implement a Voting System that allows voters to cast votes for candidates, ensures each voter can vote only once, and provides the ability to tally and display results.

---

## Requirements

- **Voter Registration:** The system manages a list of eligible voters.
- **Candidate Registration:** The system manages a list of candidates.
- **Vote Casting:** Each voter can cast a vote for a candidate, but only once.
- **Vote Recording:** The system records each vote and prevents duplicate voting.
- **Result Tallying:** The system can tally votes for each candidate and display the results.
- **Extensibility:** Easy to add new features such as multiple elections, voting rounds, or different voting methods.

---

## Core Entities

- **VotingSystem:** Main class that manages voters, candidates, vote casting, and result tallying.
- **Voter:** Represents a voter with a unique ID and name.
- **Candidate:** Represents a candidate with a unique ID and name.
- **VoteRecord:** Represents a record of a vote cast by a voter for a candidate.

---

## Class Design

### 1. VotingSystem
- **Fields:** Map<Integer, Voter> voters, Map<Integer, Candidate> candidates, Map<Integer, VoteRecord> voteRecords
- **Methods:** registerVoter(Voter), registerCandidate(Candidate), castVote(int voterId, int candidateId), tallyResults(), displayResults(), hasVoted(int voterId)

### 2. Voter
- **Fields:** int id, String name

### 3. Candidate
- **Fields:** int id, String name

### 4. VoteRecord
- **Fields:** int voterId, int candidateId

---

## Example Usage

```java
VotingSystem votingSystem = new VotingSystem();
votingSystem.registerVoter(new Voter(1, "Alice"));
votingSystem.registerVoter(new Voter(2, "Bob"));
votingSystem.registerCandidate(new Candidate(1, "John"));
votingSystem.registerCandidate(new Candidate(2, "Jane"));

votingSystem.castVote(1, 1); // Alice votes for John
votingSystem.castVote(2, 2); // Bob votes for Jane

votingSystem.displayResults();
```

---

## Demo

See `VotingSystemDemo.java` for a sample usage and simulation of the voting system.

---

## Extending the Design

- **Add multiple elections:** Support for different elections or voting rounds.
- **Add voting methods:** Implement ranked-choice, weighted voting, etc.
- **Add features:** Such as voter authentication, audit logs, or result export.

---