import time

class BuildSystem:
    def compile_project(self) -> bool:
        print("BuildSystem: Compiling project...")
        self._simulate_delay(2)
        print("BuildSystem: Build successful.")
        return True

    def get_artifact_path(self) -> str:
        path = "target/myapplication-1.0.jar"
        print(f"BuildSystem: Artifact located at {path}")
        return path
    
    def _simulate_delay(self, seconds: int) -> None:
        time.sleep(seconds) 