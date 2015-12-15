using Pw.Elka.TIN.Client.Logic.Model.Parsers;

namespace Pw.Elka.TIN.Client.Logic.Model.Communicates
{
    internal class ClientMessageGetAllCommunicate : ClientCommunicate
    {

        internal override byte[] GetBytes()
        {
            return ASIAParserData.GetClientCommunicationCodeByType<ClientMessageGetAllCommunicate>();
        }
    }
}
