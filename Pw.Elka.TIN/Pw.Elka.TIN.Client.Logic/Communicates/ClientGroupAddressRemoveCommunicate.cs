using Pw.Elka.TIN.Client.Logic.Parsers;
using System.Linq;

namespace Pw.Elka.TIN.Client.Logic.Communicates
{
    internal class ClientGroupAddressRemoveCommunicate : ClientCommunicate
    {
        public int AddressID { get; set; }

        internal override byte[] GetBytes()
        {
            return ASIAParserData.GetClientCommunicationCodeByType<ClientGroupAddressRemoveCommunicate>()
            .Concat(ASIAIntParser.GetBytes(AddressID))
            .ToArray();
        }
    }
}
