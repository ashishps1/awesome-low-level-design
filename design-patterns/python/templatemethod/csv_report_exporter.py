from .abstract_report_exporter import AbstractReportExporter
from .report_data import ReportData


class CsvReportExporter(AbstractReportExporter):
    """Concrete Template Class for CSV export"""
    
    def _write_header(self, data: ReportData) -> None:
        headers = ",".join(data.get_headers())
        print(f"CSV Header: {headers}")
    
    def _write_data(self, data: ReportData) -> None:
        print("Writing CSV data rows:")
        for i, row in enumerate(data.get_data(), 1):
            values = ",".join(str(row.get(header, "")) for header in data.get_headers())
            print(f"  Row {i}: {values}")
    
    def _finalize_export(self, filename: str) -> None:
        print(f"Saving CSV file: {filename}")
        print("CSV export finalized")