
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Security.Cryptography.X509Certificates;
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

namespace MyMainWindow
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>


    public unsafe partial class MainWindow : Window
    {

        [DllImport("PluginsManage.dll")]
        public static extern IntPtr CreatePluginManager();

        [DllImport("PluginsManage.dll")]
        public static extern void LoadPlugins(IntPtr manage, string Pluginname);

        [DllImport("PluginsManage.dll")]
        public static extern void RunPlugin(IntPtr manager, string Pluginname);


        [DllImport("Myplugin1.dll")]
        public static extern IntPtr CreateMyplugin();

        public IntPtr manager;

        public IntPtr plugin;

        public MainWindow()
        {
            InitializeComponent();
            manager= CreatePluginManager();
            LoadPlugins(manager, "MyPlugin1");
            LoadPlugins(manager, "MyPlugin2");
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string name = "plugin1";
        
            RunPlugin(manager, name);
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {

        }
    }
}
