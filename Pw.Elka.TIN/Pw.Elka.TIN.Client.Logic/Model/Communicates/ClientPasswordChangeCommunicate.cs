﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pw.Elka.TIN.Client.Logic.Model.Communicates
{
    public class ClientPasswordChangeCommunicate
    {
        public string PasswordHash { get; set; }
        public string NewPasswordHash { get; set; }
    }
}
