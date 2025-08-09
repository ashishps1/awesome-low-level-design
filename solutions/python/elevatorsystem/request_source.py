from enum import Enum

class RequestSource(Enum):
    INTERNAL = "INTERNAL"  # From inside the cabin
    EXTERNAL = "EXTERNAL"  # From the hall/floor