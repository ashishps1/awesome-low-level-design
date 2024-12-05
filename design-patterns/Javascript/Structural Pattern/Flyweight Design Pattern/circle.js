// Intrinsic state
class Circle{
    constructor(color){
        this.color = color;
    }

    draw(size, x, y){
        console.log(`Drawing a circle of size ${size} at position (${x}, ${y})`);
    }
}

module.exports = Circle;