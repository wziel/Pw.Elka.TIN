using Pw.Elka.TIN.Client.Logic.Exceptions;
using Pw.Elka.TIN.Client.Logic.Models;
using Pw.Elka.TIN.Client.WPF.Views.Main.Addresses;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
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
    /// Interaction logic for AddressesView.xaml
    /// </summary>
    public partial class AddressesView : UserControl
    {
        public AddressesView()
        {
            var app = (App)Application.Current;
            InitializeComponent();
            app.AppDAL.AddressModels.ToList().ForEach(a => stkAddress.Children.Add(new AddressListItemView(a, this)));

            txtNewName.PrepareApplicationControl();
            txtNewValue.PrepareApplicationControl();
        }

        private void btnSubmit_Click(object sender, RoutedEventArgs e)
        {
            var app = (App)Application.Current;

            if (txtNewName.Text.Length == 0)
            {
                Helpers.DisplayError("Nazwa adresata nie może być pusta.");
                return;
            }
            if (!Regex.IsMatch(txtNewValue.Text, @"\A(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?)\Z", RegexOptions.IgnoreCase))
            {
                Helpers.DisplayError("Podany adres email nie jest poprawny.");
                return;
            }
            if (app.AppDAL.AddressModels.SingleOrDefault(a => a.AdresseeName == txtNewName.Text) != null)
            {
                Helpers.DisplayError("Adresat z podaną nazwą już istnieje.");
                return;
            }

            AddressModel addrModel;
            try
            {
                addrModel = app.AppDAL.AddressAdd(txtNewValue.Text, txtNewName.Text);
            }
            catch (BadAddressException)
            {
                Helpers.DisplayError("Nie udało się dodać adresu. Prawdopodobnie adres o takiej nazwie lub zawartości już istnieje.");
                return;
            }
            finally
            {
                txtNewName.Text = "";
                txtNewValue.Text = "";
            }

            stkAddress.Children.Insert(0, new AddressListItemView(addrModel, this));
        }

        public void RemoveAddressListItem(AddressListItemView addrView)
        {
            var app = (App)Application.Current;

            app.AppDAL.AddressRemove(addrView.ModelId);
            stkAddress.Children.Remove(addrView);
        }
    }
}
