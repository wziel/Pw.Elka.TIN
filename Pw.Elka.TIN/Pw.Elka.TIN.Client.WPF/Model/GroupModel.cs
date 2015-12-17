using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.WPF.Model
{
    internal class GroupModel
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public List<AddressModel> Addresses { get; set; }
    }
}
