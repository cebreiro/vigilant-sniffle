using db_code_generator.Parse;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace db_code_generator.Generate.Table.Method
{
    internal class AssignWriter : IClassMethodWriter
    {
        public void Write(NameUtil util, Struct udt, TextWriter headerWriter, TextWriter cxxWriter)
        {
            string className = util.GetClassName();
            string methodName = "Assign";
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
            cxxWriter.WriteLine($"\t\t\t\t({temp2})");

            Func<Struct.Column, bool> updateCondition = column => column.Option is not { PrimaryKey: true } && column.Option is not { ForeignKey: true };

            cxxWriter.WriteLine("\t\t\tON DUPLICATE KEY UPDATE");
            string temp3 = udt.Columns
                .Where(updateCondition)
                .Select(column => $"`{column.FieldName}` = ?")
                .Aggregate((s1, s2) => $"{s1}, {s2}");
            cxxWriter.WriteLine($"\t\t\t\t({temp3});");

            cxxWriter.WriteLine("\t\t)delimiter\");");
            int i = 1;
            for (; i <= udt.Columns.Count; ++i)
            {
                var column = udt.Columns[i - 1];

                cxxWriter.WriteLine($"\t\tstatement.Set<{column.TypeName}>({i}, {paramName}.{column.FieldName});");
            }

            foreach (var column in udt.Columns.Where(updateCondition))
            {
                cxxWriter.WriteLine($"\t\tstatement.Set<{column.TypeName}>({i}, {paramName}.{column.FieldName});");
                ++i;
            }

            cxxWriter.WriteLine("\t\tstatement.Execute();");
            cxxWriter.WriteLine("\t}");
        }
    }
}
