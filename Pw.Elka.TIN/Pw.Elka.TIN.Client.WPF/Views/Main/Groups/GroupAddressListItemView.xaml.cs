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
    /// Interaction logic for GroupAddressListItemView.xaml
    /// </summary>
    public partial class GroupAddressListItemView : UserControl
    {
        private GroupModel _groupModel;
        private AddressModel _addressModel;

        public GroupAddressListItemView(GroupModel groupModel, AddressModel addressModel)
        {
            InitializeComponent();

            lblAddressName.Content = addressModel.AdresseeName;
            lblAddressValue.Content = addressModel.Value;
            _groupModel = groupModel;
            _addressModel = addressModel;
        }

        private void btnAdd_Click(object sender, RoutedEventArgs e)
        {
            btnAdd.Visibility = Visibility.Hidden;
            
            var app = (App)Application.Current;
            app.AppDAL.GroupModelAddressAdd(_groupModel.Id, _addressModel.Id);

            btnRemove.Visibility = Visibility.Visible;
        }

        private void btnRemove_Click(object sender, RoutedEventArgs e)
        {
            btnRemove.Visibility = Visibility.Hidden;

            var app = (App)Application.Current;
            app.AppDAL.GroupModelAddressRemove(_groupModel.Id, _addressModel.Id);

            btnAdd.Visibility = Visibility.Visible;
        }
    }
}
