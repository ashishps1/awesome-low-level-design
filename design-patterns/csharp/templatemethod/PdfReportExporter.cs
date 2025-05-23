using System;

namespace TemplateMethod
{
    public class PdfReportExporter : AbstractReportExporter
    {
        protected override void WriteHeader(ReportData data)
        {
            Console.WriteLine("PDF Header:");
            Console.WriteLine("----------------------------------------");
            foreach (var header in data.GetHeaders())
            {
                Console.Write($"{header,-15}");
            }
            Console.WriteLine("\n----------------------------------------");
        }

        protected override void WriteDataRows(ReportData data)
        {
            Console.WriteLine("PDF Data:");
            foreach (var row in data.GetRows())
            {
                foreach (var header in data.GetHeaders())
                {
                    Console.Write($"{row[header],-15}");
                }
                Console.WriteLine();
            }
            Console.WriteLine("----------------------------------------");
        }
    }
} 