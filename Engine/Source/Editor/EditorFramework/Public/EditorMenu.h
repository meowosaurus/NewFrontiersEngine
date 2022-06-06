//
// Created by Sonnen on 14.05.2022.
//

#ifndef NEWFRONTIERSENGINE_EDITORMENU_H
#define NEWFRONTIERSENGINE_EDITORMENU_H

#include "Editor/General/nf_error.h"

class QMainWindow;
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class EditorError;

class EditorMenu
{
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

private:
    QMainWindow *mainWindow;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *objectsMenu;
    QMenu *rendererMenu;
    QMenu *buildMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;

    QAction *newFileAct;
    QAction *openFileAct;
    QAction *saveFileAct;
    QAction *saveFileAsAct;

    EditorError *err;

};

#endif //NEWFRONTIERSENGINE_EDITORMENU_H
