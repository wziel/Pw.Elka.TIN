using Pw.Elka.TIN.Client.Logic.Models;
using Pw.Elka.TIN.Client.WPF.Views.Main.Messages;
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
    /// Interaction logic for MessagesView.xaml
    /// </summary>
    public partial class MessagesView : UserControl
    {
        public MessagesView()
        {
            InitializeComponent();
            stkMain.Children.Add(new MessagesListView(this));
        }

        public void DisplayDetailsListItem(MessageModel model)
        {
            stkMain.Children.Clear();
            stkMain.Children.Add(new MessagesDetailsView(model, this));
        }

        public void DisplayListView()
        {
            stkMain.Children.Clear();
            stkMain.Children.Add(new MessagesListView(this));
        }
    }
}
