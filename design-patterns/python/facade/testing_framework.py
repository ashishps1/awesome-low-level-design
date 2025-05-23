import time

class TestingFramework:
    def run_unit_tests(self) -> bool:
        print("Testing: Running unit tests...")
        self._simulate_delay(1.5)
        print("Testing: Unit tests passed.")
        return True

    def run_integration_tests(self) -> bool:
        print("Testing: Running integration tests...")
        self._simulate_delay(3)
        print("Testing: Integration tests passed.")
        return True

    def _simulate_delay(self, seconds: int) -> None:
        time.sleep(seconds) 