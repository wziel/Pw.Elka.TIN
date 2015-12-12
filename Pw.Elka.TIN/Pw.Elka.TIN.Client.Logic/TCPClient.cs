using Pw.Elka.TIN.Client.Logic.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic
{
    internal class TCPLayer : ITCPLayer
    {
        private int _port;
        private string _ipAddress;
        private IDecipher _cipher;
        private TcpClient _tcpClient;
        private NetworkStream _networkStream;

        public bool IsConnected
        {
            get;
            private set;
        }

        public TCPLayer(int port, string ipAddress, IDecipher cipher)
        {
            _port = port;
            _ipAddress = ipAddress;
            _cipher = cipher;
            _tcpClient = new TcpClient();
            IsConnected = false;
        }

        public void Connect()
        {
            _tcpClient.Connect(_ipAddress, _port);
            _networkStream = _tcpClient.GetStream();
        }

        public void Send(byte[] buffer)
        {
            var length = Convert.ToInt16(buffer.Length);
            var data = BitConverter.GetBytes(length).Concat(buffer).ToArray();
            _networkStream.Write(data, 0, length + 2);
        }

        public void Receive()
        {
            byte[] buffer = new byte[2];
            _networkStream.Read(buffer, 0, 2);
            int length = BitConverter.ToInt16(buffer, 0);

            buffer = new byte[length];
            _networkStream.Read(buffer, 0, length);
            _cipher.decipher(buffer);
        }
    }
}
