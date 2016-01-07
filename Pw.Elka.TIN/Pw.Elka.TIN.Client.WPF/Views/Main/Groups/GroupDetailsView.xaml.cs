using Pw.Elka.TIN.Client.Logic.Models;
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

namespace Pw.Elka.TIN.Client.WPF.Views.Main.Groups
{
    /// <summary>
    /// Interaction logic for GroupDetailsView.xaml
    /// </summary>
    public partial class GroupDetailsView : UserControl
    {
        private GroupModel _model;
        private GroupsView _masterView;

        public GroupDetailsView(GroupModel model, GroupsView groupsView)
        {
            InitializeComponent();

            _model = model;
            _masterView = groupsView;
            lblDetailsGroupName.Content = model.Name;

            var app = (App)Application.Current;

            foreach (var addressModel in app.AppDAL.AddressModels)
            {
                var groupAddrView = new GroupAddressListItemView(_model, addressModel);
                if (_model.Addresses.Contains(addressModel))
                {
                    groupAddrView.btnRemove.Visibility = Visibility.Visible;
                    groupAddrView.btnAdd.Visibility = Visibility.Hidden;
                }
                else
                {
                    groupAddrView.btnRemove.Visibility = Visibility.Hidden;
                    groupAddrView.btnAdd.Visibility = Visibility.Visible;
                }
                stkAddressesList.Children.Add(groupAddrView);
            }
        }

        private void btnDetailsCollapse_Click(object sender, RoutedEventArgs e)
        {
            _masterView.DisplayListView();
        }
    }
}
