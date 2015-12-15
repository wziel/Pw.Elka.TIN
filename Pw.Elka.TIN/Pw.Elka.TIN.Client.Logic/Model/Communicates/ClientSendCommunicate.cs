using Pw.Elka.TIN.Client.Logic.Model.Parsers;
using System.Collections.Generic;
using System.Linq;

namespace Pw.Elka.TIN.Client.Logic.Model.Communicates
{
    internal class ClientSendCommunicate : ClientCommunicate
    {
        public int GroupID { get; set; }
        public int MessageID { get; set; }
        public List<string> TemplateValues { get; set; }

        internal override byte[] GetBytes()
        {
            return ASIAParserData.GetClientCommunicationCodeByType<ClientSendCommunicate>()
            .Concat(ASIAIntParser.GetBytes(GroupID))
            .Concat(ASIAIntParser.GetBytes(MessageID))
            .Concat(ASIAStringListParser.GetBytes(TemplateValues))
            .ToArray();
        }
    }
}
