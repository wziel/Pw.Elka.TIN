using Pw.Elka.TIN.Client.Logic.Exceptions;
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
    /// Interaction logic for GroupsListview.xaml
    /// </summary>
    public partial class GroupsListView : UserControl
    {
        private GroupsView _masterView;

        public GroupsListView(GroupsView masterView)
        {
            InitializeComponent();

            _masterView = masterView;
            var app = (App)Application.Current;
            app.AppDAL.GroupModels.ForEach(g => stkGroups.Children.Add(new GroupsListItemView(g, this)));

            txtNewGroupName.PrepareApplicationControl();
        }

        public void RemoveGroupListItem(GroupsListItemView groupListItem)
        {
            var app = (App)Application.Current;

            app.AppDAL.GroupModelDelete(groupListItem.ModelId);
            stkGroups.Children.Remove(groupListItem);
        }

        public void DisplayDetails(GroupModel model)
        {
            _masterView.DisplayDetailsListItem(model);
        }

        private void btnSubmitNewGroup_Click(object sender, RoutedEventArgs e)
        {
            var app = (App)Application.Current;

            if (app.AppDAL.GroupModels.SingleOrDefault(g => g.Name == txtNewGroupName.Text) != null)
            {
                Helpers.DisplayError("Grupa z podaną nazwą już istnieje.");
                return;
            }

            GroupModel groupModel;
            try
            {
                groupModel = app.AppDAL.GroupModelCreate(txtNewGroupName.Text);
            }
            catch(BadGroupException)
            {
                Helpers.DisplayError("Nie udało się dodać grupy. Prawdopodobnie grupa o podanej nazwie już istnieje.");
                return;
            }
            finally
            {
                txtNewGroupName.Text = "";
            }

            stkGroups.Children.Insert(0, new GroupsListItemView(groupModel, this));
        }
    }
}
