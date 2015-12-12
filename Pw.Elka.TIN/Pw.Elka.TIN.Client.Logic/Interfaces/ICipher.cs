using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Interfaces
{
    interface ICipher
    {
        void Receive();
        void Cipher(byte[] buffer);
    }
}
