using Pw.Elka.TIN.Client.Logic.Parsers;
using System;
using System.Linq;

namespace Pw.Elka.TIN.Client.Logic.Communicates
{
    internal class ClientAuthCommunicate : ClientCommunicate
    {
        public string Login { get; set; }
        public int Passwhash { get; set; }

        internal override byte[] GetBytes()
        {
            return ASIAParserData.GetClientCommunicationCodeByType<ClientAuthCommunicate>()
            .Concat(ASIAStringParser.GetBytes(Login))
            .Concat(ASIAIntParser.GetBytes(Passwhash))
            .ToArray();
        }
    }
}
