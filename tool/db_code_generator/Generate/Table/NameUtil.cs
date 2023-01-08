using db_code_generator.Parse;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace db_code_generator.Generate.Table
{
    internal class NameUtil
    {
        private readonly Struct _udt;

        public NameUtil(Struct udt)
        {
            _udt = udt;
        }

        public string GetClassName()
        {
            return $"{_udt.Name}Table";
        }

        public string GetDbTableName()
        {
            return _udt.Name;
        }
    }
}
