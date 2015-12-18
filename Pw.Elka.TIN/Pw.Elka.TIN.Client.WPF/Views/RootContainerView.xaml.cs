using Pw.Elka.TIN.Client.WPF.Views.Main;
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
    /// Interaction logic for RootContainerView.xaml
    /// </summary>
    public partial class RootContainerView : UserControl
    {
        public RootContainerView()
        {
            InitializeComponent();
        }

        public void NavigateToLoginView()
        {
            stkPanel.Children.Clear();
            stkPanel.Children.Add(new LoginView());
        }

        public void NavigateToMainView()
        {
            stkPanel.Children.Clear();
            stkPanel.Children.Add(new MainView());
        }
    }
}
