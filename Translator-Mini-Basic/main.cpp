#include "translator.h"
#include <QApplication>

/*
#include <QApplication>
#include "MDIProgram.h"

// ----------------------------------------------------------------------
int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MDIProgram   pmdi;

    pmdi.setWindowTitle("MDI Program");
    pmdi.show();

    return app.exec();
}
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Translator w;
    w.setWindowTitle("Translator Program");
    w.setWindowIcon(QPixmap(":/rsc/imgs/3d.png"));
    w.show();
    return a.exec();
}
