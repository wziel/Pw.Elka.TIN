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
    /// Interaction logic for MessagesListView.xaml
    /// </summary>
    public partial class MessagesListView : UserControl
    {
        MessagesView _masterView;

        public MessagesListView(MessagesView masterView)
        {
            InitializeComponent();
            _masterView = masterView;

            var app = (App)Application.Current;
            app.AppDAL.MessageModels.ForEach(m => stkMsgs.Children.Add(new MessagesListItemView(m, this)));

            txtNewMsgContent.PrepareApplicationControl();
            txtNewMsgName.PrepareApplicationControl();
        }

        private void btnSubmitNewMsg_Click(object sender, RoutedEventArgs e)
        {
            var app = (App)Application.Current;

            if(app.AppDAL.MessageModels.FirstOrDefault(m => m.Name == txtNewMsgName.Text) != null)
            {
                Helpers.DisplayError("Szablon wiadomości z podaną nazwą już istnieje.");
                return;
            }

            var messageModel = app.AppDAL.MessageModelCreate(txtNewMsgName.Text, txtNewMsgContent.Text);
            stkMsgs.Children.Insert(0, new MessagesListItemView(messageModel, this));

            txtNewMsgName.Text = "";
            txtNewMsgContent.Text = "";
        }

        public void DisplayListView()
        {
            _masterView.DisplayListView();
        }

        public void DisplayDetails(MessageModel model)
        {
            _masterView.DisplayDetailsListItem(model);
        }

        internal void RemoveMessageListItem(MessagesListItemView messagesListItemView)
        {
            var app = (App)Application.Current;
            app.AppDAL.MessageModelDelete(messagesListItemView.ModelId);
            stkMsgs.Children.Remove(messagesListItemView);
        }
    }
}
