package linkedin;

import linkedin.entities.Member;
import linkedin.entities.Post;
import linkedin.services.ConnectionService;
import linkedin.services.NewsFeedService;
import linkedin.services.NotificationService;
import linkedin.services.SearchService;
import linkedin.strategy.ChronologicalSortStrategy;

import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class LinkedInSystem {
    private static volatile LinkedInSystem instance;

    // Data stores (simulating databases)
    private final Map<String, Member> members = new ConcurrentHashMap<>();

    // Services
    private final ConnectionService connectionService;
    private final NewsFeedService newsFeedService;
    private final SearchService searchService;

    private LinkedInSystem() {
        // Initialize services
        this.connectionService = new ConnectionService(new NotificationService());
        this.newsFeedService = new NewsFeedService();
        this.searchService = new SearchService(members.values());
    }

    public static LinkedInSystem getInstance() {
        if (instance == null) {
            synchronized (LinkedInSystem.class) {
                if (instance == null) {
                    instance = new LinkedInSystem();
                }
            }
        }
        return instance;
    }

    public void registerMember(Member member) {
        members.put(member.getId(), member);
        System.out.println("New member registered: " + member.getName());
    }

    public Member getMember(String name) {
        return members.values().stream().filter(m -> m.getName().equals(name)).findFirst().orElse(null);
    }

    public String sendConnectionRequest(Member from, Member to) {
        return connectionService.sendRequest(from, to);
    }

    public void acceptConnectionRequest(String requestId) {
        connectionService.acceptRequest(requestId);
    }

    public void createPost(String memberId, String content) {
        Member author = members.get(memberId);
        Post post = new Post(author, content);
        newsFeedService.addPost(author, post);
        System.out.printf("%s created a new post.%n", author.getName());
    }

    public Post getLatestPostByMember(String memberId) {
        List<Post> memberPosts = newsFeedService.getMemberPosts(members.get(memberId));
        if (memberPosts == null || memberPosts.isEmpty()) return null;
        return memberPosts.get(memberPosts.size() - 1);
    }

    public void viewNewsFeed(String memberId) {
        Member member = members.get(memberId);
        System.out.println("\n--- News Feed for " + member.getName() + " ---");
        // Using the default chronological strategy
        newsFeedService.displayFeedForMember(member, new ChronologicalSortStrategy());
    }

    public List<Member> searchMemberByName(String name) {
        return searchService.searchByName(name);
    }
}