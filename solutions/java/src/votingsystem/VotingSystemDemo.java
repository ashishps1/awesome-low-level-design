package votingsystem;

import java.util.*;
import java.util.concurrent.*;

class VotingSystemDemo {
    public static void main(String[] args) {
        VotingSystem votingSystem = VotingSystem.getInstance();

        votingSystem.registerCandidate("C1", "John Doe", "Party A");
        votingSystem.registerCandidate("C2", "Jane Smith", "Party B");

        for (int i = 1; i <= 100; i++) {
            votingSystem.registerVoter("V" + i, "Voter " + i, "pass" + i);
        }

        votingSystem.startVoting();

        ExecutorService executor = Executors.newFixedThreadPool(10);
        List<Future<Boolean>> futures = new ArrayList<>();

        for (int i = 1; i <= 100; i++) {
            final String voterId = "V" + i;
            final String candidateId = "C" + ((i % 2) + 1);

            futures.add(executor.submit(() -> {
                try {
                    Thread.sleep(new Random().nextInt(100));
                    return votingSystem.castVote(voterId, candidateId);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    return false;
                }
            }));
        }

        for (Future<Boolean> future : futures) {
            try {
                future.get();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        votingSystem.endVoting();

        Map<String, Integer> results = votingSystem.getCurrentResults();
        System.out.println("\nVoting Results:");
        results.forEach((candidate, votes) -> 
            System.out.println(candidate + ": " + votes + " votes"));

        System.out.println("\nAudit Log:");
        votingSystem.getAuditLog().forEach(System.out::println);

        executor.shutdown();
    }
}