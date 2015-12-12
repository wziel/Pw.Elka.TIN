using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Model.Communicates
{
    public class ServerGroupGetOneCommunicate
    {
        public int GroupID { get; set; }
        public string GroupName { get; set; }
        public List<int> AddressID { get; set; }
        public List<int> AddressValue { get; set; }
    }
}
