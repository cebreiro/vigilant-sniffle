using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace db_code_generator.Generate
{
    internal struct Result
    {
        public string FileName;
        public string HeaderContent;
        public string CxxContent;

        public Result(string fileName, string headerContent, string cxxContent)
        {
            FileName = fileName;
            HeaderContent = headerContent;
            CxxContent = cxxContent;
        }
    }
}
