from abc import ABC, abstractmethod
from .report_data import ReportData


class AbstractReportExporter(ABC):
    """Abstract Template Class for report exporters"""
    
    def export_report(self, data: ReportData, filename: str) -> None:
        """Template method defining the export algorithm"""
        print(f"Starting export to {filename}")
        
        # Template method steps
        self._prepare_export()
        self._write_header(data)
        self._write_data(data)
        self._write_footer(data)
        self._finalize_export(filename)
        
        print(f"Export completed: {filename}")
    
    def _prepare_export(self) -> None:
        """Hook method - can be overridden"""
        print("Preparing export...")
    
    @abstractmethod
    def _write_header(self, data: ReportData) -> None:
        """Abstract method - must be implemented by subclasses"""
        pass
    
    @abstractmethod
    def _write_data(self, data: ReportData) -> None:
        """Abstract method - must be implemented by subclasses"""
        pass
    
    def _write_footer(self, data: ReportData) -> None:
        """Hook method - can be overridden"""
        print(f"Writing footer (Total rows: {data.get_row_count()})")
    
    @abstractmethod
    def _finalize_export(self, filename: str) -> None:
        """Abstract method - must be implemented by subclasses"""
        pass