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
            masterView = _masterView;
            InitializeComponent();

            var app = (App)Application.Current;
            var mainWindow = ((MainWindow)app.MainWindow);
            //app.AppDAL.GroupModels.ForEach(g => stkGroups.Children.Add(new GroupsListItemView(g, this)));
        }

        public void RemoveGroupListItem(GroupsListItemView groupListItem)
        {
            var app = (App)Application.Current;
            var mainWindow = ((MainWindow)app.MainWindow);
            mainWindow.ClearMessage();

            //app.AppDAL.GroupModelDelete(groupListItem.ModelId);
            stkGroups.Children.Remove(groupListItem);

            mainWindow.DisplayMessage("Pomyślnie usunięto grupę");
        }

        public void DisplayDetails(GroupModel model)
        {
            _masterView.DisplayDetailsListItem(model);
        }

        private void btnSubmitNewGroup_Click(object sender, RoutedEventArgs e)
        {
            var app = (App)Application.Current;
            var mainWindow = ((MainWindow)app.MainWindow);
            mainWindow.ClearMessage();

            //if(app.AppDAL.GroupModels.SingleOrDefault(g => g.Name == txtNewGroupName.Text) != null)
            //{
            //    mainWindow.DisplayMessage("Grupa z podaną nazwą już istnieje. Spróbuj jeszcze raz.");
            //    return;
            //}

            //var groupModel = app.AppDAL.GroupModelCreate(txtNewGroupName.Text);
            //stkGroups.Children.Add(new GroupsListItemView(groupModel, this));

            txtNewGroupName.Text = "";

            mainWindow.DisplayMessage("Pomyślnie dodano nową grupę.");
        }
    }
}
