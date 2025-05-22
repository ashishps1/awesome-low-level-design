public abstract class AbstractReportExporter {
    public final void exportReport(ReportData data, String filePath) {
        prepareData(data);
        openFile(filePath);
        writeHeader(data);
        writeDataRows(data);
        writeFooter(data);
        closeFile(filePath);
        System.out.println("Report exported to " + filePath);
    }

    // Hook method – optional for subclasses to override
    protected void prepareData(ReportData data) {
        System.out.println("Preparing report data...");
    }

    // Hook method – optional for subclasses to override
    protected void openFile(String filePath) {
        System.out.println("Opening file: " + filePath);
    }

    protected abstract void writeHeader(ReportData data);

    protected abstract void writeDataRows(ReportData data);
    
    // Hook method – optional for subclasses to override
    protected void writeFooter(ReportData data) {
        System.out.println("Writing footer...");
    }

    // Hook method – optional for subclasses to override
    protected void closeFile(String filePath) {
        System.out.println("Closing file: " + filePath);
    }
}
