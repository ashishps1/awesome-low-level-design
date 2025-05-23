package facade

import (
	"fmt"
)

// BuildSystem handles project compilation
type BuildSystem struct{}

// NewBuildSystem creates a new BuildSystem instance
func NewBuildSystem() *BuildSystem {
	return &BuildSystem{}
}

// CompileProject compiles the project
func (b *BuildSystem) CompileProject() bool {
	fmt.Println("Build: Compiling project...")
	simulateDelay()
	fmt.Println("Build: Compilation complete.")
	return true
}

// GetArtifactPath returns the path to the compiled artifact
func (b *BuildSystem) GetArtifactPath() string {
	return "/path/to/artifact"
}
