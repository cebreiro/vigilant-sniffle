using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using db_code_generator.Parse;

namespace db_code_generator.Generate.Table.Method
{
    internal class AddWriter : IClassMethodWriter
    {
        public void Write(NameUtil util, Struct udt, TextWriter headerWriter, TextWriter cxxWriter)
        {
            string className = util.GetClassName();
            string methodName = "Add";
            string paramType = $"const {udt.GetFullName()}&";
            string paramName = "item";

            headerWriter.WriteLine($"\t\tvoid {methodName}({paramType} {paramName});");

            cxxWriter.WriteLine($"\tvoid {className}::{methodName}({paramType} {paramName})");
            cxxWriter.WriteLine("\t{");
            cxxWriter.WriteLine("\t\tauto statement = _connection.GetStatement();");
            cxxWriter.WriteLine("\t\tstatement.Prepare(R\"delimiter(");
            cxxWriter.WriteLine($"\t\t\tINSERT INTO `{util.GetDbTableName()}`");

            string temp1 = udt.Columns
                .Select(column => $"`{column.FieldName}`")
                .Aggregate((s1, s2) => $"{s1}, {s2}");
            cxxWriter.WriteLine($"\t\t\t\t({temp1})");
            cxxWriter.WriteLine("\t\t\tVALUES");

            string temp2 = udt.Columns
                .Select(_ => "?")
                .Aggregate((s1, s2) => $"{s1}, {s2}");
            cxxWriter.WriteLine($"\t\t\t\t({temp2});");

            cxxWriter.WriteLine("\t\t)delimiter\");");
            for (int i = 1; i <= udt.Columns.Count; ++i)
            {
                var column = udt.Columns[i - 1];

                cxxWriter.WriteLine($"\t\tstatement.Set<{column.TypeName}>({i}, {paramName}.{column.FieldName});");
            }
            cxxWriter.WriteLine("\t\tstatement.Execute();");
            cxxWriter.WriteLine("\t}");
        }
    }
}
