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

namespace Pw.Elka.TIN.Client.WPF.Views.Main.Groups
{
    /// <summary>
    /// Interaction logic for GroupsListItemView.xaml
    /// </summary>
    public partial class GroupsListItemView : UserControl
    {
        private GroupModel _model;
        private GroupsView _masterView;

        public int ModelId
        {
            get
            {
                return _model.Id;
            }
        }

        public GroupsListItemView(GroupModel model, GroupsView masterView)
        {
            InitializeComponent();
            lblGroupName.Content = model.Name;

            _masterView = masterView;
        }

        private void RemoveButton_Click(object sender, RoutedEventArgs e)
        {
            _masterView.RemoveGroupListItem(this);
        }

        private void EditButton_Click(object sender, RoutedEventArgs e)
        {
            _masterView.DisplayDetailsListItem(_model);
        }
    }
}
