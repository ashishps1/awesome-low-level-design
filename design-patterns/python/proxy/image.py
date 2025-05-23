from abc import ABC, abstractmethod

class Image(ABC):
    @abstractmethod
    def display(self) -> None:
        pass

    @abstractmethod
    def get_file_name(self) -> str:
        pass 