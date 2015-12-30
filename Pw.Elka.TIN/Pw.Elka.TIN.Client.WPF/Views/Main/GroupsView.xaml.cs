using Pw.Elka.TIN.Client.Logic.Models;
using Pw.Elka.TIN.Client.WPF.Views.Main.Groups;
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
    /// Interaction logic for GroupsView.xaml
    /// </summary>
    public partial class GroupsView : UserControl
    {
        public GroupsView()
        {
            var app = (App)Application.Current;
            var mainWindow = ((MainWindow)app.MainWindow);
            InitializeComponent();
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

        public void DisplayDetailsListItem(GroupModel model)
        {
            stkListView.Visibility = Visibility.Hidden;
            stkDetailsView.Visibility = Visibility.Visible;

            txtDetailsGroupName.Text = model.Name;

            throw new NotImplementedException();
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

        private void btnDetailsSave_Click(object sender, RoutedEventArgs e)
        {

        }

        private void btnDetailsCollapse_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
