using System;
using System.Windows;

namespace Plugin1Window
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public ModelData data = new ModelData();

        public MainWindow()
        {
            InitializeComponent();

        }
        private void OkButton_Click(object sender, RoutedEventArgs e)
        {
            data.Area = Convert.ToDouble(this.area.Text);
            data.width = Convert.ToDouble(this.width.Text);
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
