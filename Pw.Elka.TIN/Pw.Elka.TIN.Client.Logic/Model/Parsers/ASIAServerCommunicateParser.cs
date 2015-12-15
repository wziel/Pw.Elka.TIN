using Pw.Elka.TIN.Client.Logic.Model.Communicates;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Model.Parsers
{
    static internal class ASIAServerCommunicateParser
    {
        internal static ServerCommunicate GetCommunicateFromBytes(byte[] bytes)
        {
            var type = ASIAParserData.GetServerCommunicateTypeByCode(bytes[0]);
            var serverCommunicate = (ServerCommunicate)Activator.CreateInstance(type);
            serverCommunicate.SetFieldsFrom(bytes);
            return serverCommunicate;
        }
    }
}
