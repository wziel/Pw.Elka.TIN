using Pw.Elka.TIN.Client.Logic.Parsers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Communicates
{
    internal class ServerAddressGetOneCommunicate : ServerCommunicate
    {
        public int AddressID { get; set; }

        public override void SetFieldsFrom(byte[] bytes)
        {
            int startIndex = 1;
            int newStartIndex = 0;

            AddressID = ASIAIntParser.GetInt(bytes, startIndex, out newStartIndex);
            startIndex = newStartIndex;
        }
    }
}
