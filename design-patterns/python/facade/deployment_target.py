import time

class DeploymentTarget:
    def transfer_artifact(self, artifact_path: str, server: str) -> None:
        print(f"Deployment: Transferring {artifact_path} to {server}...")
        self._simulate_delay(1)
        print("Deployment: Transfer complete.")

    def activate_new_version(self, server: str) -> None:
        print(f"Deployment: Activating new version on {server}...")
        self._simulate_delay(0.5)
        print(f"Deployment: Now live on {server}!")

    def _simulate_delay(self, seconds: int) -> None:
        time.sleep(seconds) 