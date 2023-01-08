using ClangSharp.Interop;
using db_code_generator.Parse;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using db_code_generator.Generate.Table;

namespace db_code_generator.Generate.ODBC
{
    internal class DeserializerWriter
    {
        public Result GenerateSourceFile(List<HeaderParseResult> headerParseResults)
        {
            return GenerateSource(headerParseResults
                .Where(results => results.Structs.Count > 0)
                .ToList());
        }

        private Result GenerateSource(List<HeaderParseResult> headerParseResults)
        {
            TextWriter headerWriter = new TextWriter();
            TextWriter cxxWriter = new TextWriter();

            headerWriter.WriteLine("#pragma once");
            headerWriter.WriteLine("#include <cstdint>");
            headerWriter.WriteLine("#include <memory>");
            headerWriter.BreakLine();
            headerWriter.WriteLine("#include \"lib/odbc/connection.h\"");
            headerWriter.BreakLine();

            foreach (var header in headerParseResults)
            {
                foreach (var udt in header.Structs)
                {
                    bool hasNamespace = udt.Namespaces.Count > 0;
                    if (hasNamespace)
                    {
                        headerWriter.Write("namespace ");

                        for (int i = 0; i < udt.Namespaces.Count; ++i)
                        {
                            headerWriter.Write($"{udt.Namespaces[i]}");

                            if (i < udt.Namespaces.Count - 1)
                            {
                                headerWriter.Write("::");
                            }
                        }

                        headerWriter.Write(" { ");
                    }

                    headerWriter.Write($"struct {udt.Name};");

                    if (hasNamespace)
                    {
                        headerWriter.Write(" } ");
                    }
                    headerWriter.BreakLine();
                }
            }

            cxxWriter.WriteLine($"#include \"{GetFileName()}.h\"");
            cxxWriter.BreakLine();
            cxxWriter.WriteLine("#include <cstdint>");
            cxxWriter.WriteLine("#include <cassert>");
            cxxWriter.WriteLine("#include <format>");
            cxxWriter.BreakLine();

            foreach (var result in headerParseResults)
            {
                cxxWriter.WriteLine($"#include \"{PathUtil.GetIncludePath(result)}\"");
            }

            cxxWriter.BreakLine();
            cxxWriter.WriteLine("namespace cebreiro::gamedb");
            cxxWriter.WriteLine("{");

            headerWriter.WriteLine("namespace cebreiro::gamedb");
            headerWriter.WriteLine("{");

            headerWriter.WriteLine("\ttemplate <typename T> struct Deserializer;");
            headerWriter.BreakLine();

            foreach (var header in headerParseResults)
            {
                foreach (var udt in header.Structs)
                {
                    string variableName = "result";

                    headerWriter.WriteLine($"\ttemplate <> struct Deserializer<{udt.GetFullName()}> {{");
                    headerWriter.WriteLine($"\t\tstatic auto Deserialize(odbc::ResultSet& rs) -> {udt.GetFullName()};");
                    headerWriter.WriteLine("\t};");


                    cxxWriter.WriteLine($"\tauto Deserializer<{udt.GetFullName()}>::Deserialize(odbc::ResultSet& rs) -> {udt.GetFullName()}");
                    cxxWriter.WriteLine("\t{");
                    cxxWriter.WriteLine($"\t\t{udt.GetFullName()} {variableName};");

                    for (int i = 0; i < udt.Columns.Count; ++i)
                    {
                        Struct.Column column = udt.Columns[i];
                        int index = i + 1;

                        if (column.TypeName.StartsWith("std::optional"))
                        {
                            string methodName = GetResultSetGetMethodName(column.TypeName.Split('<', '>')[1]);

                            cxxWriter.WriteLine($"\t\tif (rs.IsNull({index}))");
                            cxxWriter.WriteLine("\t\t{");
                            cxxWriter.WriteLine($"\t\t\t{variableName}.{column.FieldName} = std::nullopt;");
                            cxxWriter.WriteLine("\t\t}");
                            cxxWriter.WriteLine("\t\telse");
                            cxxWriter.WriteLine("\t\t{");
                            cxxWriter.WriteLine($"\t\t\t{variableName}.{column.FieldName} = rs.{methodName}({index});");
                            cxxWriter.WriteLine("\t\t}");
                        }
                        else
                        {
                            string methodName = GetResultSetGetMethodName(column.TypeName);
                            cxxWriter.WriteLine($"\t\t{variableName}.{column.FieldName} = rs.{methodName}({index});");
                        }
                    }
                    cxxWriter.BreakLine();
                    cxxWriter.WriteLine($"\t\treturn {variableName};");
                    cxxWriter.WriteLine("\t}");
                }
            }

            headerWriter.WriteLine("}"); // namespace
            cxxWriter.WriteLine("}");  // namespace

            return new Result(GetFileName(), headerWriter.Get(), cxxWriter.Get());
        }

        private string GetFileName()
        {
            return "deserializer";
        }

        private string GetResultSetGetMethodName(string type)
        {
            switch (type)
            {
                case "int8_t": return "GetInt8";
                case "uint8_t": return "GetUInt8";
                case "int16_t": return "GetInt16";
                case "uint16_t": return "GetUInt16";
                case "int32_t": return "GetInt32";
                case "uint32_t": return "GetUInt32";
                case "int64_t": return "GetInt64";
                case "float": return "GetFloat32";
                case "double": return "GetFloat64";
                case "std::string": return "GetString";
            }

            throw new NotImplementedException($"fail to find target type. type: {type}"); }
    }
}
