using Pw.Elka.TIN.Client.Logic.Parsers;
using System.Linq;

namespace Pw.Elka.TIN.Client.Logic.Communicates
{
    internal class ClientGroupAddressAddCommunicate : ClientCommunicate
    {
        public int GroupID { get; set; }
        public string AddressValue { get; set; }

        internal override byte[] GetBytes()
        {
            return ASIAParserData.GetClientCommunicationCodeByType<ClientGroupAddressAddCommunicate>()
            .Concat(ASIAIntParser.GetBytes(GroupID))
            .Concat(ASIAStringParser.GetBytes(AddressValue))
            .ToArray();
        }
    }
}
