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
namespace Plugin1Window
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public ModelData data=new ModelData();

        public MainWindow()
        {
            InitializeComponent();

        }
        private void OkButton_Click(object sender, RoutedEventArgs e)
        {
            data.Area = Convert.ToDouble( this.area.Text);
            data.width= Convert.ToDouble(this.width.Text);
            data.height = Convert.ToDouble(this.height.Text);
            this.DialogResult = true;
            this.Close();
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            this.DialogResult = false;

            this.Close();
        }

        public ModelData getUIData()
        {
            return data;
        }
    }
}
