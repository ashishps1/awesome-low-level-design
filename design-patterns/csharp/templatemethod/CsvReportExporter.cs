using System;
using System.Linq;

namespace TemplateMethod
{
    public class CsvReportExporter : AbstractReportExporter
    {
        protected override void WriteHeader(ReportData data)
        {
            var headers = data.GetHeaders();
            Console.WriteLine(string.Join(",", headers));
        }

        protected override void WriteDataRows(ReportData data)
        {
            foreach (var row in data.GetRows())
            {
                var values = data.GetHeaders()
                    .Select(header => row[header].ToString())
                    .ToList();
                Console.WriteLine(string.Join(",", values));
            }
        }
    }
} 