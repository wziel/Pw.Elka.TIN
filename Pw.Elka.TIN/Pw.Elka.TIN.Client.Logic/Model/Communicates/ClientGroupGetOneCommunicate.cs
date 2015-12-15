﻿using Pw.Elka.TIN.Client.Logic.Model.Parsers;
using System.Linq;

namespace Pw.Elka.TIN.Client.Logic.Model.Communicates
{
    internal class ClientGroupGetOneCommunicate : ClientCommunicate
    {
        public int GroupID { get; set; }

        internal override byte[] GetBytes()
        {
            return ASIAParserData.GetClientCommunicationCodeByType<ClientGroupGetOneCommunicate>()
            .Concat(ASIAIntParser.GetBytes(GroupID))
            .ToArray();
        }
    }
}
