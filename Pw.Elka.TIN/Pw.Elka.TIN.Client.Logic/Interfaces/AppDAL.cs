using Pw.Elka.TIN.Client.Logic.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Interfaces
{
    public interface AppDAL
    {
        List<GroupModel> GroupModels { get; }
        List<MessageModel> MessageModels { get; }
        List<AddressModel> AddressModels { get; }


        GroupModel GroupModelGetById(int id);

        MessageModel MessageModelGetById(int id);

        void GroupModelAddressAdd(int groupId, int addressId);

        void GroupModelAddressRemove(int addressId, int groupId);

        GroupModel GroupModelCreate(string name);

        void GroupModelDelete(int id);

        void MessageModelCreate(string name, string template);

        void MessageModelDelete(int id);

        void MessageModelModify(int id, string name, string template);

        void ClientAuthenticate(string password, string login);

        void ClientPasswordChange(string password, string newPassword);

        void Send(int groupId, int messageId, List<string> templateValues);

        AddressModel AddressAdd(string addresValue, string addresseeName);

        void AddressRemove(int addressId);
    }
}
