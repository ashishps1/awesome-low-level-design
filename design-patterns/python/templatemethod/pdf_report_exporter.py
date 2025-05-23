from .abstract_report_exporter import AbstractReportExporter
from .report_data import ReportData


class PdfReportExporter(AbstractReportExporter):
    """Concrete Template Class for PDF export"""
    
    def _prepare_export(self) -> None:
        print("Initializing PDF document...")
        print("Setting up PDF formatting...")
    
    def _write_header(self, data: ReportData) -> None:
        print("PDF Header: Creating title section")
        headers = " | ".join(data.get_headers())
        print(f"PDF Table Headers: {headers}")
    
    def _write_data(self, data: ReportData) -> None:
        print("Writing PDF data with formatting:")
        for i, row in enumerate(data.get_data(), 1):
            values = " | ".join(str(row.get(header, "")) for header in data.get_headers())
            print(f"  PDF Row {i}: {values}")
    
    def _write_footer(self, data: ReportData) -> None:
        super()._write_footer(data)
        print("Adding PDF page numbers and metadata")
    
    def _finalize_export(self, filename: str) -> None:
        print("Optimizing PDF...")
        print(f"Saving PDF file: {filename}")
        print("PDF export finalized")