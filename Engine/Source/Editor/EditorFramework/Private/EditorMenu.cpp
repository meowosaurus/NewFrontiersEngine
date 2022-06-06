//
// Created by Sonnen on 14.05.2022.
//

#include "Editor/EditorFramework/Public/EditorMenu.h"
#include "Editor/EditorFramework/Public/EditorError.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QWidget>
#include <QAction>
#include <QDir>

EditorMenu::EditorMenu(QMainWindow *mainWindow)
{
    this->mainWindow = mainWindow;

    this->err = new EditorError();
}

NF_ERROR EditorMenu::CreateMenus()
{
    NF_ERR_CHECK(CreateActions(), err, "Unable to create main window action buttons");

    fileMenu = this->mainWindow->menuBar()->addMenu(QWidget::tr("&File"));
    if(fileMenu == nullptr)
        return NF_ERROR::error;
    editMenu = this->mainWindow->menuBar()->addMenu(QWidget::tr("&Edit"));
    if(editMenu == nullptr)
        return NF_ERROR::error;
    objectsMenu = this->mainWindow->menuBar()->addMenu(QWidget::tr("&Objects"));
    if(objectsMenu == nullptr)
        return NF_ERROR::error;
    rendererMenu = this->mainWindow->menuBar()->addMenu(QWidget::tr("&Renderer"));
    if(rendererMenu == nullptr)
        return NF_ERROR::error;
    buildMenu = this->mainWindow->menuBar()->addMenu(QWidget::tr("&Build"));
    if(buildMenu == nullptr)
        return NF_ERROR::error;
    windowMenu = this->mainWindow->menuBar()->addMenu(QWidget::tr("&Window"));
    if(windowMenu == nullptr)
        return NF_ERROR::error;
    toolsMenu = this->mainWindow->menuBar()->addMenu(QWidget::tr("&Tools"));
    if(toolsMenu == nullptr)
        return NF_ERROR::error;
    helpMenu = this->mainWindow->menuBar()->addMenu(QWidget::tr("&Help"));
    if(helpMenu == nullptr)
        return NF_ERROR::error;

    // File menu
    fileMenu->addAction(newFileAct);
    fileMenu->addAction(openFileAct);
    fileMenu->addAction(saveFileAct);
    fileMenu->addAction(saveFileAsAct);

    // Tools menu
    toolsMenu->addAction(createDesktopShortcutAct);

    return NF_ERROR::ok;
}

NF_ERROR EditorMenu::CreateActions()
{
    newFileAct = new QAction(QAction::tr("New File"), this->mainWindow);
    if(newFileAct == nullptr)
        return NF_ERROR::error;
    newFileAct->setStatusTip("Create a new file");

    openFileAct = new QAction(QAction::tr("Open File"), this->mainWindow);
    if(openFileAct == nullptr)
        return NF_ERROR::error;
    openFileAct->setStatusTip("Open existing file");

    saveFileAct = new QAction(QAction::tr("Save File"), this->mainWindow);
    if(saveFileAct == nullptr)
        return NF_ERROR::error;
    saveFileAct->setStatusTip("Save current file");

    saveFileAsAct = new QAction(QAction::tr("Save File As.."), this->mainWindow);
    if(saveFileAsAct == nullptr)
        return NF_ERROR::error;
    saveFileAsAct->setStatusTip("Save current file as new file..");

    // Action menu

    createDesktopShortcutAct = new QAction(QAction::tr("Create Desktop Shortcut"), this->mainWindow);
    if(createDesktopShortcutAct == nullptr)
        return NF_ERROR::error;
    createDesktopShortcutAct->setStatusTip("Create an engine desktop shortcut");
    connect(createDesktopShortcutAct, &QAction::triggered, this, &EditorMenu::createDesktopShortcut);

    return NF_ERROR::ok;
}

void EditorMenu::createDesktopShortcut()
{
    // ToDo: Check if OS is Linux
    QString command = QString("printf \"[Desktop Entry]\nName=NewFrontiersEngine\nExec="
            + QDir::currentPath() + "/NewFrontiersEngine\n"
            + "Icon=" + QDir::currentPath() + "/../Engine/Images/nfe_icon.jpg\n"
            + "Type=Application\" >> /home/$USER/.local/share/applications/nfe.desktop");
    system(command.toStdString().c_str());
}