using Pw.Elka.TIN.Client.Logic.Model.Parsers;
using System.Linq;

namespace Pw.Elka.TIN.Client.Logic.Model.Communicates
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
