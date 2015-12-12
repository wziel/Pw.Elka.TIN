using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Model.Communicates
{
    public class ServerMessageGetAllCommunicate
    {
        public List<int> MessageIDs { get; set; }
        public List<string> MessageNames { get; set; }
    }
}
