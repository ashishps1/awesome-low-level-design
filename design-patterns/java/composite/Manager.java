class Manager implements Employee {
    private String name;
    private double salary;
    private List<Employee> subordinates = new ArrayList<>();

    public Manager(String name, double salary) {
        this.name = name;
        this.salary = salary;
    }

    public void addEmployee(Employee employee) {
        subordinates.add(employee);
    }

    public void removeEmployee(Employee employee) {
        subordinates.remove(employee);
    }

    @Override
    public void showDetails() {
        System.out.println("Manager: " + name + ", Salary: $" + salary);
        System.out.println("Subordinates:");
        for (Employee employee : subordinates) {
            employee.showDetails();
        }
    }

    @Override
    public double getSalary() {
        double totalSalary = salary;
        for (Employee employee : subordinates) {
            totalSalary += employee.getSalary();
        }
        return totalSalary;
    }
}