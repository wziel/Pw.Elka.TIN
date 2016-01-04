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
            for(int i = 0; i < str.Length; ++ i)
            {
                strBytes[i] = (byte)str[i];
            }
            return lengthBytes.Concat(strBytes).ToArray();
        }

        internal static string GetString(byte[] bytes, int fromIndex, out int newFromIndex, int? stringKnownLength = null)
        {
            var length = stringKnownLength.HasValue ? stringKnownLength.Value : BitConverter.ToInt16(bytes, fromIndex);
            fromIndex += 2;
            newFromIndex = fromIndex + length;

            var characters = new char[length];
            for(int i = 0; i < length; ++i)
            {
                characters[i] = (char)bytes[i + fromIndex];
            }
            return new string(characters);
        }
    }
}
