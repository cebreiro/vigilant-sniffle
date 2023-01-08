using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using db_code_generator.Parse;

namespace db_code_generator.Generate.Table.Method
{
    internal class CreateTableWriter : IClassMethodWriter
    {
        public void Write(NameUtil util, Struct udt, TextWriter headerWriter, TextWriter cxxWriter)
        {
            string methodName = "CreateTable";

            headerWriter.WriteLine($"\t\tvoid {methodName}();");

            cxxWriter.WriteLine($"\tvoid {util.GetClassName()}::{methodName}()");
            cxxWriter.WriteLine("\t{");
            cxxWriter.WriteLine("\t\tauto statement = _connection.GetStatement();");
            cxxWriter.WriteLine("\t\tstatement.Prepare(R\"delimiter(");
            cxxWriter.WriteLine($"\t\tCREATE TABLE IF NOT EXISTS `{util.GetDbTableName()}` (");

            for (var i = 0; i < udt.Columns.Count; i++)
            {
                cxxWriter.Write("\t\t\t");

                if (i > 0)
                {
                    cxxWriter.Write(", ");
                }

                cxxWriter.WriteLine(GetCreateTableColumnText(udt.Columns[i]));
            }

            foreach (var column in udt.Columns.Where(column => column.Option != null))
            {
                Option option = column.Option;

                if (option.PrimaryKey)
                {
                    cxxWriter.WriteLine($"\t\t\t, PRIMARY KEY(`{column.FieldName}`)");
                }

                if (option.Index)
                {
                    cxxWriter.WriteLine($"\t\t\t, KEY `{udt.Name}_idx_{column.FieldName}` (`{column.FieldName}`)");
                }

                if (option.Unique)
                {
                    cxxWriter.WriteLine($"\t\t\t, UNIQUE KEY `{udt.Name}_unique_{column.FieldName}` (`{column.FieldName}`)");
                }

                if (option.ForeignKey)
                {
                    cxxWriter.WriteLine($"\t\t\t, CONSTRAINT `{udt.Name}_fk_{column.FieldName}` FOREIGN KEY (`{column.FieldName}`)");
                    cxxWriter.WriteLine($"\t\t\t\tREFERENCES `{option.ForeignKeyTargetTable}` (`{option.ForeignKeyTargetField}`)");
                    cxxWriter.WriteLine($"\t\t\t\tON DELETE CASCADE ON UPDATE CASCADE");
                }
            }

            cxxWriter.WriteLine("\t\t) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;");
            cxxWriter.WriteLine("\t\t)delimiter\");");
            cxxWriter.WriteLine("\t\tstatement.Execute();");
            cxxWriter.WriteLine("\t}");
        }

        private string GetCreateTableColumnText(Struct.Column column)
        {
            StringBuilder builder = new StringBuilder();
            builder.Append($"`{column.FieldName}`");

            Option option = column.Option;
            bool isNullable = column.TypeName.StartsWith("std::optional");

            string typeName = column.TypeName;
            if (isNullable)
            {
                typeName = column.TypeName.Split('<', '>')[1];
            }

            switch (typeName)
            {
                case "int8_t":
                case "uint8_t":
                    builder.Append(" TINYINT");
                    break;
                case "int16_t":
                case "uint16_t":
                    builder.Append(" SMALLINT");
                    break;
                case "int32_t":
                case "uint32_t":
                    builder.Append(" INT");
                    break;
                case "int64_t":
                    builder.Append(" BIGINT");
                    break;
                case "float":
                    builder.Append(" FLOAT");
                    break;
                case "double":
                    builder.Append(" DOUBLE");
                    break;
                case "std::string":
                    builder.Append($" VARCHAR({option?.MaxLength ?? 4096})");
                    break;
                default:
                    throw new NotImplementedException($"invalid typename: {typeName}");
            }

            if (!isNullable)
            {
                builder.Append(" NOT NULL");
            }

            if (option != null)
            {
                if (option.DefaultValue != null)
                {
                    builder.Append($" DEFAULT '{option.DefaultValue}' ");
                }

                if (option.AutoIncrement)
                {
                    builder.Append(" AUTO_INCREMENT");
                }
            }

            return builder.ToString();
        }
    }
}
