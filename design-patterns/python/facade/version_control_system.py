import time

class VersionControlSystem:
    def pull_latest_changes(self, branch: str) -> None:
        print(f"VCS: Pulling latest changes from '{branch}'...")
        self._simulate_delay()
        print("VCS: Pull complete.")
    
    def _simulate_delay(self) -> None:
        time.sleep(1) 