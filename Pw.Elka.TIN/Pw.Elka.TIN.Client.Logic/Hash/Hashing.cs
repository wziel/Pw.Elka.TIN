using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Hash
{
    internal static class Hashing
    {
        internal static int GetDJBHash(string str)
        {
            int hash = 5381;

            for (int i = 0; i < str.Length; i++)
            {
                hash = ((hash << 5) + hash) + str[i];
            }

            return hash;
        }

        internal static string GetXoredString(string str)
        {
            byte[] key = { 143, 87, 133, 84, 123, 101, 68 };
            int minimumStringLength = 16;
            var characters = new char[Math.Max(str.Length, minimumStringLength)];

            for (int i = 0; i < characters.Length; ++i)
            {
                characters[i] = (char)(key[i % key.Length] ^ str[i % str.Length]);
            }
            
            return new string(characters);
        }
    }
}
