﻿using Pw.Elka.TIN.Client.Logic.Exceptions;
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
    /// Interaction logic for MessagesDetailsView.xaml
    /// </summary>
    public partial class MessagesDetailsView : UserControl
    {
        private MessageModel _model;
        private MessagesView _masterView;

        public MessagesDetailsView(MessageModel model, MessagesView masterView)
        {
            InitializeComponent();
            _model = model;
            _masterView = masterView;

            txtMessageContent.Text = model.Content;
            txtMessageName.Text = model.Name;
        }

        private void btnGoBack_Click(object sender, RoutedEventArgs e)
        {
            _masterView.DisplayListView();
        }

        private void btnSave_Click(object sender, RoutedEventArgs e)
        {
            var app = (App)Application.Current;

            if(txtMessageName.Text.Length == 0)
            {
                MessageBox.Show("Nazwa szablonu wiadomości nie może być pusta.");
                return;
            }
            
            try
            {
                app.AppDAL.MessageModelModify(_model.Id, txtMessageName.Text, txtMessageContent.Text);
            }
            catch(BadMessage)
            {
                MessageBox.Show("Szablon o podanej nazwie już istnieje");
                return;
            }
            MessageBox.Show("Pomyślnie zmodyfikowano szablon wiadomości");
        }
    }
}