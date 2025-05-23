using System.Collections.Generic;

namespace TemplateMethod
{
    public class ReportData
    {
        public List<string> GetHeaders()
        {
            return new List<string> { "ID", "Name", "Value" };
        }

        public List<Dictionary<string, object>> GetRows()
        {
            return new List<Dictionary<string, object>>
            {
                new Dictionary<string, object> { { "ID", 1 }, { "Name", "Item A" }, { "Value", 100.0 } },
                new Dictionary<string, object> { { "ID", 2 }, { "Name", "Item B" }, { "Value", 150.5 } },
                new Dictionary<string, object> { { "ID", 3 }, { "Name", "Item C" }, { "Value", 75.25 } }
            };
        }
    }
} 