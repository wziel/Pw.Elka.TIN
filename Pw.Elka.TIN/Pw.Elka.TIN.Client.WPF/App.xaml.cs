using Pw.Elka.TIN.Client.Logic;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace Pw.Elka.TIN.Client.WPF
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        internal Logic.App AppLogic { get; set; }
        internal AppDAL AppDAL { get; set; }
    }
}
