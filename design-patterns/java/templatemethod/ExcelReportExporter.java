import java.util.Map;

public class ExcelReportExporter extends AbstractReportExporter {
    //prepareData() not overridden - default will be used
    //openFile() not overridden - default will be used

    @Override
    protected void writeHeader(ReportData data) {
        System.out.println("Excel: Writing header: " + String.join(",", data.getHeaders()));
    }

    @Override
    protected void writeDataRows(ReportData data) {
        System.out.println("Excel: Writing data rows...");
        for (Map<String, Object> row : data.getRows()) {
            System.out.println("Excel: " + row.values());
        }
    }

    // writeFooter() not overridden - default will be used
    // closeFile() not overridden - default will be used
}