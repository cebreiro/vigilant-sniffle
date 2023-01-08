using db_code_generator.Parse;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace db_code_generator.Generate.Table.Method
{
    internal interface IClassMethodWriter
    {
        void Write(NameUtil util, Struct udt, TextWriter headerWriter, TextWriter cxxWriter);
    }
}
