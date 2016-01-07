using Pw.Elka.TIN.Client.Logic.Models;
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

namespace Pw.Elka.TIN.Client.WPF.Views.Main.Messages
{
    /// <summary>
    /// Interaction logic for MessagesListItemView.xaml
    /// </summary>
    public partial class MessagesListItemView : UserControl
    {
        private MessageModel _model;
        private MessagesListView _masterView;

        public int ModelId
        {
            get
            {
                return _model.Id;
            }
        }

        public MessagesListItemView(MessageModel model, MessagesListView masterView)
        {
            InitializeComponent();

            _model = model;
            _masterView = masterView;

            lblMsgName.Content = model.Name;
        }

        private void RemoveButton_Click(object sender, RoutedEventArgs e)
        {
            _masterView.RemoveMessageListItem(this);
        }

        private void EditButton_Click(object sender, RoutedEventArgs e)
        {
            _masterView.DisplayDetails(_model);
        }
    }
}
