using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using db_code_generator.Parse;
using static db_code_generator.Parse.Struct;

namespace db_code_generator.Generate.Table.Method
{
    internal class FindWriter : IClassMethodWriter
    {
        public void Write(NameUtil util, Struct udt, TextWriter headerWriter, TextWriter cxxWriter)
        {
            Write_FindByPk(util, udt, headerWriter, cxxWriter);
            Write_FindByUnique(util, udt, headerWriter, cxxWriter);
            Write_FindByFk(util, udt, headerWriter, cxxWriter);
        }

        private void Write_FindByPk(NameUtil util, Struct udt, TextWriter headerWriter, TextWriter cxxWriter)
        {
            Column? column = udt.Columns.Find(column => column.Option?.PrimaryKey ?? false);
            if (column == null)
            {
                return;
            }

            string className = util.GetClassName();
            string methodName = $"FindBy{column.FieldName.ToUpper()}";
            string resultType = $"std::optional<{udt.GetFullName()}>";
            string paramType = $"const {column.TypeName}&";
            string paramName = $"{column.FieldName}";

            headerWriter.WriteLine($"\t\tauto {methodName}({paramType} {paramName}) -> {resultType};");

            cxxWriter.WriteLine($"\tauto {className}::{methodName}({paramType} {paramName}) -> {resultType}");
            cxxWriter.WriteLine("\t{");
            cxxWriter.WriteLine("\t\tauto statement = _connection.GetStatement();");
            cxxWriter.WriteLine("\t\tstatement.Prepare(R\"delimiter(");
            cxxWriter.WriteLine($"\t\t\tSELECT * FROM `{util.GetDbTableName()}`");
            cxxWriter.WriteLine($"\t\t\t\tWHERE `{column.FieldName}` = ?;");
            cxxWriter.WriteLine("\t\t\t");
            cxxWriter.WriteLine("\t\t)delimiter\");");

            cxxWriter.WriteLine($"\t\t");
            cxxWriter.WriteLine($"\t\tstatement.Set<{column.TypeName}>(1, {paramName});");
            cxxWriter.WriteLine("\t\tstatement.Execute();");
            cxxWriter.BreakLine();
            cxxWriter.WriteLine("\t\tauto resultSet = statement.GetResultSet();");
            cxxWriter.WriteLine("\t\tif (resultSet.Fetch())");
            cxxWriter.WriteLine("\t\t{");
            cxxWriter.WriteLine($"\t\t\treturn Deserializer<{udt.GetFullName()}>::Deserialize(resultSet);");
            cxxWriter.WriteLine("\t\t}");
            cxxWriter.WriteLine("\t\treturn std::nullopt;");
            cxxWriter.WriteLine("\t}");
        }

        private void Write_FindByUnique(NameUtil util, Struct udt, TextWriter headerWriter, TextWriter cxxWriter)
        {
            foreach (var column in udt.Columns.Where(column => column.Option?.Unique ?? false))
            {
                string className = util.GetClassName();
                string methodName = $"FindBy{column.FieldName.ToUpper()}";
                string resultType = $"std::optional<{udt.GetFullName()}>";
                string paramType = $"const {column.TypeName}&";
                string paramName = $"{column.FieldName}";

                headerWriter.WriteLine($"\t\tauto {methodName}({paramType} {paramName}) -> {resultType};");

                cxxWriter.WriteLine($"\tauto {className}::{methodName}({paramType} {paramName}) -> {resultType}");
                cxxWriter.WriteLine("\t{");
                cxxWriter.WriteLine("\t\tauto statement = _connection.GetStatement();");
                cxxWriter.WriteLine("\t\tstatement.Prepare(R\"delimiter(");
                cxxWriter.WriteLine($"\t\t\tSELECT * FROM `{util.GetDbTableName()}`");
                cxxWriter.WriteLine($"\t\t\t\tWHERE `{column.FieldName}` = ?;");
                cxxWriter.WriteLine("\t\t\t");
                cxxWriter.WriteLine("\t\t)delimiter\");");

                cxxWriter.WriteLine($"\t\t");
                cxxWriter.WriteLine($"\t\tstatement.Set<{column.TypeName}>(1, {paramName});");
                cxxWriter.WriteLine("\t\tstatement.Execute();");
                cxxWriter.BreakLine();
                cxxWriter.WriteLine("\t\tauto resultSet = statement.GetResultSet();");
                cxxWriter.WriteLine("\t\tif (resultSet.Fetch())");
                cxxWriter.WriteLine("\t\t{");
                cxxWriter.WriteLine($"\t\t\treturn Deserializer<{udt.GetFullName()}>::Deserialize(resultSet);");
                cxxWriter.WriteLine("\t\t}");
                cxxWriter.WriteLine("\t\treturn std::nullopt;");
                cxxWriter.WriteLine("\t}");
            }
        }

        private void Write_FindByFk(NameUtil util, Struct udt, TextWriter headerWriter, TextWriter cxxWriter)
        {
            foreach (var column in udt.Columns)
            {
                if (column.Option == null || !column.Option.ForeignKey)
                {
                    continue;
                }

                if ((column.Option?.PrimaryKey ?? false) || (column.Option?.Unique ?? false))
                {
                    continue;
                }

                string className = util.GetClassName();
                string methodName = $"FindBy{column.FieldName.ToUpper()}";
                string resultType = $"std::vector<{udt.GetFullName()}>";
                string paramType = $"const {column.TypeName}&";
                string paramName = $"{column.FieldName}";

                headerWriter.WriteLine($"\t\tauto {methodName}({paramType} {paramName}) -> {resultType};");

                cxxWriter.WriteLine($"\tauto {className}::{methodName}({paramType} {paramName}) -> {resultType}");
                cxxWriter.WriteLine("\t{");
                cxxWriter.WriteLine("\t\tauto statement = _connection.GetStatement();");
                cxxWriter.WriteLine("\t\tstatement.Prepare(R\"delimiter(");
                cxxWriter.WriteLine($"\t\t\tSELECT * FROM `{util.GetDbTableName()}`");
                cxxWriter.WriteLine($"\t\t\t\tWHERE `{column.FieldName}` = ?;");
                cxxWriter.WriteLine("\t\t\t");
                cxxWriter.WriteLine("\t\t)delimiter\");");

                cxxWriter.WriteLine($"\t\t");
                cxxWriter.WriteLine($"\t\tstatement.Set<{column.TypeName}>(1, {paramName});");
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
}
