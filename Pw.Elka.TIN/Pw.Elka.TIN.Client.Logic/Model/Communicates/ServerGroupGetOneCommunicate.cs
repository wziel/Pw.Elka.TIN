using Pw.Elka.TIN.Client.Logic.Model.Parsers;
using System.Collections.Generic;

namespace Pw.Elka.TIN.Client.Logic.Model.Communicates
{
    internal class ServerGroupGetOneCommunicate : ServerCommunicate
    {
        public int GroupID { get; set; }
        public string GroupName { get; set; }
        public List<int> AddressID { get; set; }
        public List<int> AddressValuse { get; set; }

        internal override void SetFieldsFrom(byte[] bytes)
        {
            int startIndex = 1;
            int newStartIndex = 0;

            GroupID = ASIAIntParser.GetInt(bytes, startIndex, out newStartIndex);
            startIndex = newStartIndex;

            GroupName = ASIAStringParser.GetString(bytes, startIndex, out newStartIndex);
            startIndex = newStartIndex;

            AddressID = ASIAIntListParser.GetList(bytes, startIndex, out newStartIndex);
            startIndex = newStartIndex;

            AddressValuse = ASIAIntListParser.GetList(bytes, startIndex, out newStartIndex);
            startIndex = newStartIndex;
        }
    }
}
