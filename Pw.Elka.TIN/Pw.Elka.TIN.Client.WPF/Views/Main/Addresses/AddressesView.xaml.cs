using Pw.Elka.TIN.Client.Logic.Models;
using Pw.Elka.TIN.Client.WPF.Views.Main.Addresses;
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
    /// Interaction logic for AddressesView.xaml
    /// </summary>
    public partial class AddressesView : UserControl
    {
        public AddressesView()
        {
            var app = (App)Application.Current;
            var mainWindow = ((MainWindow)app.MainWindow);
            InitializeComponent();
            //app.AppDAL.AddressModels.ForEach(a => stkAddress.Children.Add(new AddressListItemView(a, this)));
        }

        private void btnSubmit_Click(object sender, RoutedEventArgs e)
        {
            var app = (App)Application.Current;
            var mainWindow = ((MainWindow)app.MainWindow);

            mainWindow.ClearMessage();

            //if (app.AppDAL.AddressModels.SingleOrDefault(a => a.AdresseeName == txtNewName.Text) != null)
            //{
            //    mainWindow.DisplayMessage("Adresat z podaną nazwą już istnieje. Spróbuj jeszcze raz.");
            //    return;
            //}

            //var addrModel = app.AppDAL.AddressAdd(txtNewValue.Text, txtNewName.Text);
            //stkAddress.Children.Add(new AddressListItemView(addrModel, this));

            txtNewName.Text = "";
            txtNewValue.Text = "";

            mainWindow.DisplayMessage("Pomyślnie dodano nowego adresata");
        }

        public void RemoveAddressListItem(AddressListItemView addrView)
        {
            var app = (App)Application.Current;
            var mainWindow = ((MainWindow)app.MainWindow);

            //app.AppDAL.AddressRemove(addrView.ModelId);
            stkAddress.Children.Remove(addrView);

            mainWindow.DisplayMessage("Pomyślnie usunięto adresata");
        }
    }
}
