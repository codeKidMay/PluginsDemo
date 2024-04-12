#include <iostream>
#include "Stdafx.h"

using namespace System;
using namespace System::Windows;
using namespace MyMainWindow;

[STAThread]
int main()
{
	// 启动主窗口界面
	MyMainWindow::MainWindow^ wd1 = gcnew MyMainWindow::MainWindow();
	wd1->ShowDialog();

	return 0;
}