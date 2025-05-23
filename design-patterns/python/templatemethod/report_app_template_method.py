from .report_data import ReportData
from .csv_report_exporter import CsvReportExporter
from .pdf_report_exporter import PdfReportExporter
from .excel_report_exporter import ExcelReportExporter


def create_sample_data() -> ReportData:
    """Create sample report data"""
    data = ReportData()
    data.add_row({"Name": "John Doe", "Department": "Engineering", "Salary": 85000})
    data.add_row({"Name": "Jane Smith", "Department": "Marketing", "Salary": 75000})
    data.add_row({"Name": "Bob Johnson", "Department": "Sales", "Salary": 65000})
    data.add_row({"Name": "Alice Brown", "Department": "Engineering", "Salary": 90000})
    return data


def template_method_demo():
    """Demonstrate Template Method pattern"""
    print("=== Template Method Pattern Demo ===")
    
    # Create sample data
    report_data = create_sample_data()
    
    # Create exporters
    csv_exporter = CsvReportExporter()
    pdf_exporter = PdfReportExporter()
    excel_exporter = ExcelReportExporter()
    
    # Export using different formats - same algorithm, different implementations
    print("\n--- CSV Export ---")
    csv_exporter.export_report(report_data, "employee_report.csv")
    
    print("\n--- PDF Export ---")
    pdf_exporter.export_report(report_data, "employee_report.pdf")
    
    print("\n--- Excel Export ---")
    excel_exporter.export_report(report_data, "employee_report.xlsx")


if __name__ == "__main__":
    template_method_demo()