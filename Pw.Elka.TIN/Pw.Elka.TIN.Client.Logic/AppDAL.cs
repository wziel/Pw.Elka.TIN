﻿using Pw.Elka.TIN.Client.Logic.Communicates;
using Pw.Elka.TIN.Client.Logic.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic
{
    public class AppDAL
    {
        private static Logic.App _appLogic;

        public static void Initialize(Logic.App application)
        {
            _appLogic = application;
        }


        private static List<GroupModel> _groupModels;

        public static List<GroupModel> GroupModels
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
                }
                return _groupModels;
            }
        }

        private static List<MessageModel> _messagrModels;

        public static List<MessageModel> MessageModels
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
                }
                return _messagrModels;
            }
        }

        private static List<AddressModel> _addressModels;

        public static List<AddressModel> AddressModels
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
                }
                return _addressModels;
            }
        }


        public static GroupModel GroupModelGetById(int id)
        {
            var groupModel = GroupModels.Single(g => g.Id == id);
            if (groupModel.Addresses == null)
            {
                var serverCommunicate = _appLogic.GroupGetOne(id);
                var communicate = serverCommunicate as ServerGroupGetOneCommunicate;
                if (communicate == null)
                {
                    throw new NotImplementedException();
                }
                groupModel.Addresses = new List<AddressModel>();
                for (int i = 0; i < communicate.AddressID.Count; ++i)
                {
                    groupModel.Addresses.Add(new AddressModel()
                    {
                        Id = communicate.AddressID[i],
                        Value = communicate.AddressValuse[i]
                    });
                }
            }
            return groupModel;
        }

        public static MessageModel MessageModelGetById(int id)
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

        public static void GroupModelAddressAdd(int groupId, int addressId)
        {
            var groupModel = GroupModelGetById(groupId);
            var serverCommunicate = _appLogic.GroupAddressAdd(groupId, addressId);
            var communicate = serverCommunicate as ServerAckCommunicate;
            if (communicate == null)
            {
                throw new NotImplementedException();
            }
            var address = AddressModels.Single(a => a.Id == addressId);
            groupModel.Addresses.Add(address);
        }

        public static void GroupModelAddressRemove(int addressId, int groupId)
        {
            var groupModel = GroupModelGetById(groupId);
            var serverCommunicate = _appLogic.GroupAddressRemove(groupId, addressId);
            var communicate = serverCommunicate as ServerAckCommunicate;
            if (communicate == null)
            {
                throw new NotImplementedException();
            }
            groupModel.Addresses.RemoveAll(a => a.Id == addressId);
        }

        public static void GroupModelCreate(string name)
        {
            var serverCommunicate = _appLogic.GroupCreate(name);
            var communicate = serverCommunicate as ServerGroupGetOneCommunicate;
            if (communicate == null)
            {
                throw new NotImplementedException();
            }
            var groupModel = new GroupModel()
            {
                Id = communicate.GroupID,
                Name = communicate.GroupName,
                Addresses = new List<AddressModel>()
            };
            for (int i = 0; i < communicate.AddressID.Count; ++i)
            {
                groupModel.Addresses.Add(new AddressModel()
                {
                    Id = communicate.AddressID[i],
                    Value = communicate.AddressValuse[i]
                });
            }
            GroupModels.Add(groupModel);
        }

        public static void GroupModelDelete(int id)
        {
            var serverCommunicate = _appLogic.GroupDelete(id);
            var communicate = serverCommunicate as ServerAckCommunicate;
            if (communicate == null)
            {
                throw new NotImplementedException();
            }
            GroupModels.RemoveAll(g => g.Id == id);
        }

        public static void MessageModelCreate(string name, string template)
        {
            var serverCommunicate = _appLogic.MessageCreate(template, name);
            var communicate = serverCommunicate as ServerMessageGetOneCommunicate;
            if (communicate == null)
            {
                throw new NotImplementedException();
            }
            MessageModels.Add(new MessageModel()
            {
                Id = communicate.MessageID,
                Name = communicate.MessageName,
                Content = communicate.MessageTemplate
            });
        }

        public static void MessageModelDelete(int id)
        {
            var serverCommunicate = _appLogic.MessageDelete(id);
            var communicate = serverCommunicate as ServerAckCommunicate;
            if (communicate == null)
            {
                throw new NotImplementedException();
            }
            MessageModels.RemoveAll(m => m.Id == id);
        }

        public static void MessageModelModify(int id, string name, string template)
        {
            var serverCommunicate = _appLogic.MessageModyify(template, name, id);
            var communicate = serverCommunicate as ServerAckCommunicate;
            if (communicate == null)
            {
                throw new NotImplementedException();
            }
            var messageModel = MessageModels.Single(m => m.Id == id);
            messageModel.Name = name;
            messageModel.Content = template;
        }

        public static void ClientAuthenticate(string password, string login)
        {
            var serverCommunicate = _appLogic.Authorize(login, password);
            var communicate = serverCommunicate as ServerAckCommunicate;
            if (communicate == null)
            {
                throw new NotImplementedException();
            }
        }

        public static void ClientPasswordChange(string password, string newPassword)
        {
            var serverCommunicate = _appLogic.PasswordChange(password, newPassword);
            var communicate = serverCommunicate as ServerAckCommunicate;
            if (communicate == null)
            {
                throw new NotImplementedException();
            }
        }

        public static void Send(int groupId, int messageId, List<string> templateValues)
        {
            var serverCommunicate = _appLogic.Send(groupId, messageId, templateValues);
            var communicate = serverCommunicate as ServerAckCommunicate;
            if (communicate == null)
            {
                throw new NotImplementedException();
            }
        }

        public static void AddressAdd(string addresValue, string addresseeName)
        {
            var serverCommunicate = _appLogic.AddressAdd(addresValue, addresseeName);
            var communicate = serverCommunicate as ServerAddressGetOneCommunicate;
            if(communicate == null)
            {
                throw new NotImplementedException();
            }
            AddressModels.Add(new AddressModel()
            {
                AdresseeName = addresseeName,
                Value = addresValue,
                Id = communicate.AddressID
            });
        }

        public static void AddressRemove(int addressId)
        {
            var serverCommunicate = _appLogic.AddressRemove(addressId);
            var communicate = serverCommunicate as ServerAckCommunicate;
            if(communicate == null)
            {
                throw new NotImplementedException();
            }
            foreach(var group in GroupModels)
            {
                group.Addresses.RemoveAll(a => a.Id == addressId);
            }
        }
    }
}