//
// Created by Sonnen on 14.05.2022.
//

#ifndef NEWFRONTIERSENGINE_EDITORMENU_H
#define NEWFRONTIERSENGINE_EDITORMENU_H

#include <QObject>

#include "Editor/General/nf_error.h"

class QMainWindow;
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class EditorError;

class EditorMenu : public QObject
{
Q_OBJECT

public:
    EditorMenu(QMainWindow* mainWindow);

    /**
     * Creates menus and submenus for the main editor window
     * @return NF_ERROR returns NF_ERROR::ok if successful
     */
    NF_ERROR CreateMenus();

private:
    /**
     * Links menus and submenus to actions, called in EditorMenu::CreateMenus
     * @return NF_ERROR returns NF_ERROR::ok if successful
     */
    NF_ERROR CreateActions();

private slots:
    /**
     * Button functionality for createDesktopShortcutAct.
     * Creates a .desktop file in /home/$USER/.local/share/applications/
     */
    void createDesktopShortcut();

private:
    QMainWindow *mainWindow;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *objectsMenu;
    QMenu *rendererMenu;
    QMenu *buildMenu;
    QMenu *toolsMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;

    QAction *newFileAct;
    QAction *openFileAct;
    QAction *saveFileAct;
    QAction *saveFileAsAct;

    QAction *createDesktopShortcutAct;

    EditorError *err;

};

#endif //NEWFRONTIERSENGINE_EDITORMENU_H
