from .abstract_report_exporter import AbstractReportExporter
from .report_data import ReportData


class ExcelReportExporter(AbstractReportExporter):
    """Concrete Template Class for Excel export"""
    
    def _prepare_export(self) -> None:
        print("Creating Excel workbook...")
        print("Setting up worksheet...")
    
    def _write_header(self, data: ReportData) -> None:
        print("Excel Header: Formatting header row")
        for i, header in enumerate(data.get_headers(), 1):
            print(f"  Cell A{i}: {header} (Bold, Background Color)")
    
    def _write_data(self, data: ReportData) -> None:
        print("Writing Excel data with cell formatting:")
        for row_idx, row in enumerate(data.get_data(), 2):  # Start from row 2
            for col_idx, header in enumerate(data.get_headers(), 1):
                value = row.get(header, "")
                col_letter = chr(64 + col_idx)  # A, B, C, etc.
                print(f"  Cell {col_letter}{row_idx}: {value}")
    
    def _write_footer(self, data: ReportData) -> None:
        super()._write_footer(data)
        print("Adding Excel formulas and totals")
    
    def _finalize_export(self, filename: str) -> None:
        print("Applying Excel auto-formatting...")
        print(f"Saving Excel file: {filename}")
        print("Excel export finalized")