package main

import (
	"design-patterns/golang/bridge"
	"fmt"
)

func main() {
	// Create renderers
	vectorRenderer := bridge.NewVectorRenderer()
	rasterRenderer := bridge.NewRasterRenderer()

	// Create shapes with vector renderer
	circle := bridge.NewCircle(vectorRenderer, 5.0)
	rectangle := bridge.NewRectangle(vectorRenderer, 10.0, 5.0)

	fmt.Println("Drawing shapes with vector renderer:")
	circle.Draw()
	rectangle.Draw()

	// Create shapes with raster renderer
	circle = bridge.NewCircle(rasterRenderer, 5.0)
	rectangle = bridge.NewRectangle(rasterRenderer, 10.0, 5.0)

	fmt.Println("\nDrawing shapes with raster renderer:")
	circle.Draw()
	rectangle.Draw()
}
