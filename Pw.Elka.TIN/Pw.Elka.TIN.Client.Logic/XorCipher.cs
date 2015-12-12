using Pw.Elka.TIN.Client.Logic.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic
{
    internal class XorCipher : ILayer
    {
        //key: 011011010110100101100011011010000110000101101100

        private byte[] _key = { 109, 105, 99, 104, 97, 108 };
        private ILayer _bottomLayer;

        public XorCipher(ILayer bottomLayer)
        {
            _bottomLayer = bottomLayer;
        }

        public byte[] Receive()
        {
            var buffer = _bottomLayer.Receive();
            if (buffer[0] != 0)
            {
                throw new NotImplementedException();
            }
            buffer = buffer.Skip(3).ToArray();
            Xor(buffer);
            return buffer;
        }

        public void Send(byte[] buffer)
        {
            var length = Convert.ToInt16(buffer.Length);
            var lengthBytes = BitConverter.GetBytes(length);

            var headers = new byte[3] { 0, lengthBytes[0], lengthBytes[1] };
            Xor(buffer);
            buffer = headers.Concat(buffer).ToArray();

            _bottomLayer.Send(buffer);
        }

        private void Xor(byte[] buffer)
        {
            for (int i = 0; i < buffer.Length; ++i)
            {
                var key = _key[i % _key.Length];
                buffer[i] = (byte)(buffer[i] ^ key);
            }
        }
    }
}
