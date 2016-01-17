using Pw.Elka.TIN.Client.Logic.Exceptions;
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

        private bool _isAdded;
        public bool IsAdded
        {
            get
            {
                return _isAdded;
            }
            set
            {
                _isAdded = value;
                if(value)
                {
                    btnAdd.Visibility = Visibility.Hidden;
                    btnRemove.Visibility = Visibility.Visible;
                    Background = Brushes.White;
                }
                else
                {
                    btnAdd.Visibility = Visibility.Visible;
                    btnRemove.Visibility = Visibility.Hidden;
                    Background = Brushes.LightGray;
                }
            }
        }

        public GroupAddressListItemView(GroupModel groupModel, AddressModel addressModel, bool isAdded)
        {
            InitializeComponent();

            lblAddressName.Content = addressModel.AdresseeName;
            lblAddressValue.Content = addressModel.Value;
            _groupModel = groupModel;
            _addressModel = addressModel;
            IsAdded = isAdded;

        }

        private void btnAdd_Click(object sender, RoutedEventArgs e)
        {
            btnAdd.Visibility = Visibility.Hidden;

            var app = (App)Application.Current;
            try
            {
                app.AppDAL.GroupModelAddressAdd(_groupModel.Id, _addressModel.Id);
            }
            catch(Exception ex) when (ex is BadAddressException || ex is BadGroupException)
            {
                Helpers.DisplayError("Nie udało się dodać adresu do grupy. Prawdopodobnie jedno z nich zostało usunięte. Zrestartuj aplikację.");
                return;
            }

            IsAdded = true;
        }

        private void btnRemove_Click(object sender, RoutedEventArgs e)
        {
            btnRemove.Visibility = Visibility.Hidden;

            var app = (App)Application.Current;
            app.AppDAL.GroupModelAddressRemove(_addressModel.Id, _groupModel.Id);

            IsAdded = false;
        }
    }
}
