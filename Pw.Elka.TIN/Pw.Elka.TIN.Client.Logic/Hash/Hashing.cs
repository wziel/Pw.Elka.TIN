using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Hash
{
    public static class Hashing
    {
        public static int GetDJBHash(string str)
        {
            int hash = 5381;

            for (int i = 0; i < str.Length; i++)
            {
                hash = ((hash << 5) + hash) + str[i];
            }

            return hash;
        }

        public static string GetObfuscatedString(string str)
        {
            byte[] key = { 143, 87, 133, 84, 123, 101, 68 };
            int minimumStringLength = 32;
            var characters = new char[Math.Max(str.Length, minimumStringLength)];
            var summedChars = 5381;

            for (int i = 0; i < characters.Length; ++i)
            {
                char c = (char)(key[i % key.Length] ^ str[i % str.Length]);
                summedChars += (int)c;

                characters[i] = (char)('0' + (summedChars % 10));
            }

            return new string(characters);
        }
    }
}
