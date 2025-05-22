public class ReportAppNaive {
    public static void main(String[] args) {
        ReportData reportData = new ReportData();

        CsvReportExporterNaive csvExporter = new CsvReportExporterNaive();
        csvExporter.export(reportData, "sales_report");

        System.out.println();

        PdfReportExporterNaive pdfExporter = new PdfReportExporterNaive();
        pdfExporter.export(reportData, "financial_summary");
    }
}
