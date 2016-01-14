using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Pw.Elka.TIN.Client.WPF
{
    public static class Helpers
    {
        public static void DisplayError(string errorMessage)
        {
            MessageBox.Show(errorMessage, "Błąd w aplikacji", MessageBoxButton.OK, MessageBoxImage.Error);
        }

        public static void DisplaySuccess(string successMessage)
        {
            MessageBox.Show(successMessage, "Sukces", MessageBoxButton.OK, MessageBoxImage.Asterisk);
        }
    }
}
