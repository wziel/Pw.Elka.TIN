﻿using Pw.Elka.TIN.Client.Logic.Exceptions;
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

namespace Pw.Elka.TIN.Client.WPF.Views
{
    /// <summary>
    /// Interaction logic for LoginView.xaml
    /// </summary>
    public partial class LoginView : UserControl
    {
        public LoginView()
        {
            InitializeComponent();
        }

        private void btnSubmit_Click(object sender, RoutedEventArgs e)
        {
            var app = (App)Application.Current;
            var mainWindow = ((MainWindow)app.MainWindow);
            try
            {
                app.AppDAL.ClientAuthenticate(txtPassword.Password, txtUsername.Text);
            }
            catch (NotAuthorizedException)
            {
                Helpers.DisplayError("Logowanie nie powiodło się. Spróbuj jeszcze raz.");
                return;
            }
            mainWindow.rootContainer.NavigateToMainView();
        }
    }
}
