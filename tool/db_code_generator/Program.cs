using System.Runtime.CompilerServices;
using ClangSharp.Interop;
using db_code_generator.Generate.ODBC;
using db_code_generator.Generate.Table;
using db_code_generator.Parse;

try
{
    // string targetFile = Environment.GetCommandLineArgs()[1];

    List<HeaderParseResult> parseResults = new List<HeaderParseResult>();
    string[] options = { "-x", "c++", "--std=c++20" };

    var files = Directory.GetFiles("F:/repos/cebreiro/lib/game_base/db/", "*.h", SearchOption.TopDirectoryOnly);
    foreach (var file in files)
    {
        var index = CXIndex.Create();
        var tu = CXTranslationUnit.Parse(
            index,
            file,
            options,
            Array.Empty<CXUnsavedFile>(),
            CXTranslationUnit_Flags.CXTranslationUnit_DetailedPreprocessingRecord);
        if (tu == null)
        {
            throw new Exception("translate unit is null");
        }

        HeaderParseResult result = new HeaderParseResult(tu, tu.Cursor);
        parseResults.Add(result);
    }


    DeserializerWriter deserializerWriter = new DeserializerWriter();
    var deserializer = deserializerWriter.GenerateSourceFile(parseResults);

    ClassWriter classWriter = new ClassWriter(deserializer.FileName);
    var results = classWriter.GenerateSourceFile(parseResults);

    foreach (var result in results)
    {
        File.WriteAllText(Path.Combine("F:/test/", $"{result.FileName}.h"), result.HeaderContent);
        File.WriteAllText(Path.Combine("F:/test/", $"{result.FileName}.cpp"), result.CxxContent);
    }

    File.WriteAllText(Path.Combine("F:/test/", $"{deserializer.FileName}.h"), deserializer.HeaderContent);
    File.WriteAllText(Path.Combine("F:/test/", $"{deserializer.FileName}.cpp"), deserializer.CxxContent);

    Console.WriteLine("end");
}
catch (Exception e)
{
    Console.WriteLine($"exception: {e.Message}\n{e.StackTrace}");
}
