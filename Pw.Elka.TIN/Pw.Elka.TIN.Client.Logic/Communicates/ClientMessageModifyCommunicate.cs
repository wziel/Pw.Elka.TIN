using Pw.Elka.TIN.Client.Logic.Parsers;
using System.Linq;

namespace Pw.Elka.TIN.Client.Logic.Communicates
{
    internal class ClientMessageModifyCommunicate : ClientCommunicate
    {
        public int MessageID { get; set; }
        public string MessageTemplate { get; set; }
        public string MessageName { get; set; }
        
        internal override byte[] GetBytes()
        {
            return ASIAParserData.GetClientCommunicationCodeByType<ClientMessageModifyCommunicate>()
            .Concat(ASIAIntParser.GetBytes(MessageID))
            .Concat(ASIAStringParser.GetBytes(MessageTemplate))
            .Concat(ASIAStringParser.GetBytes(MessageName))
            .ToArray();
        }
    }
}
