using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

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

        public static void PrepareApplicationControl(this TextBox txt)
        {
            txt.GotFocus += TextBox_GotFocus;
            txt.PreviewTextInput += TextBox_PreviewTextInput;
        }

        public static void PrepareApplicationControl(this PasswordBox txt)
        {
            txt.GotFocus += PasswordBox_GotFocus;
            txt.PreviewTextInput += TextBox_PreviewTextInput;
        }

        private static void TextBox_GotFocus(object sender, RoutedEventArgs e)
        {
            (sender as TextBox).SelectAll();
        }

        private static void PasswordBox_GotFocus(object sender, RoutedEventArgs e)
        {
            (sender as PasswordBox).SelectAll();
        }

        private static void TextBox_PreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            e.Handled = !IsTextAllowed(e.Text);
        }

        private static bool IsTextAllowed(string text)
        {
            Regex regex = new Regex("[^\u0000-\u007F]"); //regex that matches disallowed text
            return !regex.IsMatch(text);
        }
    }
}
