from abc import ABC, abstractmethod

class MatchFormatStrategy(ABC):
    @abstractmethod
    def get_total_innings(self):
        pass

    @abstractmethod
    def get_total_overs(self):
        pass

    @abstractmethod
    def get_format_name(self):
        pass

class T20FormatStrategy(MatchFormatStrategy):
    def get_total_innings(self):
        return 2

    def get_total_overs(self):
        return 20

    def get_format_name(self):
        return "T20"

class ODIFormatStrategy(MatchFormatStrategy):
    def get_total_innings(self):
        return 2

    def get_total_overs(self):
        return 50

    def get_format_name(self):
        return "ODI"