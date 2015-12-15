﻿using Pw.Elka.TIN.Client.Logic.Model.Parsers;
using System.Linq;

namespace Pw.Elka.TIN.Client.Logic.Model.Communicates
{
    internal class ClientGroupDeleteCommunicate : ClientCommunicate
    {
        public int GroupID { get; set; }

        internal override byte[] GetBytes()
        {
            return ASIAParserData.GetClientCommunicationCodeByType<ClientGroupDeleteCommunicate>()
            .Concat(ASIAIntParser.GetBytes(GroupID))
            .ToArray();
        }
    }
}
