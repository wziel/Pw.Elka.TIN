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

        public MockAppDAL(Logic.App application)
        {
            _appLogic = application;
            _realAppDAL = new Logic.AppDAL(_appLogic);

            _addressModels = new List<AddressModel>()
            {
                new AddressModel()
                {
                    Id = 0,
                    AdresseeName = "Pierwszy adresat",
                    Value = "pierwszy.adresat@asia.pl"
                },
                new AddressModel()
                {
                    Id = 1,
                    AdresseeName = "Ciekawy adres",
                    Value = "ciekawyadres1234@michal.pl"
                },
                new AddressModel()
                {
                    Id = 2,
                    AdresseeName = "Lubię placki",
                    Value = "xxxOOOxxxLubie@kamil.com"
                },
                new AddressModel()
                {
                    Id = 3,
                    AdresseeName = "Student nr. 1234",
                    Value = "bardzopilnystudent@wojtek.org"
                }
            };

            _messageModels = new List<MessageModel>()
            {
                new MessageModel()
                {
                    Id = 0,
                    Content = "To jest szablon bardzo ciekawej wiadomosc bez zadnych dodatkowych pól",
                    Name = "Ciekawa wiadomość"
                },
                new MessageModel()
                {
                    Id = 1,
                    Content = "Ten szablon zawiera jedno pole o nazwie {pole}",
                    Name = "Jedno pole"
                },
                new MessageModel()
                {
                    Id = 2,
                    Content = "Ta wiadomość w zasadzie nie wiem po co jest, ale niech będzie i niech ma jedno pole dodatkowe",
                    Name = "Ale po co?"
                }
            };

            _groupModels = new List<GroupModel>()
            {
                new GroupModel()
                {
                    Id = 0,
                    Name = "Grupa pierwsza",
                    Addresses = new List<AddressModel>()
                    {
                        _addressModels[0],
                        _addressModels[1],
                        _addressModels[2]
                    }
                },
                new GroupModel()
                {
                    Id = 1,
                    Name = "Grupa druga",
                    Addresses = new List<AddressModel>()
                    {
                        _addressModels[1],
                        _addressModels[3]
                    }
                },
                new GroupModel()
                {
                    Id = 2,
                    Name = "Grupa bez adresów",
                    Addresses = new List<AddressModel>()
                }
            };

            _addressModelsIdHighWaterMark = _addressModels.Count;
            _groupModelsIdHighWaterMark = GroupModels.Count;
            _messageModelsIdHighWaterMark = MessageModels.Count;
        }


        private List<GroupModel> _groupModels;
        private int _groupModelsIdHighWaterMark;

        public List<GroupModel> GroupModels
        {
            get { return _groupModels; }
        }

        private List<MessageModel> _messageModels;
        private int _messageModelsIdHighWaterMark;

        public List<MessageModel> MessageModels
        {
            get { return _messageModels; }
        }

        private List<AddressModel> _addressModels;
        private int _addressModelsIdHighWaterMark;

        public List<AddressModel> AddressModels
        {
            get { return _addressModels; }
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
                Id = _groupModelsIdHighWaterMark++,
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
                Id = _messageModelsIdHighWaterMark++,
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
            var addrModel = new AddressModel()
            {
                AdresseeName = addresseeName,
                Value = addresValue,
                Id = _addressModelsIdHighWaterMark
            };
            AddressModels.Add(addrModel);
            return addrModel;
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