using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Interfaces
{
    interface ILayer
    {
        byte[] Receive();
        void Send(byte[] buffer);
    }
}
