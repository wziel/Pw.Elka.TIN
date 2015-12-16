using Pw.Elka.TIN.Client.Logic.Interfaces;
using Pw.Elka.TIN.Client.Logic.Communicates;
using Pw.Elka.TIN.Client.Logic.Parsers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic
{
    internal class SessionLayer
    {
        private ILayer _bottomLayer;

        internal SessionLayer(ILayer bottomLayer)
        {
            _bottomLayer = bottomLayer;
        }
        
        internal ServerCommunicate ReceiveCommunicate()
        {
            var bytes = _bottomLayer.Receive();
            return ASIAServerCommunicateParser.GetCommunicateFromBytes(bytes);
        }

        internal void SendCommunicate(ClientCommunicate communicate)
        {
            var bytes = communicate.GetBytes();
            _bottomLayer.Send(bytes);
        }
    }
}
