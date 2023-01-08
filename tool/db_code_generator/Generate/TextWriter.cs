using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace db_code_generator.Generate
{
    internal class TextWriter
    {
        private readonly StringBuilder _stringBuilder = new();

        public void Write(string text)
        {
            _stringBuilder.Append(text);
        }

        public void WriteLine(string text)
        {
            _stringBuilder.Append($"{text}\r\n");
        }

        public void BreakLine()
        {
            _stringBuilder.Append("\r\n");
        }

        public string Get()
        {
            return _stringBuilder.ToString();
        }
    }
}
