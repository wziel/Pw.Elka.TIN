using Pw.Elka.TIN.Client.Logic.Model.Parsers;
using System.Linq;

namespace Pw.Elka.TIN.Client.Logic.Model.Communicates
{
    internal class ClientMessageCreateCommunicate : ClientCommunicate
    {
        public string MessageTemplate { get; set; }
        public string MessageName { get; set; }
        
        internal override byte[] GetBytes()
        {
            return ASIAParserData.GetClientCommunicationCodeByType<ClientMessageCreateCommunicate>()
            .Concat(ASIAStringParser.GetBytes(MessageTemplate))
            .Concat(ASIAStringParser.GetBytes(MessageName))
            .ToArray();
        }
    }
}
