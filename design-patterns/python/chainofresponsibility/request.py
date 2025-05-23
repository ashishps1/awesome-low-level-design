from dataclasses import dataclass

@dataclass
class Request:
    user: str
    user_role: str
    request_count: int
    payload: str 