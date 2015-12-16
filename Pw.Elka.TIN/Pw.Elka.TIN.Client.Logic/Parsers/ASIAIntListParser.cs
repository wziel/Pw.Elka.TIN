using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Parsers
{
    internal class ASIAIntListParser
    {
        internal static byte[] GetBytes(List<int> numbers)
        {
            var bytes = BitConverter.GetBytes((short)numbers.Count);
            for(int i = 0; i < numbers.Count; ++i)
            {
                bytes.Concat(ASIAIntParser.GetBytes(numbers[i]));
            }
            return bytes.ToArray();
        }

        internal static List<int> GetList(byte[] bytes, int fromIndex, out int newFromIndex)
        {
            var length = BitConverter.ToInt16(bytes, fromIndex);
            fromIndex += 2;
            newFromIndex = 0;

            var list = new List<int>();
            for(int i = 0; i < length; ++i)
            {
                list.Add(ASIAIntParser.GetInt(bytes, fromIndex, out newFromIndex));
                fromIndex = newFromIndex;
            }

            return list;
        }
    }
}
