using db_code_generator.Parse;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace db_code_generator.Generate.Table.Method
{
    internal class CtorWriter : IClassMethodWriter
    {
        public void Write(NameUtil util, Struct udt, TextWriter headerWriter, TextWriter cxxWriter)
        {
            string className = util.GetClassName();

            headerWriter.WriteLine($"\t\t{className}(odbc::Connection& connection);");

            cxxWriter.WriteLine($"\t{className}::{className}(odbc::Connection& connection)");
            cxxWriter.WriteLine("\t\t: _connection(connection)");
            cxxWriter.WriteLine("\t{");
            cxxWriter.WriteLine("\t}");
        }
    }
}
