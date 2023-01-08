using System.Text;
using ClangSharp.Interop;

namespace db_code_generator.Parse
{
    internal class Struct
    {
        public class Column
        {
            public uint Line { get; }
            public string TypeName { get; }
            public string FieldName { get; }
            public Option? Option { get; set; } = null;

            public Column(CXTranslationUnit tu, CXCursor cursor)
            {
                Line = cursor.GetLine();
                TypeName = cursor.Type.Spelling.ToString();
                FieldName = cursor.Spelling.ToString();

                if (!CheckTypeName(TypeName))
                {
                    throw new InvalidOperationException($"unsupported type. file: {tu.Spelling}, type: {TypeName}");
                }
            }

            private static bool CheckTypeName(string typeName)
            {
                if (SupportTypes.Any((type => type == typeName)))
                {
                    return true;
                }

                if (typeName.StartsWith("std::optional"))
                {
                    if (typeName.Count(c => c == '<') >= 2)
                    {
                        return false;
                    }

                    var split = typeName.Split('<', '>');
                    return SupportTypes.Any((type => type == split[1]));
                }

                return false;
            }

            private static readonly IReadOnlyList<string> SupportTypes = new List<string>()
            {
                "int8_t", "uint8_t",
                "int16_t", "uint16_t",
                "int32_t", "uint32_t",
                "int64_t",
                "float", "double",
                "std::string"
            };
        }

        public uint Line { get; }
        public string Name { get; }
        public List<Column> Columns { get; } = new();
        public List<string> Namespaces { get; } = new();

        public Struct(CXTranslationUnit tu, CXCursor cursor)
        {
            Line = cursor.GetLine();
            Name = cursor.Spelling.ToString();

            for (int i = 0; i < cursor.NumFields; ++i)
            {
                Columns.Add(new Column(tu, cursor.GetField((uint)i)));
            }

            CXCursor current = cursor;
            CXCursor next = CXCursor.Null;

            while (true)
            {
                next = current.SemanticParent;
                current = next;

                if (next == CXCursor.Null || next.kind != CXCursorKind.CXCursor_Namespace)
                {
                    break;
                }

                Namespaces.Insert(0, next.Spelling.ToString());
            }
        }

        public string GetFullName()
        {
            StringBuilder builder = new StringBuilder();

            foreach (var ns in Namespaces)
            {
                builder.Append(ns);
                builder.Append("::");
            }

            builder.Append(Name);
            return builder.ToString();
        }
    }
}
