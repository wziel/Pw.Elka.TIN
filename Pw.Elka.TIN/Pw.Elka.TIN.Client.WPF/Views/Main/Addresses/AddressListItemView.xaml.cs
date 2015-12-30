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

namespace Pw.Elka.TIN.Client.WPF.Views.Main.Addresses
{
    /// <summary>
    /// Interaction logic for AddressListItemView.xaml
    /// </summary>
    public partial class AddressListItemView : UserControl
    {
        private AddressesView _masterView;
        private AddressModel _addrModel;

        public int ModelId
        {
            get
            {
                return _addrModel.Id;
            }
        }

        public AddressListItemView(AddressModel model, AddressesView masterView)
        {
            InitializeComponent();
            lblAddressName.Content = model.AdresseeName;
            lblAddressValue.Content = model.Value;

            _masterView = masterView;
        }

        private void RemoveButton_Click(object sender, RoutedEventArgs e)
        {
            _masterView.RemoveAddressListItem(this);
        }
    }
}
