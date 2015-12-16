using Pw.Elka.TIN.Client.Logic.Parsers;
using System.Linq;

namespace Pw.Elka.TIN.Client.Logic.Communicates
{
    internal class ClientMessageDeleteCommunicate : ClientCommunicate
    {
        public int MessageID { get; set; }

        internal override byte[] GetBytes()
        {
            return ASIAParserData.GetClientCommunicationCodeByType<ClientMessageDeleteCommunicate>()
            .Concat(ASIAIntParser.GetBytes(MessageID))
            .ToArray();
        }
    }
}
