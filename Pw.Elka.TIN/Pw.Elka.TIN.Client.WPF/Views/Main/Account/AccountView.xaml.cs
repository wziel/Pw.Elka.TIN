using Pw.Elka.TIN.Client.Logic.Hash;
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
    /// Interaction logic for AccountView.xaml
    /// </summary>
    public partial class AccountView : UserControl
    {
        public AccountView()
        {
            InitializeComponent();
        }

        private void btnSubmit_Click(object sender, RoutedEventArgs e)
        {
            var app = (App)Application.Current;
            var mainWindow = ((MainWindow)app.MainWindow);
            mainWindow.ClearMessage();

            if(txtNewPass.Password != txtNewPassConfirm.Password)
            {
                mainWindow.DisplayMessage("Podane nowe hasła nie zgadzają się. Spróbuj jeszcze raz.");
                return;
            }

            var oldPass = Hashing.GetXoredString(txtOldPass.Password);
            var newPass = Hashing.GetXoredString(txtNewPass.Password);

            /////create exception in logic project when old password is wrong and catch it here if needed
            //throw new NotImplementedException();
            //app.AppDAL.ClientPasswordChange(oldPass, newPass);
        }
    }
}
