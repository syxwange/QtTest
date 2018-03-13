#include "QtTestUI.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtTestUI w;
	w.show();
	return a.exec();
}
