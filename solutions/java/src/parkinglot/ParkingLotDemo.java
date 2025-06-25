package parkinglot;

import parkinglot.fee.VehicleBasedFeeStrategy;
import parkinglot.parkingspot.*;
import parkinglot.vehicle.*;
import java.util.List;

public class ParkingLotDemo {
    public static void run() {
        ParkingLot parkingLot = ParkingLot.getInstance();

        List<ParkingSpot> parkingSpotsFloor1 = List.of(
                ParkingSpotFactory.createParkingSpot(ParkingSpotType.BIKE, "101"),
                ParkingSpotFactory.createParkingSpot(ParkingSpotType.COMPACT, "102"),
                ParkingSpotFactory.createParkingSpot(ParkingSpotType.LARGE, "103")
        );

        List<ParkingSpot> parkingSpotsFloor2 = List.of(
                ParkingSpotFactory.createParkingSpot(ParkingSpotType.BIKE, "201"),
                ParkingSpotFactory.createParkingSpot(ParkingSpotType.LARGE, "202")
        );

        // Add a floor with different types of spots
        ParkingFloor floor1 = new ParkingFloor(1, parkingSpotsFloor1);
        ParkingFloor floor2 = new ParkingFloor(2, parkingSpotsFloor2);

        parkingLot.addFloor(floor1);
        parkingLot.addFloor(floor2);

        parkingLot.setFeeStrategy(new VehicleBasedFeeStrategy());

        // Create vehicles
        Vehicle car1 = new Car("ABC123");
        Vehicle car2 = new Car("XYZ789");
        Vehicle bike1 = new Bike("M1234");

        // Park vehicles
        try {
            ParkingTicket parkingTicket1 = parkingLot.parkVehicle(car1);
            System.out.println("Car 1 parked, Ticket Id: " + parkingTicket1.getTicketId());

            ParkingTicket parkingTicket2 = parkingLot.parkVehicle(car2);
            System.out.println("Car 2 parked, Ticket Id: " + parkingTicket2.getTicketId());

            ParkingTicket parkingTicket3 = parkingLot.parkVehicle(bike1);
            System.out.println("Bike 1 parked, Ticket Id: " + parkingTicket3.getTicketId());

            // Try parking another car when spots are full
            Vehicle car3 = new Car("DL0432");
            parkingLot.parkVehicle(car3);
        } catch (Exception e) {
            System.out.println("Exception: " + e.getMessage());
        }

        // Unpark vehicles
        try {
            double fee = parkingLot.unparkVehicle(car1.getLicenseNumber()); // valid ticket ID
            System.out.println("Vehicle: " + car1.getLicenseNumber() + ", Fee: " + fee);

            fee = parkingLot.unparkVehicle("1"); // invalid license number
        } catch (Exception e) {
            System.out.println("Exception while unparking: " + e.getMessage());
        }
    }
}
