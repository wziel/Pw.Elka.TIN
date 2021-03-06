﻿using Pw.Elka.TIN.Client.Logic.Exceptions;
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

            txtNewPass.PrepareApplicationControl();
            txtNewPassConfirm.PrepareApplicationControl();
            txtOldPass.PrepareApplicationControl();
        }

        private void btnSubmit_Click(object sender, RoutedEventArgs e)
        {
            var app = (App)Application.Current;

            if(txtNewPass.Password != txtNewPassConfirm.Password)
            {
                Helpers.DisplayError("Podane nowe hasła nie zgadzają się.");
                return;
            }

            var newPass = txtNewPass.Password;
            var oldPass = txtOldPass.Password;
            
            try
            {
                app.AppDAL.ClientPasswordChange(oldPass, newPass);
                Helpers.DisplaySuccess("Pomyślnie zmieniono hasło.");
            }
            catch(NotAuthorizedException)
            {
                Helpers.DisplayError("Podane stare hasło nie jest poprawne.");
            }
        }

        private void btnLogOut_Click(object sender, RoutedEventArgs e)
        {
            var app = (App)Application.Current;
            app.LogOut();
            Helpers.DisplaySuccess("Wylogowanie powiodło się.");
        }
    }
}
