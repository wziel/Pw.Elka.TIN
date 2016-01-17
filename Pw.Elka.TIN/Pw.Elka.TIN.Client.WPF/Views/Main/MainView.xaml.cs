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

namespace Pw.Elka.TIN.Client.WPF.Views.Main
{
    /// <summary>
    /// Interaction logic for MainView.xaml
    /// </summary>
    public partial class MainView : UserControl
    {
        public MainView()
        {
            InitializeComponent();
            var app = (App)Application.Current;
            lblUserWelcome.Content = $"Witaj, {app.UserName}";
        }

        private void tabControl_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if(e.OriginalSource != tabControl)
            {
                return;
            }

            var app = (App)Application.Current;

            if(tabControl.SelectedItem == tabItemAccount)
            {
                tabItemAccount.Content = new AccountView();
            }
            else if(tabControl.SelectedItem == tabItemAddresses)
            {
                tabItemAddresses.Content = new AddressesView();
            }
            else if(tabControl.SelectedItem == tabItemGroups)
            {
                tabItemGroups.Content = new GroupsView();
            }
            else if(tabControl.SelectedItem == tabItemMessages)
            {
                tabItemMessages.Content = new MessagesView();
            }
            else if(tabControl.SelectedItem == tabItemSend)
            {
                tabItemSend.Content = new SendView();
            }
        }
    }
}
