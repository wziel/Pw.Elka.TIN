using Pw.Elka.TIN.Client.Logic.Communicates;
using Pw.Elka.TIN.Client.Logic.Exceptions;
using Pw.Elka.TIN.Client.Logic.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic
{
    public class AppDAL : Interfaces.AppDAL
    {
        private Logic.App _appLogic;

        public AppDAL(Logic.App application)
        {
            _appLogic = application;
        }


        private List<GroupModel> _groupModels;

        public List<GroupModel> GroupModels
        {
            get
            {
                if (_groupModels == null)
                {
                    var serverCommunicate = _appLogic.GroupGetAll();
                    var communicate = serverCommunicate as ServerGroupGetAllCommunicate;
                    if (communicate == null)
                    {
                        throw new NotImplementedException();
                    }
                    _groupModels = new List<GroupModel>();
                    for (int i = 0; i < communicate.GroupIDs.Count; ++i)
                    {
                        _groupModels.Add(new GroupModel()
                        {
                            Id = communicate.GroupIDs[i],
                            Name = communicate.GroupNames[i],
                            Addresses = null
                        });
                    }
                    _groupModels = _groupModels.OrderBy(g => g.Name).ToList();
                }
                return _groupModels;
            }
        }

        private List<MessageModel> _messagrModels;

        public List<MessageModel> MessageModels
        {
            get
            {
                if (_messagrModels == null)
                {
                    var serverCommunicate = _appLogic.MessageGetAll();
                    var communicate = serverCommunicate as ServerMessageGetAllCommunicate;
                    if (communicate == null)
                    {
                        throw new NotImplementedException();
                    }
                    _messagrModels = new List<MessageModel>();
                    for (int i = 0; i < communicate.MessageIDs.Count; ++i)
                    {
                        _messagrModels.Add(new MessageModel()
                        {
                            Id = communicate.MessageIDs[i],
                            Name = communicate.MessageNames[i],
                            Content = null
                        });
                    }
                    _messagrModels = _messagrModels.OrderBy(m => m.Name).ToList();
                }
                return _messagrModels;
            }
        }

        private List<AddressModel> _addressModels;

        public List<AddressModel> AddressModels
        {
            get
            {
                if (_addressModels == null)
                {
                    var serverCommunicate = _appLogic.AddressGetAll();
                    var communicate = serverCommunicate as ServerAddressGetAllCommunicate;
                    if (communicate == null)
                    {
                        throw new NotImplementedException();
                    }
                    _addressModels = new List<AddressModel>();
                    for (int i = 0; i < communicate.AddressIds.Count; ++i)
                    {
                        _addressModels.Add(new AddressModel()
                        {
                            AdresseeName = communicate.AddressNames[i],
                            Value = communicate.AddressValues[i],
                            Id = communicate.AddressIds[i]
                        });
                    }
                    _addressModels = _addressModels.OrderBy(a => a.AdresseeName).ToList();
                }
                return _addressModels;
            }
        }


        public GroupModel GroupModelGetById(int id)
        {
            var groupModel = GroupModels.Single(g => g.Id == id);
            if (groupModel.Addresses == null)
            {
                var serverCommunicate = _appLogic.GroupGetOne(id);
                var communicate = serverCommunicate as ServerGroupGetOneCommunicate;
                if (communicate == null)
                {
                    if (serverCommunicate is ServerErrorBadGroupCommunicate)
                    {
                        throw new BadGroupException();
                    }
                    throw new NotImplementedException();
                }
                groupModel.Addresses = new List<AddressModel>();
                for (int i = 0; i < communicate.AddressIDs.Count; ++i)
                {
                    var addrModel = AddressModels.FirstOrDefault(a => a.Id == communicate.AddressIDs[i]) ??
                        new AddressModel()
                        {
                            Id = communicate.AddressIDs[i],
                            Value = communicate.AddressValues[i]
                        };
                    groupModel.Addresses.Add(addrModel);
                }
            }
            return groupModel;
        }

        public MessageModel MessageModelGetById(int id)
        {
            var messageModel = MessageModels.Single(m => m.Id == id);
            if (messageModel.Content == null)
            {
                var serverCommunicate = _appLogic.MessageGetOne(id);
                var communicate = serverCommunicate as ServerMessageGetOneCommunicate;
                if (communicate == null)
                {
                    throw new NotImplementedException();
                }
                messageModel.Content = communicate.MessageTemplate;
            }
            return messageModel;
        }

        public void GroupModelAddressAdd(int groupId, int addressId)
        {
            var groupModel = GroupModelGetById(groupId);
            var serverCommunicate = _appLogic.GroupAddressAdd(groupId, addressId);
            var communicate = serverCommunicate as ServerAckCommunicate;
            if (communicate == null)
            {
                if (serverCommunicate is ServerErrorBadGroupCommunicate)
                {
                    throw new BadGroupException();
                }
                if (serverCommunicate is ServerErrorBadAddressCommunicate)
                {
                    throw new BadAddressException();
                }
                throw new NotImplementedException();
            }
            var address = AddressModels.Single(a => a.Id == addressId);
            groupModel.Addresses.Add(address);
        }

        public void GroupModelAddressRemove(int addressId, int groupId)
        {
            var groupModel = GroupModelGetById(groupId);
            var serverCommunicate = _appLogic.GroupAddressRemove(groupId, addressId);
            var communicate = serverCommunicate as ServerAckCommunicate;
            if (communicate == null)
            {
                if (serverCommunicate is ServerErrorBadGroupCommunicate)
                {
                    throw new BadGroupException();
                }
                if (serverCommunicate is ServerErrorBadAddressCommunicate)
                {
                    throw new BadAddressException();
                }
                throw new NotImplementedException();
            }
            groupModel.Addresses.RemoveAll(a => a.Id == addressId);
        }

        public GroupModel GroupModelCreate(string name)
        {
            var serverCommunicate = _appLogic.GroupCreate(name);
            var communicate = serverCommunicate as ServerGroupGetOneCommunicate;
            if (communicate == null)
            {
                if (serverCommunicate is ServerErrorBadGroupCommunicate)
                {
                    throw new BadGroupException();
                }
                throw new NotImplementedException();
            }
            var groupModel = new GroupModel()
            {
                Id = communicate.GroupID,
                Name = communicate.GroupName,
                Addresses = new List<AddressModel>()
            };
            for (int i = 0; i < communicate.AddressIDs.Count; ++i)
            {
                groupModel.Addresses.Add(new AddressModel()
                {
                    Id = communicate.AddressIDs[i],
                    Value = communicate.AddressValues[i]
                });
            }
            _groupModels.Add(groupModel);
            _groupModels = _groupModels.OrderBy(g => g.Name).ToList();
            return groupModel;
        }

        public void GroupModelDelete(int id)
        {
            var serverCommunicate = _appLogic.GroupDelete(id);
            var communicate = serverCommunicate as ServerAckCommunicate;
            if (communicate == null)
            {
                if (serverCommunicate is ServerErrorBadGroupCommunicate)
                {
                    throw new BadGroupException();
                }
                throw new NotImplementedException();
            }
            GroupModels.RemoveAll(g => g.Id == id);
        }

        public MessageModel MessageModelCreate(string name, string template)
        {
            var serverCommunicate = _appLogic.MessageCreate(template, name);
            var communicate = serverCommunicate as ServerMessageGetOneCommunicate;
            if (communicate == null)
            {
                if (serverCommunicate is ServerErrorBadMessageCommunicate)
                {
                    throw new BadMessageException();
                }
                throw new NotImplementedException();
            }

            var messageModel = new MessageModel()
            {
                Id = communicate.MessageID,
                Name = name,
                Content = template
            };

            _messagrModels.Add(messageModel);
            _messagrModels = _messagrModels.OrderBy(m => m.Name).ToList();
            return messageModel;
        }

        public void MessageModelDelete(int id)
        {
            var serverCommunicate = _appLogic.MessageDelete(id);
            var communicate = serverCommunicate as ServerAckCommunicate;
            if (communicate == null)
            {
                if (serverCommunicate is ServerErrorBadMessageCommunicate)
                {
                    throw new BadMessageException();
                }
                throw new NotImplementedException();
            }
            MessageModels.RemoveAll(m => m.Id == id);
        }

        public void MessageModelModify(int id, string name, string template)
        {
            var serverCommunicate = _appLogic.MessageModyify(template, name, id);
            var communicate = serverCommunicate as ServerAckCommunicate;
            if (communicate == null)
            {
                if (serverCommunicate is ServerErrorBadMessageCommunicate)
                {
                    throw new BadMessageException();
                }
                throw new NotImplementedException();
            }
            var messageModel = MessageModels.Single(m => m.Id == id);
            messageModel.Name = name;
            messageModel.Content = template;
            _messagrModels = _messagrModels.OrderBy(m => m.Name).ToList();
        }

        public void ClientAuthenticate(string password, string login)
        {
            var serverCommunicate = _appLogic.ReceiveNextCommunicate();
            var authCommunicate = serverCommunicate as ServerAuthCommunicate;
            if (authCommunicate == null)
            {
                if(serverCommunicate is ServerErrorBusyCommunicate)
                {
                    throw new ServerBusyException();
                }
                throw new NotImplementedException();
            }
            var salt = authCommunicate.Salt;

            serverCommunicate = _appLogic.Authorize(login, password, salt);
            var ackCommunicate = serverCommunicate as ServerAckCommunicate;
            if (ackCommunicate == null)
            {
                if (serverCommunicate is ServerErrorBadLoginCommunicate)
                {
                    throw new NotAuthorizedException();
                }
                throw new NotImplementedException();
            }
        }

        public void ClientPasswordChange(string password, string newPassword)
        {
            var serverCommunicate = _appLogic.PasswordChange(password, newPassword);
            var communicate = serverCommunicate as ServerAckCommunicate;
            if (communicate == null)
            {
                if (serverCommunicate is ServerErrorBadLoginCommunicate)
                {
                    throw new NotAuthorizedException();
                }
                throw new NotImplementedException();
            }
        }

        public void Send(int groupId, int messageId, List<string> templateValues)
        {
            var serverCommunicate = _appLogic.Send(groupId, messageId, templateValues);
            var communicate = serverCommunicate as ServerAckCommunicate;
            if (communicate == null)
            {
                if (serverCommunicate is ServerErrorBadMessageCommunicate)
                {
                    throw new BadMessageException();
                }
                if (serverCommunicate is ServerErrorBadGroupCommunicate)
                {
                    throw new BadGroupException();
                }
                throw new NotImplementedException();
            }
        }

        public AddressModel AddressAdd(string addresValue, string addresseeName)
        {
            var serverCommunicate = _appLogic.AddressAdd(addresValue, addresseeName);
            var communicate = serverCommunicate as ServerAddressGetOneCommunicate;
            if (communicate == null)
            {
                if (serverCommunicate is ServerErrorBadAddressCommunicate)
                {
                    throw new BadAddressException();
                }
                throw new NotImplementedException();
            }
            var addrModel = new AddressModel()
            {
                AdresseeName = addresseeName,
                Value = addresValue,
                Id = communicate.AddressID
            };
            _addressModels.Add(addrModel);
            _addressModels = _addressModels.OrderBy(a => a.AdresseeName).ToList();
            return addrModel;
        }

        public void AddressRemove(int addressId)
        {
            var serverCommunicate = _appLogic.AddressRemove(addressId);
            var communicate = serverCommunicate as ServerAckCommunicate;
            if (communicate == null)
            {
                if (serverCommunicate is ServerErrorBadAddressCommunicate)
                {
                    throw new BadAddressException();
                }
                throw new NotImplementedException();
            }
            foreach (var group in GroupModels)
            {
                if (group.Addresses != null)
                {
                    group.Addresses.RemoveAll(a => a.Id == addressId);
                }
            }
            AddressModels.RemoveAll(a => a.Id == addressId);
        }
    }
}
