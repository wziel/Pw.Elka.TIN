using Pw.Elka.TIN.Client.Logic.Parsers;
using System.Collections.Generic;

namespace Pw.Elka.TIN.Client.Logic.Communicates
{
    internal class ServerMessageGetAllCommunicate : ServerCommunicate
    {
        public List<int> MessageIDs { get; set; }
        public List<string> MessageNames { get; set; }

        public override void SetFieldsFrom(byte[] bytes)
        {
            int startIndex = 1;
            int newStartIndex = 0;

            MessageIDs = ASIAIntListParser.GetList(bytes, startIndex, out newStartIndex);
            startIndex = newStartIndex;

            MessageNames = ASIAStringListParser.GetList(bytes, startIndex, out newStartIndex);
            startIndex = newStartIndex;
        }
    }
}
