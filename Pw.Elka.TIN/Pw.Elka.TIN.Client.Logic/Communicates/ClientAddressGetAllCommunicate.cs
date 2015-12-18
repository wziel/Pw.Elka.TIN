using Pw.Elka.TIN.Client.Logic.Parsers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Communicates
{
    internal class ClientAddressGetAllCommunicate: ClientCommunicate
    {
        internal override byte[] GetBytes()
        {
            return ASIAParserData.GetClientCommunicationCodeByType<ClientAddressGetAllCommunicate>();
        }
    }
}
