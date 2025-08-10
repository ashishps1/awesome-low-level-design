using System.Collections.Concurrent;

class ParkingLot
{
    private static ParkingLot instance;
    private static readonly object instanceLock = new object();
    private readonly List<ParkingFloor> floors;
    private readonly ConcurrentDictionary<string, ParkingTicket> activeTickets;
    private IFeeStrategy feeStrategy;
    private IParkingStrategy parkingStrategy;
    private readonly object mainLock = new object();

    private ParkingLot()
    {
        floors = new List<ParkingFloor>();
        activeTickets = new ConcurrentDictionary<string, ParkingTicket>();
        feeStrategy = new FlatRateFeeStrategy();
        parkingStrategy = new NearestFirstStrategy();
    }

    public static ParkingLot GetInstance()
    {
        if (instance == null)
        {
            lock (instanceLock)
            {
                if (instance == null)
                {
                    instance = new ParkingLot();
                }
            }
        }
        return instance;
    }

    public void AddFloor(ParkingFloor floor)
    {
        floors.Add(floor);
    }

    public void SetFeeStrategy(IFeeStrategy feeStrategy)
    {
        this.feeStrategy = feeStrategy;
    }

    public void SetParkingStrategy(IParkingStrategy parkingStrategy)
    {
        this.parkingStrategy = parkingStrategy;
    }

    public ParkingTicket ParkVehicle(Vehicle vehicle)
    {
        lock (mainLock)
        {
            var spot = parkingStrategy.FindSpot(floors, vehicle);
            if (spot != null)
            {
                spot.ParkVehicle(vehicle);
                var ticket = new ParkingTicket(vehicle, spot);
                activeTickets.TryAdd(vehicle.GetLicenseNumber(), ticket);
                Console.WriteLine($"Vehicle {vehicle.GetLicenseNumber()} parked at spot {spot.GetSpotId()}");
                return ticket;
            }
            else
            {
                Console.WriteLine($"No available spot for vehicle {vehicle.GetLicenseNumber()}");
                return null;
            }
        }
    }

    public double? UnparkVehicle(string licenseNumber)
    {
        lock (mainLock)
        {
            if (!activeTickets.TryRemove(licenseNumber, out ParkingTicket ticket))
            {
                Console.WriteLine($"Ticket not found for vehicle {licenseNumber}");
                return null;
            }

            ticket.GetSpot().UnparkVehicle();
            ticket.SetExitTimestamp();
            double fee = feeStrategy.CalculateFee(ticket);
            Console.WriteLine($"Vehicle {licenseNumber} unparked from spot {ticket.GetSpot().GetSpotId()}");
            return fee;
        }
    }
}