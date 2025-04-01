public class CompositeDemo {
    public static void main(String[] args) {
        Developer dev1 = new Developer("John Doe", 100000);
        Developer dev2 = new Developer("Jane Smith", 120000);
        Designer designer = new Designer("Mike Johnson", 90000);

        Manager engManager = new Manager("Emily Brown", 200000);
        engManager.addEmployee(dev1);
        engManager.addEmployee(dev2);
        engManager.addEmployee(designer);

        Manager generalManager = new Manager("David Wilson", 300000);
        generalManager.addEmployee(engManager);

        System.out.println("Company Structure:");
        generalManager.showDetails();

        System.out.println("\nTotal Salary Budget: $" + generalManager.getSalary());
    }
}