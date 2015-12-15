using Pw.Elka.TIN.Client.Logic.Model.Parsers;
using System.Collections.Generic;

namespace Pw.Elka.TIN.Client.Logic.Model.Communicates
{
    internal class ServerGroupGetAllCommunicate : ServerCommunicate
    {
        public List<int> GroupIDs { get; set; }
        public List<string> GroupNames { get; set; }

        internal override void SetFieldsFrom(byte[] bytes)
        {
            int startIndex = 1;
            int newStartIndex = 0;

            GroupIDs = ASIAIntListParser.GetList(bytes, startIndex, out newStartIndex);
            startIndex = newStartIndex;

            GroupNames = ASIAStringListParser.GetList(bytes, startIndex, out newStartIndex);
            startIndex = newStartIndex;
        }
    }
}
