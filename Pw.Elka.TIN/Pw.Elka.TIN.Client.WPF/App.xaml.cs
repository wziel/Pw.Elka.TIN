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
            Dispatcher.UnhandledException += UnhandledExceptionHandler;
        }

        public void LogOut()
        {
            var mainWindow = ((MainWindow)MainWindow);
            mainWindow.rootContainer.stkPanel.Children.Clear();
            mainWindow.rootContainer.stkPanel.Children.Add(new ServerConnectView());
            if (AppLogic != null)
            {
                AppLogic.Disconnect();
            }
        }

        private void UnhandledExceptionHandler(object sender, DispatcherUnhandledExceptionEventArgs e)
        {
            LogOut();
            Helpers.DisplayError("Wystąpił nieoczekiwany błąd w aplikacji.");
            e.Handled = true;
        }

        protected override void OnExit(ExitEventArgs e)
        {
            if (AppLogic != null)
            {
                AppLogic.Disconnect();
            }
            base.OnExit(e);
        }
    }
}
