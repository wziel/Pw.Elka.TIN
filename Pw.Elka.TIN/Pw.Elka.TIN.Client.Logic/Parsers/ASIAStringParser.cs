using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Parsers
{
    internal static class ASIAStringParser
    {
        internal static byte[] GetBytes(string str)
        {
            var lengthBytes = BitConverter.GetBytes((short)str.Length);
            var strBytes = new byte[str.Length];
            Buffer.BlockCopy(str.ToCharArray(), 0, strBytes, 0, str.Length);
            return lengthBytes.Concat(strBytes).ToArray();
        }

        internal static string GetString(byte[] bytes, int fromIndex, out int newFromIndex)
        {
            var length = BitConverter.ToInt16(bytes, fromIndex);
            fromIndex += 2;
            newFromIndex = 0;

            var characters = new char[length];
            Buffer.BlockCopy(bytes, fromIndex, characters, 0, length);
            return new string(characters);
        }
    }
}
