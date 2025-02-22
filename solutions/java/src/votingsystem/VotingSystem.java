package votingsystem;

import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class VotingSystem {
    private static volatile VotingSystem instance;
    private final Map<String, Voter> voters;
    private final Map<String, Candidate> candidates;
    private final Map<String, AtomicInteger> voteCount;
    private final Set<String> votedVoters;
    private final ReadWriteLock votingLock;
    private volatile boolean isVotingOpen;
    private final BlockingQueue<VoteRecord> voteAuditLog;

    private VotingSystem() {
        this.voters = new ConcurrentHashMap<>();
        this.candidates = new ConcurrentHashMap<>();
        this.voteCount = new ConcurrentHashMap<>();
        this.votedVoters = ConcurrentHashMap.newKeySet();
        this.votingLock = new ReentrantReadWriteLock();
        this.voteAuditLog = new LinkedBlockingQueue<>();
        this.isVotingOpen = false;
    }

    public static VotingSystem getInstance() {
        VotingSystem result = instance;
        if (result == null) {
            synchronized (VotingSystem.class) {
                if (result == null) {
                    instance = result = new VotingSystem();
                }
            }
        }
        return result;
    }

    public void registerVoter(String voterId, String name, String password) {
        Voter voter = new Voter(voterId, name, password);
        voters.putIfAbsent(voterId, voter);
    }

    public void registerCandidate(String candidateId, String name, String party) {
        Candidate candidate = new Candidate(candidateId, name, party);
        candidates.putIfAbsent(candidateId, candidate);
        voteCount.putIfAbsent(candidateId, new AtomicInteger(0));
    }

    public void startVoting() {
        votingLock.writeLock().lock();
        try {
            isVotingOpen = true;
            System.out.println("Voting has started!");
        } finally {
            votingLock.writeLock().unlock();
        }
    }

    public void endVoting() {
        votingLock.writeLock().lock();
        try {
            isVotingOpen = false;
            System.out.println("Voting has ended!");
        } finally {
            votingLock.writeLock().unlock();
        }
    }

    public boolean castVote(String voterId, String candidateId) {
        votingLock.readLock().lock();
        try {
            if (!isVotingOpen) {
                System.out.println("Voting is not open!");
                return false;
            }

            Voter voter = voters.get(voterId);
            Candidate candidate = candidates.get(candidateId);
            
            if (voter == null || candidate == null) {
                System.out.println("Invalid voter or candidate ID!");
                return false;
            }

            if (!votedVoters.add(voterId)) {
                System.out.println("Voter has already cast their vote!");
                return false;
            }

            voteCount.get(candidateId).incrementAndGet();
            
            voteAuditLog.offer(new VoteRecord(voterId, candidateId, System.currentTimeMillis()));
            
            return true;
        } finally {
            votingLock.readLock().unlock();
        }
    }

    public Map<String, Integer> getCurrentResults() {
        Map<String, Integer> results = new HashMap<>();
        votingLock.readLock().lock();
        try {
            for (Map.Entry<String, AtomicInteger> entry : voteCount.entrySet()) {
                results.put(candidates.get(entry.getKey()).getName(), 
                           entry.getValue().get());
            }
            return results;
        } finally {
            votingLock.readLock().unlock();
        }
    }

    public List<VoteRecord> getAuditLog() {
        return new ArrayList<>(voteAuditLog);
    }
}