using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using db_code_generator.Parse;
using static db_code_generator.Parse.Struct;

namespace db_code_generator.Generate.Table.Method
{
    internal class RemoveWriter : IClassMethodWriter
    {
        public void Write(NameUtil util, Struct udt, TextWriter headerWriter, TextWriter cxxWriter)
        {
            Write_RemoveByPk(util, udt, headerWriter, cxxWriter);
            Write_RemoveByFk(util, udt, headerWriter, cxxWriter);
        }

        private void Write_RemoveByPk(NameUtil util, Struct udt, TextWriter headerWriter, TextWriter cxxWriter)
        {
            Column? column = udt.Columns.Find(column => column.Option?.PrimaryKey ?? false);
            if (column == null)
            {
                return;
            }

            string className = util.GetClassName();
            string methodName = $"RemoveBy{column.FieldName.ToUpper()}";
            string paramType = $"const {column.TypeName}&";
            string paramName = $"{column.FieldName}";

            headerWriter.WriteLine($"\t\tvoid {methodName}({paramType} {paramName});");

            cxxWriter.WriteLine($"\tvoid {className}::{methodName}({paramType} {paramName})");
            cxxWriter.WriteLine("\t{");
            cxxWriter.WriteLine("\t\tauto statement = _connection.GetStatement();");
            cxxWriter.WriteLine("\t\tstatement.Prepare(R\"delimiter(");
            cxxWriter.WriteLine($"\t\t\tDELETE FROM `{util.GetDbTableName()}`");
            cxxWriter.WriteLine($"\t\t\t\tWHERE `{column.FieldName}` = ?;");
            cxxWriter.WriteLine("\t\t\t");
            cxxWriter.WriteLine("\t\t)delimiter\");");

            cxxWriter.WriteLine($"\t\t");
            cxxWriter.WriteLine($"\t\tstatement.Set<{column.TypeName}>(1, {paramName});");
            cxxWriter.WriteLine("\t\tstatement.Execute();");
            cxxWriter.WriteLine("\t}");
        }

        private void Write_RemoveByFk(NameUtil util, Struct udt, TextWriter headerWriter, TextWriter cxxWriter)
        {
            foreach (var column in udt.Columns.Where(column => column.Option?.ForeignKey ?? false))
            {
                string className = util.GetClassName();
                string methodName = $"RemoveBy{column.FieldName.ToUpper()}";
                string paramType = $"const {column.TypeName}&";
                string paramName = $"{column.FieldName}";

                headerWriter.WriteLine($"\t\tvoid {methodName}({paramType} {paramName});");

                cxxWriter.WriteLine($"\tvoid {className}::{methodName}({paramType} {paramName})");
                cxxWriter.WriteLine("\t{");
                cxxWriter.WriteLine("\t\tauto statement = _connection.GetStatement();");
                cxxWriter.WriteLine("\t\tstatement.Prepare(R\"delimiter(");
                cxxWriter.WriteLine($"\t\t\tDELETE FROM `{util.GetDbTableName()}`");
                cxxWriter.WriteLine($"\t\t\t\tWHERE `{column.FieldName}` = ?;");
                cxxWriter.WriteLine("\t\t\t");
                cxxWriter.WriteLine("\t\t)delimiter\");");

                cxxWriter.WriteLine($"\t\t");
                cxxWriter.WriteLine($"\t\tstatement.Set<{column.TypeName}>(1, {paramName});");
                cxxWriter.WriteLine("\t\tstatement.Execute();");
                cxxWriter.WriteLine("\t}");
            }
        }
    }
}
