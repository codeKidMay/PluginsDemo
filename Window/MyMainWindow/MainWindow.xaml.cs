
using CSharpAdapter;
using Microsoft.CSharp;
using System;
using System.Runtime.InteropServices;
using System.Windows;

namespace MyMainWindow
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>


    public partial class MainWindow : Window
    {
        private readonly NcAdapter _adapter = new NcAdapter();
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string name = "plugin1";
            _adapter.SendMessage(name);
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            string name = "plugin2";
            _adapter.SendMessage(name);
        }

        private void Button_Click_3(object sender, RoutedEventArgs e)
        {
            string name = "plugin3";
            _adapter.SendMessage(name);
        }
    }
}
