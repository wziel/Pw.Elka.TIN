﻿using Pw.Elka.TIN.Client.Logic.Exceptions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
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
    /// Interaction logic for ServerConnectView.xaml
    /// </summary>
    public partial class ServerConnectView : UserControl
    {
        public ServerConnectView()
        {
            InitializeComponent();
            txtAddress.PrepareApplicationControl();
            txtPort.PrepareApplicationControl();
            txtPassword.PrepareApplicationControl();
            txtUsername.PrepareApplicationControl();
        }

        private void btnConnect_Click(object sender, RoutedEventArgs e)
        {
            var app = (App)Application.Current;
            var mainWindow = ((MainWindow)app.MainWindow);

            try
            {
                app.AppLogic = new Logic.App(txtAddress.Text, int.Parse(txtPort.Text));
                app.AppLogic.Connect();
                app.AppDAL = new Logic.AppDAL(app.AppLogic);

                app.AppDAL.ClientAuthenticate(txtPassword.Password, txtUsername.Text);
            }
            catch (SocketException)
            {
                Helpers.DisplayError("Nie udało połączyć się z serwerem. Spróbuj jeszcze raz.");
                return;
            }
            catch (NotAuthorizedException)
            {
                app.AppLogic.Disconnect();
                Helpers.DisplayError("Logowanie nie powiodło się. Podałeś złą nazwę, hasło, albo jesteś już zalogowany z innego urządzenia.");
                return;
            }
            catch(ServerBusyException)
            {
                app.AppLogic.Disconnect();
                Helpers.DisplayError("Serwer aplikacji jest przeciążony. Spróbuj jeszcze raz później.");
                return;
            }

            app.UserName = txtUsername.Text;
            mainWindow.rootContainer.NavigateToMainView();
        }
    }
}
