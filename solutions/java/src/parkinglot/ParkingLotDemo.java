package parkinglot;

import parkinglot.vehicletype.Car;
import parkinglot.vehicletype.Motorcycle;
import parkinglot.vehicletype.Truck;
import parkinglot.vehicletype.Vehicle;

public class ParkingLotDemo {
    public static void run() {
        ParkingLot parkingLot = ParkingLot.getInstance();
        parkingLot.addLevel(new Level(1, 100));
        parkingLot.addLevel(new Level(2, 80));

        Vehicle car = new Car("ABC123");
        Vehicle truck = new Truck("XYZ789");
        Vehicle motorcycle = new Motorcycle("M1234");

        // Park vehicles
        Ticket ticket1 = parkingLot.parkVehicle(car);
        Ticket ticket2 = parkingLot.parkVehicle(truck);
        Ticket ticket3 = parkingLot.parkVehicle(motorcycle);

        if(ticket1 != null) {
            System.out.println("Car parked with ticket ID: " + ticket1.getTicketId());
        }
        if(ticket2 != null) {
            System.out.println("Truck parked with ticket ID: " + ticket2.getTicketId());
        }
        if(ticket3 != null) {
            System.out.println("Motorcycle parked with ticket ID: " + ticket3.getTicketId());
        }

        // Display availability
        parkingLot.displayAvailability();

        // Unpark vehicle
        parkingLot.unparkVehicle(motorcycle);

        // Display updated availability
        parkingLot.displayAvailability();
    }
}
