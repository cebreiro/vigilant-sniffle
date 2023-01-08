using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using db_code_generator.Parse;

namespace db_code_generator.Generate.Table.Method
{
    internal class DropTableWriter : IClassMethodWriter
    {
        public void Write(NameUtil util, Struct udt, TextWriter headerWriter, TextWriter cxxWriter)
        {
            string methodName = "DropTable";

            headerWriter.WriteLine($"\t\tvoid {methodName}();");

            cxxWriter.WriteLine($"\tvoid {util.GetClassName()}::{methodName}()");
            cxxWriter.WriteLine("\t{");
            cxxWriter.WriteLine("\t\tauto statement = _connection.GetStatement();");
            cxxWriter.WriteLine("\t\tstatement.Prepare(R\"delimiter(");
            cxxWriter.WriteLine($"\t\tDROP TABLE IF EXISTS `{util.GetDbTableName()}`;");
            cxxWriter.WriteLine("\t\t)delimiter\");");
            cxxWriter.WriteLine("\t\tstatement.Execute();");
            cxxWriter.WriteLine("\t}");
        }
    }
}
