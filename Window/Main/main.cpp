#include <iostream>



using namespace System;
using namespace System::Windows;
using namespace MyMainWindow;

typedef void (*fun)();

[STAThread]
int main() 
{
	//���������ڽ���
	MyMainWindow::MainWindow^ wd1 = gcnew MyMainWindow::MainWindow();
	wd1->ShowDialog();

	return 0;
}