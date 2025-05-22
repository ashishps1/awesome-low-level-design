public class ReportAppTemplateMethod {
    public static void main(String[] args) {
        ReportData reportData = new ReportData();

        AbstractReportExporter csvExporter = new CsvReportExporter();
        csvExporter.exportReport(reportData, "sales_report");

        System.out.println();

        AbstractReportExporter pdfExporter = new PdfReportExporter();
        pdfExporter.exportReport(reportData, "financial_summary");
    }
}
