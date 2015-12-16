using Pw.Elka.TIN.Client.Logic.Parsers;

namespace Pw.Elka.TIN.Client.Logic.Communicates
{
    internal class ClientMessageGetAllCommunicate : ClientCommunicate
    {

        internal override byte[] GetBytes()
        {
            return ASIAParserData.GetClientCommunicationCodeByType<ClientMessageGetAllCommunicate>();
        }
    }
}
