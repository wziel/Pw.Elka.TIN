using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Parsers
{
    internal class ASIAStringListParser
    {
        internal static byte[] GetBytes(List<string> strings)
        {
            var bytes = BitConverter.GetBytes((short)strings.Count);
            for (int i = 0; i < strings.Count; ++i)
            {
                bytes.Concat(ASIAStringParser.GetBytes(strings[i]));
            }
            return bytes.ToArray();
        }

        internal static List<string> GetList(byte[] bytes, int fromIndex, out int newFromIndex)
        {
            var length = BitConverter.ToInt16(bytes, fromIndex);
            fromIndex += 2;
            newFromIndex = 0;

            var list = new List<string>();
            for (int i = 0; i < length; ++i)
            {
                list.Add(ASIAStringParser.GetString(bytes, fromIndex, out newFromIndex));
                fromIndex = newFromIndex;
            }

            return list;
        }
    }
}
