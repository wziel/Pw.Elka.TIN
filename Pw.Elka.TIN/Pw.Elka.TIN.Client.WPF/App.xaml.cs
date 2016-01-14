using Pw.Elka.TIN.Client.Logic;
using Pw.Elka.TIN.Client.WPF.Views;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Threading;

namespace Pw.Elka.TIN.Client.WPF
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        internal Logic.App AppLogic { get; set; }
        internal Logic.Interfaces.AppDAL AppDAL { get; set; }

        public App() : base()
        {
            this.Dispatcher.UnhandledException += UnhandledExceptionHandler;
        }

        private void UnhandledExceptionHandler(object sender, DispatcherUnhandledExceptionEventArgs e)
        {
            var mainWindow = ((MainWindow)MainWindow);
            mainWindow.rootContainer.stkPanel.Children.Clear();
            mainWindow.rootContainer.stkPanel.Children.Add(new ServerConnectView());
            string errorMessage = $"Wystąpił nieoczekiwany błąd. Spróbuj jeszcze raz połączyć się z serwerem.\nSzczegóły błędu:\n{e.Exception.Message}";
            MessageBox.Show(errorMessage);
            e.Handled = true;
        }
    }
}
