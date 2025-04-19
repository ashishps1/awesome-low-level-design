package parkinglot;

import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;



public class TicketManager {
    

    List<Ticket> tickets = new java.util.ArrayList<>();
    private static TicketManager instance;
    private static AtomicInteger ticketId  = new AtomicInteger(0);
    public static TicketManager getInstance() {
        if (instance == null) {
            instance = new TicketManager();
        }
        return instance;
    }

    public static synchronized Ticket getTicket(Ticket ticket) {
        ticketId.incrementAndGet();
        return new Ticket(ticketId, ticket);
    }


    public Ticket getTicket(int ticketId) {
        for (Ticket ticket : tickets) {
            if (ticket.getTicketId() == ticketId) {
                return ticket;
            }
        }
        return null;
    }
    public void addTicket(Ticket ticket) {
        tickets.add(ticket);
    }
    public void removeTicket(int ticketId) {
        Ticket ticket = getTicket(ticketId);
        if (ticket != null) {
            tickets.remove(ticket);
        }
    }
    public List<Ticket> getAllTickets() {
        return tickets;
    }

}

