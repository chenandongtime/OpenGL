#include "widget.h"
#include "corefunctionwidget.h"
#include <QApplication>
#include "qtfunctionwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CoreFunctionWidget w2;
    w2.setWindowTitle(QObject::tr("CoreFunction"));
    w2.show();

    /*
    QtFunctionWidget w1;
    w1.setWindowTitle(QObject::tr("QtFunction"));
    w1.show();
    */
    return a.exec();
}
