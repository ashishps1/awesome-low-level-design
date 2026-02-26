from dataclasses import dataclass

# Since we wont be altering the contents of user objects, mark frozen.
@dataclass(frozen=True)
class User:
    id: str
    name: str
    email: str