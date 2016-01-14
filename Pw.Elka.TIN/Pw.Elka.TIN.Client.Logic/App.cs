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
        private string _salt;

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

        internal ServerCommunicate Authorize(string login, string password)
        {
            var auth = (ServerAuthCommunicate)_session.ReceiveCommunicate();
            _salt = auth.Salt;

            password = Hashing.GetXoredString(password);

            _session.SendCommunicate(new ClientAuthCommunicate()
            {
                Login = login,
                Passwhash = Hashing.GetDJBHash(password + _salt)
            });
            return _session.ReceiveCommunicate();
        }

        internal ServerCommunicate MessageCreate(string template, string name)
        {
            _session.SendCommunicate(new ClientMessageCreateCommunicate()
            {
                MessageName = name,
                MessageTemplate = template
            });
            return _session.ReceiveCommunicate();
        }

        internal ServerCommunicate MessageModyify(string template, string name, int id)
        {
            _session.SendCommunicate(new ClientMessageModifyCommunicate()
            {
                MessageID = id,
                MessageName = name,
                MessageTemplate = template
            });
            return _session.ReceiveCommunicate();
        }

        internal ServerCommunicate MessageDelete(int id)
        {
            _session.SendCommunicate(new ClientMessageDeleteCommunicate()
            {
                MessageID = id
            });
            return _session.ReceiveCommunicate();
        }

        internal ServerCommunicate MessageGetAll()
        {
            _session.SendCommunicate(new ClientMessageGetAllCommunicate());
            return _session.ReceiveCommunicate();
        }

        internal ServerCommunicate MessageGetOne(int id)
        {
            _session.SendCommunicate(new ClientMessageGetOneCommunicate()
            {
                MessageID = id
            });
            return _session.ReceiveCommunicate();
        }

        internal ServerCommunicate GroupCreate(string name)
        {
            _session.SendCommunicate(new ClientGroupCreateCommunicate()
            {
                GroupName = name
            });
            return _session.ReceiveCommunicate();
        }

        internal ServerCommunicate GroupDelete(int id)
        {
            _session.SendCommunicate(new ClientGroupDeleteCommunicate()
            {
                GroupID = id
            });
            return _session.ReceiveCommunicate();
        }

        internal ServerCommunicate GroupGetOne(int id)
        {
            _session.SendCommunicate(new ClientGroupGetOneCommunicate()
            {
                GroupID = id
            });
            return _session.ReceiveCommunicate();
        }

        internal ServerCommunicate GroupGetAll()
        {
            _session.SendCommunicate(new ClientGroupGetAllCommunicate());
            return _session.ReceiveCommunicate();
        }

        internal ServerCommunicate GroupAddressAdd(int groupid, int addressId)
        {
            _session.SendCommunicate(new ClientGroupAddressAddCommunicate()
            {
                GroupID = groupid,
                AddressID = addressId
            });
            return _session.ReceiveCommunicate();
        }

        internal ServerCommunicate GroupAddressRemove(int groupId, int addressId)
        {
            _session.SendCommunicate(new ClientGroupAddressRemoveCommunicate()
            {
                AddressID = addressId,
                GroupID = groupId
            });
            return _session.ReceiveCommunicate();
        }

        internal ServerCommunicate Send(int groupId, int messageId, List<string>templateValues)
        {
            _session.SendCommunicate(new ClientSendCommunicate()
            {
                GroupID = groupId,
                MessageID = messageId,
                TemplateValues = templateValues
            });
            return _session.ReceiveCommunicate();
        }

        internal ServerCommunicate PasswordChange(string oldPassword, string newPassword)
        {
            oldPassword = Hashing.GetXoredString(oldPassword);
            newPassword = Hashing.GetXoredString(newPassword);

            _session.SendCommunicate(new ClientPasswordChangeCommunicate()
            {
                PasswordHash = oldPassword,
                NewPasswordHash = newPassword
            });
            return _session.ReceiveCommunicate();
        }

        internal ServerCommunicate AddressAdd(string addressValue, string addresseeName)
        {
            _session.SendCommunicate(new ClientAddressAddCommunicate()
            {
                AddressValue = addressValue,
                AddresseeName = addresseeName
            });
            return _session.ReceiveCommunicate();
        }

        internal ServerCommunicate AddressRemove(int addressId)
        {
            _session.SendCommunicate(new ClientAddressRemoveCommunicate()
            {
                AddressID = addressId
            });
            return _session.ReceiveCommunicate();
        }

        internal ServerCommunicate AddressGetAll()
        {
            _session.SendCommunicate(new ClientAddressGetAllCommunicate());
            return _session.ReceiveCommunicate();
        }
    }
}
