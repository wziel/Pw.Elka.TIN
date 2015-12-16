using Pw.Elka.TIN.Client.Logic.Parsers;
using System.Linq;

namespace Pw.Elka.TIN.Client.Logic.Communicates
{
    internal class ClientMessageGetOneCommunicate : ClientCommunicate
    {
        public int MessageID { get; set; }

        internal override byte[] GetBytes()
        {
            return ASIAParserData.GetClientCommunicationCodeByType<ClientMessageGetOneCommunicate>()
            .Concat(ASIAIntParser.GetBytes(MessageID))
            .ToArray();
        }
    }
}
