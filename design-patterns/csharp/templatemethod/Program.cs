using System;

namespace TemplateMethod
{
    class Program
    {
        static void Main(string[] args)
        {
            var data = new ReportData();

            // Export to different formats
            var csvExporter = new CsvReportExporter();
            var excelExporter = new ExcelReportExporter();
            var pdfExporter = new PdfReportExporter();

            Console.WriteLine("Exporting to CSV:");
            csvExporter.ExportReport(data, "report.csv");

            Console.WriteLine("\nExporting to Excel:");
            excelExporter.ExportReport(data, "report.xlsx");

            Console.WriteLine("\nExporting to PDF:");
            pdfExporter.ExportReport(data, "report.pdf");
        }
    }
} 