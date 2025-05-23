using System;

namespace TemplateMethod
{
    public class ExcelReportExporter : AbstractReportExporter
    {
        protected override void WriteHeader(ReportData data)
        {
            Console.WriteLine("Excel Header:");
            foreach (var header in data.GetHeaders())
            {
                Console.WriteLine($"\t{header}");
            }
        }

        protected override void WriteDataRows(ReportData data)
        {
            Console.WriteLine("Excel Data:");
            foreach (var row in data.GetRows())
            {
                Console.WriteLine("\tRow:");
                foreach (var header in data.GetHeaders())
                {
                    Console.WriteLine($"\t\t{header}: {row[header]}");
                }
            }
        }
    }
} 