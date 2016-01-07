using Pw.Elka.TIN.Client.Logic.Models;
using Pw.Elka.TIN.Client.WPF.Views.Main.Groups;
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
    /// Interaction logic for GroupsView.xaml
    /// </summary>
    public partial class GroupsView : UserControl
    {
        public GroupsView()
        {
            InitializeComponent();
            stkMain.Children.Add(new GroupsListView(this));
        }

        public void DisplayDetailsListItem(GroupModel model)
        {
            stkMain.Children.Clear();
            stkMain.Children.Add(new GroupDetailsView(model, this));
        }

        public void DisplayListView()
        {
            stkMain.Children.Clear();
            stkMain.Children.Add(new GroupsListView(this));
        }
    }
}
