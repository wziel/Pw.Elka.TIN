using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Parsers
{
    internal static class ASIAIntParser
    {
        internal static byte[] GetBytes(int number)
        {
            return BitConverter.GetBytes((short)4).Concat(BitConverter.GetBytes(number)).ToArray(); ;
        }

        internal static int GetInt(byte[] bytes, int fromIndex, out int newFromIndex)
        {
            newFromIndex = fromIndex + 2 + 4;
            return BitConverter.ToInt32(bytes, fromIndex + 2);
        }
    }
}
