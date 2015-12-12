using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Model.Communicates
{
    public class ClientSendCommunicate
    {
        public int GroupID { get; set; }
        public int MessageID { get; set; }
        public List<string> TemplateValues { get; set; }
    }
}
