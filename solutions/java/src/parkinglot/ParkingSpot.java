package parkinglot;

import parkinglot.vehicletype.Vehicle;
import parkinglot.vehicletype.VehicleType;

public class ParkingSpot {
    private final int spotNumber;
    private final VehicleType vehicleType;
    private Vehicle vehicle;
    private boolean isOccupied;

    /**
     * Exp PL 01:
     * Objects state is comprised of all of the above variables.
     * So any access to these variables should be synchronized.
     */

    private Object lock = new Object();

    public ParkingSpot(int spotNumber, VehicleType vehicleType) {
        this.spotNumber = spotNumber;
        this.vehicleType = vehicleType;
        this.isOccupied = false;
    }

    public boolean isAvailable() {
        // sync on primitive(boolean) does not work. Hence use lock variable
        // Ideally i would have wanted to use isOccupied variable directly.
        // synchronized(this.isOccupied)
        // {
        // return !isOccupied;
        // }

        synchronized (lock) {
            return !isOccupied;
        }

    }

    public boolean park(Vehicle vehicle) {
        synchronized (lock) {
            // Check if the spot is already occupied or if the vehicle type does not match
            if (isOccupied || vehicle.getType() != vehicleType) {
                return false;
            }
            this.vehicle = vehicle;
            isOccupied = true;
        }
        return true;
    }

    public void unpark() {
        /**
         * See Exp PL 01
         */
        synchronized (lock) {
            vehicle = null;
            isOccupied = false;
        }

    }

    public VehicleType getVehicleType() {
        /**
         * See Exp PL 01
         */
        synchronized (lock) {
            return vehicleType;
        }
    }

    public Vehicle getVehicle() {
        /**
         * See Exp PL 01
         */
        synchronized(lock)
        {
            return vehicle;
        }
    }

    public int getSpotNumber() {
        /**
         * See Exp PL 01
         */
        synchronized (lock) {
            return spotNumber;
        }   
    }
}