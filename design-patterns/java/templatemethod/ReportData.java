import java.util.List;
import java.util.Map;
import java.util.Arrays;

public class ReportData {
    public List<String> getHeaders() {
        return Arrays.asList("ID", "Name", "Value");
    }
    public List<Map<String, Object>> getRows() {
        return Arrays.asList(
            Map.of("ID", 1, "Name", "Item A", "Value", 100.0),
            Map.of("ID", 2, "Name", "Item B", "Value", 150.5),
            Map.of("ID", 3, "Name", "Item C", "Value", 75.25)
        );
    }    
}
