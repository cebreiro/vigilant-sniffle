using db_code_generator.Parse;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static db_code_generator.Parse.Struct;

namespace db_code_generator.Generate.Table.Method
{
    internal class GetAllWriter : IClassMethodWriter
    {
        public void Write(NameUtil util, Struct udt, TextWriter headerWriter, TextWriter cxxWriter)
        {
            string className = util.GetClassName();
            string methodName = $"GetAll";
            string resultType = $"std::vector<{udt.GetFullName()}>";

            headerWriter.WriteLine($"\t\tauto {methodName}() -> {resultType};");

            cxxWriter.WriteLine($"\tauto {className}::{methodName}() -> {resultType}");
            cxxWriter.WriteLine("\t{");
            cxxWriter.WriteLine("\t\tauto statement = _connection.GetStatement();");
            cxxWriter.WriteLine("\t\tstatement.Prepare(R\"delimiter(");
            cxxWriter.WriteLine($"\t\t\tSELECT * FROM `{util.GetDbTableName()}`");
            cxxWriter.WriteLine("\t\t\t");
            cxxWriter.WriteLine("\t\t)delimiter\");");

            cxxWriter.WriteLine($"\t\t");
            cxxWriter.WriteLine("\t\tstatement.Execute();");
            cxxWriter.BreakLine();
            cxxWriter.WriteLine($"\t\t{resultType} result;");
            cxxWriter.WriteLine("\t\tauto resultSet = statement.GetResultSet();");
            cxxWriter.WriteLine("\t\twhile (resultSet.Fetch())");
            cxxWriter.WriteLine("\t\t{");
            cxxWriter.WriteLine($"\t\t\tresult.push_back(Deserializer<{udt.GetFullName()}>::Deserialize(resultSet));");
            cxxWriter.WriteLine("\t\t}");
            cxxWriter.WriteLine("\t\treturn result;");
            cxxWriter.WriteLine("\t}");
        }
    }
}
