package ridehailingservice.observer;

import ridehailingservice.entities.Trip;
import ridehailingservice.entities.User;

public class Rider extends User {
    public Rider(String name, String contact) {
        super(name, contact);
    }

    @Override
    public void onUpdate(Trip trip) {
        System.out.printf("--- Notification for Rider %s ---\n", getName());
        System.out.printf("  Trip %s is now %s.\n", trip.getId(), trip.getStatus());
        if (trip.getDriver() != null) {
            System.out.printf("  Driver: %s in a %s (%s)\n",
                    trip.getDriver().getName(), trip.getDriver().getVehicle().getModel(),
                    trip.getDriver().getVehicle().getLicenseNumber());
        }
        System.out.println("--------------------------------\n");
    }
}