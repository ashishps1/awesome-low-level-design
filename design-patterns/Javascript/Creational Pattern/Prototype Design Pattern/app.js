class Car{
    constructor(model, year, color){
        this.model = model;
        this.year = year;
        this.color = color;
    } 

    clone(){ // Clone method to clone the current object
        return new Car(this.model, this.year, this.color);  // Return the new object with same properties
    }

    getDetails(){
        return `Model: ${this.model}, Year: ${this.year}, Color: ${this.color}`
    }
}

const prototypeCar = new Car("Mustang", 2019, "red");

const cloneCar1 = prototypeCar.clone(); // 1st clone
cloneCar1.color = "blue";

const cloneCar2 = prototypeCar.clone(); // 2nd clone
cloneCar2.color = "green";

console.log(prototypeCar.getDetails());
console.log(cloneCar1.getDetails());
console.log(cloneCar2.getDetails());