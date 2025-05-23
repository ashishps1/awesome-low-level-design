using System;

namespace TemplateMethod
{
    public abstract class AbstractReportExporter
    {
        public void ExportReport(ReportData data, string filePath)
        {
            PrepareData(data);
            OpenFile(filePath);
            WriteHeader(data);
            WriteDataRows(data);
            WriteFooter(data);
            CloseFile(filePath);
            Console.WriteLine($"Report exported to {filePath}");
        }

        // Hook method – optional for subclasses to override
        protected virtual void PrepareData(ReportData data)
        {
            Console.WriteLine("Preparing report data...");
        }

        // Hook method – optional for subclasses to override
        protected virtual void OpenFile(string filePath)
        {
            Console.WriteLine($"Opening file: {filePath}");
        }

        protected abstract void WriteHeader(ReportData data);

        protected abstract void WriteDataRows(ReportData data);

        // Hook method – optional for subclasses to override
        protected virtual void WriteFooter(ReportData data)
        {
            Console.WriteLine("Writing footer...");
        }

        // Hook method – optional for subclasses to override
        protected virtual void CloseFile(string filePath)
        {
            Console.WriteLine($"Closing file: {filePath}");
        }
    }
} 