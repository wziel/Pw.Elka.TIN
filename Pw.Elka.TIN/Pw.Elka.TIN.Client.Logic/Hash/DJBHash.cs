using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Hash
{
    internal static class DJBHash
    {
        internal static string GetHash(string str, int salt)
        {
            int hash = salt;
            
            for (int i = 0; i < str.Length; i++)
            {
                hash = ((hash << 5) + hash) + str[i];
            }

            return hash.ToString();
        }
    }
}
