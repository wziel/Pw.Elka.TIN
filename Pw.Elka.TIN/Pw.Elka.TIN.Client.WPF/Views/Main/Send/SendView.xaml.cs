﻿using Pw.Elka.TIN.Client.Logic.Models;
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

namespace Pw.Elka.TIN.Client.WPF.Views.Main
{
    /// <summary>
    /// Interaction logic for SendView.xaml
    /// </summary>
    public partial class SendView : UserControl
    {
        public SendView()
        {
            InitializeComponent();

            var app = (App)Application.Current;
            //app.AppDAL.GroupModels.ForEach(g => lbGroups.Items.Add(g));
            //app.AppDAL.MessageModels.ForEach(m => lbMessages.Items.Add(m));
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var groupId = ((GroupModel)lbGroups.SelectedItem).Id;
            var msgId = ((MessageModel)lbMessages.SelectedItem).Id;

            var app = (App)Application.Current;
            //app.AppDAL.Send(groupId, msgId, new List<string>());
        }
    }
}