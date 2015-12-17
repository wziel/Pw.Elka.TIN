using Pw.Elka.TIN.Client.Logic.Communicates;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Parsers
{
    internal static class ASIAParserData
    {
        private static Dictionary<Type, byte> ClientCommunicateToCode { get; set; }
            = new Dictionary<Type, byte>()
        {
                { typeof(ClientAuthCommunicate), 0x00 },
                { typeof(ClientMessageCreateCommunicate), 0x02 },
                { typeof(ClientMessageModifyCommunicate), 0x03 },
                { typeof(ClientMessageDeleteCommunicate), 0x04 },
                { typeof(ClientMessageGetAllCommunicate), 0x05 },
                { typeof(ClientMessageGetOneCommunicate), 0x06 },
                { typeof(ClientGroupCreateCommunicate), 0x07 },
                { typeof(ClientGroupDeleteCommunicate), 0x08 },
                { typeof(ClientGroupGetOneCommunicate), 0x09 },
                { typeof(ClientGroupGetAllCommunicate), 0x0A },
                { typeof(ClientGroupAddressAddCommunicate), 0x0B },
                { typeof(ClientGroupAddressRemoveCommunicate), 0x0C },
                { typeof(ClientSendCommunicate), 0x0D },
                { typeof(ClientPasswordChangeCommunicate), 0x0E },
        };

        private static Dictionary<byte, Type> ServerCommunicateToCode { get; set; }
            = new Dictionary<byte, Type>()
        {
                { 0x00, typeof(ServerAuthCommunicate)},
                { 0x01, typeof(ServerAckCommunicate)},
                { 0x05, typeof(ServerMessageGetAllCommunicate)},
                { 0x06, typeof(ServerMessageGetOneCommunicate)},
                { 0x09, typeof(ServerGroupGetOneCommunicate)},
                { 0x0A, typeof(ServerGroupGetAllCommunicate)},
                { 0x0F, typeof(ServerErrorNotAuthorizedCommunicate)},
                { 0x10, typeof(ServerErrorBusyCommunicate)},
                { 0x12, typeof(ServerErrorBadRequestCommunicate)},
                { 0x13, typeof(ServerErrorBadContentCommunicate)},
                { 0x14, typeof(ServerErrorBadGroupCommunicate)},
                { 0x15, typeof(ServerErrorBadMessageCommunicate)},
                { 0x16, typeof(ServerErrorServerNotAvailableCommunicate)},
                { 0x17, typeof(ServerGroupAddressGetOneCommunicate) }
        };

        internal static byte[] GetClientCommunicationCodeByType<C>() where C : ClientCommunicate
        {
            return new byte[] { ClientCommunicateToCode[typeof(C)] };
        }

        internal static Type GetServerCommunicateTypeByCode(byte code)
        {
            return ServerCommunicateToCode[code];
        }
    }
}
