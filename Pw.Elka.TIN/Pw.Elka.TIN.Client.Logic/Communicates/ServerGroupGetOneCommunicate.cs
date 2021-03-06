﻿using Pw.Elka.TIN.Client.Logic.Parsers;
using System.Collections.Generic;

namespace Pw.Elka.TIN.Client.Logic.Communicates
{
    internal class ServerGroupGetOneCommunicate : ServerCommunicate
    {
        public int GroupID { get; set; }
        public string GroupName { get; set; }
        public List<int> AddressIDs { get; set; }
        public List<string> AddressValues { get; set; }

        public override void SetFieldsFrom(byte[] bytes)
        {
            int startIndex = 1;
            int newStartIndex = 0;

            GroupID = ASIAIntParser.GetInt(bytes, startIndex, out newStartIndex);
            startIndex = newStartIndex;

            GroupName = ASIAStringParser.GetString(bytes, startIndex, out newStartIndex);
            startIndex = newStartIndex;

            AddressIDs = ASIAIntListParser.GetList(bytes, startIndex, out newStartIndex);
            startIndex = newStartIndex;

            AddressValues = ASIAStringListParser.GetList(bytes, startIndex, out newStartIndex);
            startIndex = newStartIndex;
        }
    }
}
