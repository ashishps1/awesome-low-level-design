from typing import Dict, Any, List


class ReportData:
    """Data class for report information"""
    
    def __init__(self):
        self._data: List[Dict[str, Any]] = []
        self._headers: List[str] = []
    
    def add_row(self, row: Dict[str, Any]) -> None:
        """Add a data row"""
        if not self._headers and row:
            self._headers = list(row.keys())
        self._data.append(row)
    
    def get_data(self) -> List[Dict[str, Any]]:
        return self._data.copy()
    
    def get_headers(self) -> List[str]:
        return self._headers.copy()
    
    def get_row_count(self) -> int:
        return len(self._data)