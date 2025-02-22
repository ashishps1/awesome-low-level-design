package votingsystem;

import java.util.Date;

class VoteRecord {
    private final String voterId;
    private final String candidateId;
    private final long timestamp;

    public VoteRecord(String voterId, String candidateId, long timestamp) {
        this.voterId = voterId;
        this.candidateId = candidateId;
        this.timestamp = timestamp;
    }

    @Override
    public String toString() {
        return "Vote cast by " + voterId + " for candidate " + candidateId + 
               " at " + new Date(timestamp);
    }
}