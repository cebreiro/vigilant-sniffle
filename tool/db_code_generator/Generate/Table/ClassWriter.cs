using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using db_code_generator.Generate.ODBC;
using db_code_generator.Generate.Table.Method;
using db_code_generator.Parse;

namespace db_code_generator.Generate.Table
{
    internal class ClassWriter
    {
        private readonly string _deserializerFileName;

        private readonly List<List<IClassMethodWriter>> _methodWriters = new()
        {
            new List<IClassMethodWriter>
            {
                new CtorWriter(),
            },
            new List<IClassMethodWriter>
            {
                new CreateTableWriter(),
                new DropTableWriter(),
            },
            new List<IClassMethodWriter>
            {
                new AddWriter(), 
                new AssignWriter(),
            },
            new List<IClassMethodWriter>()
            {
                new RemoveWriter(),
            },
            new List<IClassMethodWriter>()
            {
                new FindWriter(),
            },
            new List<IClassMethodWriter>()
            {
                new GetAllWriter(),
            },
        };

        public ClassWriter(string deserializerFileName)
        {
            _deserializerFileName = deserializerFileName;
        }

        public List<Result> GenerateSourceFile(List<HeaderParseResult> headerParseResults)
        {
            return headerParseResults
                .Where(results => results.Structs.Count > 0)
                .Select(GenerateSource)
                .ToList();
        }

        private Result GenerateSource(HeaderParseResult result)
        {
            TextWriter headerWriter = new TextWriter();
            TextWriter cxxWriter = new TextWriter();

            headerWriter.WriteLine("#pragma once");
            headerWriter.WriteLine("#include <cstdint>");
            headerWriter.WriteLine("#include <memory>");
            headerWriter.WriteLine("#include <vector>");
            headerWriter.BreakLine();
            headerWriter.WriteLine($"#include \"{PathUtil.GetIncludePath(result)}\"");
            headerWriter.BreakLine();
            headerWriter.WriteLine("namespace cebreiro::odbc { class Connection; }");
            headerWriter.BreakLine();
            headerWriter.WriteLine("namespace cebreiro::gamedb");
            headerWriter.WriteLine("{");

            cxxWriter.WriteLine($"#include \"{GetFileName(result)}.h\"");
            cxxWriter.BreakLine();
            cxxWriter.WriteLine("#include <cstdint>");
            cxxWriter.WriteLine("#include <cassert>");
            cxxWriter.WriteLine("#include <format>");
            cxxWriter.BreakLine();
            cxxWriter.WriteLine($"#include \"{_deserializerFileName}.h\"");
            cxxWriter.WriteLine("#include \"lib/odbc/connection.h\"");
            cxxWriter.BreakLine();
            cxxWriter.WriteLine("namespace cebreiro::gamedb");
            cxxWriter.WriteLine("{");

            foreach (var udt in result.Structs)
            {
                NameUtil util = new NameUtil(udt);

                headerWriter.WriteLine($"\tclass {util.GetClassName()}");
                headerWriter.WriteLine("\t{");
                headerWriter.WriteLine("\tpublic:");

                foreach (var writers in _methodWriters)
                {
                    foreach (var writer in writers)
                    {
                        writer.Write(util, udt, headerWriter, cxxWriter);
                    }

                    headerWriter.BreakLine();
                }

                headerWriter.WriteLine("\tprivate:");
                headerWriter.WriteLine("\t\todbc::Connection& _connection;");
                headerWriter.WriteLine("\t};");
                headerWriter.BreakLine();
            }

            headerWriter.WriteLine("}"); // namespace
            cxxWriter.WriteLine("}");  // namespace

            return new Result(GetFileName(result), headerWriter.Get(), cxxWriter.Get());
        }

        private string GetFileName(HeaderParseResult result)
        {
            return Path.GetFileNameWithoutExtension(result.FileName).ToLower() + "_table";
        }
    }
}
