using db_code_generator.Parse;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace db_code_generator.Generate.Table
{
    internal static class PathUtil
    {
        public static string GetIncludePath(HeaderParseResult result)
        {
            return $"{result.FileName.Substring(result.FileName.IndexOf("lib/"))}";
        }
    }
}
