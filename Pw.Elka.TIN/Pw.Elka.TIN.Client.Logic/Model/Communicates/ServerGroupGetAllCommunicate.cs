using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Model.Communicates
{
    public class ServerGroupGetAllCommunicate
    {
        public List<int> GroupIDs { get; set; }
        public List<string> GroupNames { get; set; }
    }
}
