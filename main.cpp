
#include <QApplication>
#include <QtDebug>
#include <atomic>
#include <graphicsview.h>
#include <graphicsscene.h>
#include <itemwindow.h>
#include <QMainWindow>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GraphicsScene scene;
    GraphicsView *view = new GraphicsView(&scene);
    QMainWindow window;
    window.setCentralWidget(view);
    window.show();

    return a.exec();
}

