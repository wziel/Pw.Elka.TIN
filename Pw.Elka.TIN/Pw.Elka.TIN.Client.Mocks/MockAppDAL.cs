using Pw.Elka.TIN.Client.Logic.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Mocks
{
    public class MockAppDAL : Logic.Interfaces.AppDAL
    {
        private Logic.App _appLogic;
        private Logic.AppDAL _realAppDAL;
        private int _uniqueIdMock;

        public MockAppDAL(Logic.App application)
        {
            _appLogic = application;
            _realAppDAL = new Logic.AppDAL(_appLogic);
            _uniqueIdMock = 100;
        }

        public List<GroupModel> GroupModels
        {
            get { return _realAppDAL.GroupModels; }
        }

        public List<MessageModel> MessageModels
        {
            get { return _realAppDAL.MessageModels; }
        }

        public List<AddressModel> AddressModels
        {
            get { return _realAppDAL.AddressModels; }
        }


        public GroupModel GroupModelGetById(int id)
        {
            return GroupModels.Single(g => g.Id == id);
        }

        public MessageModel MessageModelGetById(int id)
        {
            return MessageModels.Single(m => m.Id == id);
        }

        public void GroupModelAddressAdd(int groupId, int addressId)
        {
            var groupModel = GroupModelGetById(groupId);
            var address = AddressModels.Single(a => a.Id == addressId);
            groupModel.Addresses.Add(address);
        }

        public void GroupModelAddressRemove(int addressId, int groupId)
        {
            var groupModel = GroupModelGetById(groupId);
            groupModel.Addresses.RemoveAll(a => a.Id == addressId);
        }

        public GroupModel GroupModelCreate(string name)
        {
            var groupModel = new GroupModel()
            {
                Id = _uniqueIdMock++,
                Name = name,
                Addresses = new List<AddressModel>()
            };
            GroupModels.Add(groupModel);
            return groupModel;
        }

        public void GroupModelDelete(int id)
        {
            GroupModels.RemoveAll(g => g.Id == id);
        }

        public MessageModel MessageModelCreate(string name, string template)
        {
            var messageModel = new MessageModel()
            {
                Id = _uniqueIdMock++,
                Name = name,
                Content = template
            };

            MessageModels.Add(messageModel);
            return messageModel;
        }

        public void MessageModelDelete(int id)
        {
            MessageModels.RemoveAll(m => m.Id == id);
        }

        public void MessageModelModify(int id, string name, string template)
        {
            var messageModel = MessageModels.Single(m => m.Id == id);
            messageModel.Name = name;
            messageModel.Content = template;
        }

        public void ClientAuthenticate(string password, string login)
        {
            _realAppDAL.ClientAuthenticate(password, login);
        }

        public void ClientPasswordChange(string password, string newPassword)
        {
        }

        public void Send(int groupId, int messageId, List<string> templateValues)
        {
        }

        public AddressModel AddressAdd(string addresValue, string addresseeName)
        {
            return _realAppDAL.AddressAdd(addresValue, addresseeName);
        }

        public void AddressRemove(int addressId)
        {
            foreach (var group in GroupModels)
            {
                group.Addresses.RemoveAll(a => a.Id == addressId);
            }
            AddressModels.RemoveAll(a => a.Id == addressId);
        }
    }
}