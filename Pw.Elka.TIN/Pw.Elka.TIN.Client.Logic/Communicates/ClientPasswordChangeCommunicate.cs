using Pw.Elka.TIN.Client.Logic.Parsers;
using System.Linq;

namespace Pw.Elka.TIN.Client.Logic.Communicates
{
    internal class ClientPasswordChangeCommunicate : ClientCommunicate
    {
        public string PasswordHash { get; set; }
        public string NewPasswordHash { get; set; }

        internal override byte[] GetBytes()
        {
            return ASIAParserData.GetClientCommunicationCodeByType<ClientPasswordChangeCommunicate>()
            .Concat(ASIAStringParser.GetBytes(PasswordHash))
            .Concat(ASIAStringParser.GetBytes(NewPasswordHash))
            .ToArray();
        }
    }
}
