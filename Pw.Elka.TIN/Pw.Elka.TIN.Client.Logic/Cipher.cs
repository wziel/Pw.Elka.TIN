using Pw.Elka.TIN.Client.Logic.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic
{
    internal class Cipher : ICipher, IDecipher
    {
        public void decipher(byte[] buffer)
        {
            throw new NotImplementedException();
        }

        public void Receive()
        {
            throw new NotImplementedException();
        }

        void ICipher.Cipher(byte[] buffer)
        {
            throw new NotImplementedException();
        }
    }
}
