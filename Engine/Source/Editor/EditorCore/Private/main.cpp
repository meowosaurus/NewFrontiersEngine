#include <QApplication>
#include <QPushButton>
#include "Editor/EditorCore/Public/EditorMain.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    EditorMainWindow editor;
    editor.show();

    return QApplication::exec();
}
