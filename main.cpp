#include "QtTestUI.h"
#include <QtWidgets/QApplication>

//this is a test.//20190124
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtTestUI w;
	w.show();
	return a.exec();
}
