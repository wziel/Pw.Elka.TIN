using Pw.Elka.TIN.Client.Logic.Communicates;
using Pw.Elka.TIN.Client.WPF.Model;
using Pw.Elka.TIN.Client.WPF.Views;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Pw.Elka.TIN.Client.WPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Logic.App AppLogic { get; set; }
        internal AppDAL AppDAL { get; private set; }

        public MainWindow()
        {
            InitializeComponent();
            stkMain.Children.Add(new ServerConnectView());
        }

        public void NavigateToSend()
        {
            stkMain.Children.Clear();
            stkMain.Children.Add(new SendView());
        }

        public void NavigateToMessages()
        {
            stkMain.Children.Clear();
            stkMain.Children.Add(new MessagesView());
        }

        public void NavigateToGroups()
        {
            stkMain.Children.Clear();
            stkMain.Children.Add(new GroupsView());
        }

        public void NavigateToAccount()
        {
            stkMain.Children.Clear();
            stkMain.Children.Add(new AccountView());
        }
    }
}
