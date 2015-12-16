using Pw.Elka.TIN.Client.Logic.Communicates;
using Pw.Elka.TIN.Client.Logic.Hash;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic
{
    public class App
    {
        private SessionLayer _session;
        private XorCipher _cipher;
        private TCPLayer _tcp;

        public App(string serverAddress, int serverPort)
        {
            _tcp = new TCPLayer(serverPort, serverAddress);
            _cipher = new XorCipher(_tcp);
            _session = new SessionLayer(_cipher);
        }

        public void Connect()
        {
            _tcp.Connect();
        }

        public ServerCommunicate Authorize(string login, string password)
        {
            var auth = (ServerAuthCommunicate)_session.ReceiveCommunicate();

            //todo get salt (is it int or string? aska Asia)
            throw new NotImplementedException();

            _session.SendCommunicate(new ClientAuthCommunicate()
            {
                Login = login,
                Passwhash = DJBHash.GetHash(password, 0)
            });
            return _session.ReceiveCommunicate();
        }

        public ServerCommunicate MessageCreate(string template, string name)
        {
            _session.SendCommunicate(new ClientMessageCreateCommunicate()
            {
                MessageName = name,
                MessageTemplate = template
            });
            return _session.ReceiveCommunicate();
        }

        public ServerCommunicate MessageModyify(string template, string name, int id)
        {
            _session.SendCommunicate(new ClientMessageModifyCommunicate()
            {
                MessageID = id,
                MessageName = name,
                MessageTemplate = template
            });
            return _session.ReceiveCommunicate();
        }

        public ServerCommunicate MessageDelete(int id)
        {
            _session.SendCommunicate(new ClientMessageDeleteCommunicate()
            {
                MessageID = id
            });
            return _session.ReceiveCommunicate();
        }

        public ServerCommunicate MessageGetAll()
        {
            _session.SendCommunicate(new ClientMessageGetAllCommunicate());
            return _session.ReceiveCommunicate();
        }

        public ServerCommunicate MessageGetOne(int id)
        {
            _session.SendCommunicate(new ClientMessageGetOneCommunicate()
            {
                MessageID = id
            });
            return _session.ReceiveCommunicate();
        }

        public ServerCommunicate GroupCreate(string name)
        {
            _session.SendCommunicate(new ClientGroupCreateCommunicate()
            {
                GroupName = name
            });
            return _session.ReceiveCommunicate();
        }

        public ServerCommunicate GroupDelete(int id)
        {
            _session.SendCommunicate(new ClientGroupDeleteCommunicate()
            {
                GroupID = id
            });
            return _session.ReceiveCommunicate();
        }

        public ServerCommunicate GroupGetOne(int id)
        {
            _session.SendCommunicate(new ClientGroupGetOneCommunicate()
            {
                GroupID = id
            });
            return _session.ReceiveCommunicate();
        }

        public ServerCommunicate GroupGetAll()
        {
            _session.SendCommunicate(new ClientGroupGetAllCommunicate());
            return _session.ReceiveCommunicate();
        }

        public ServerCommunicate GroupAddressAdd(int groupid, string addressValue)
        {
            _session.SendCommunicate(new ClientGroupAddressAddCommunicate()
            {
                GroupID = groupid,
                AddressValue = addressValue
            });
            return _session.ReceiveCommunicate();
        }

        public ServerCommunicate GroupAddressRemove(int addressId)
        {
            _session.SendCommunicate(new ClientGroupAddressRemoveCommunicate()
            {
                AddressID = addressId
            });
            return _session.ReceiveCommunicate();
        }

        public ServerCommunicate Send(int groupId, int messageId, List<string>templateValues)
        {
            _session.SendCommunicate(new ClientSendCommunicate()
            {
                GroupID = groupId,
                MessageID = messageId,
                TemplateValues = templateValues
            });
            return _session.ReceiveCommunicate();
        }

        public ServerCommunicate PasswordChange(string oldPassword, string newPassword)
        {

            //todo - the same as in authorize method, ask Asia what is salt
            throw new NotImplementedException();
        }
    }
}
