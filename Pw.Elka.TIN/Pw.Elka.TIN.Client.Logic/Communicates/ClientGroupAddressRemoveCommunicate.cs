﻿using Pw.Elka.TIN.Client.Logic.Parsers;
using System.Linq;

namespace Pw.Elka.TIN.Client.Logic.Communicates
{
    internal class ClientGroupAddressRemoveCommunicate : ClientCommunicate
    {
        public int GroupID { get; set; }
        public int AddressID { get; set; }

        internal override byte[] GetBytes()
        {
            return ASIAParserData.GetClientCommunicationCodeByType<ClientGroupAddressRemoveCommunicate>()
            .Concat(ASIAIntParser.GetBytes(GroupID))
            .Concat(ASIAIntParser.GetBytes(AddressID))
            .ToArray();
        }
    }
}
