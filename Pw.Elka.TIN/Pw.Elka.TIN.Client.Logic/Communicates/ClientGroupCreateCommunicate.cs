using Pw.Elka.TIN.Client.Logic.Parsers;
using System.Linq;

namespace Pw.Elka.TIN.Client.Logic.Communicates
{
    internal class ClientGroupCreateCommunicate : ClientCommunicate
    {
        public string GroupName { get; set; }

        internal override byte[] GetBytes()
        {
            return ASIAParserData.GetClientCommunicationCodeByType<ClientGroupCreateCommunicate>()
            .Concat(ASIAStringParser.GetBytes(GroupName))
            .ToArray();
        }
    }
}
