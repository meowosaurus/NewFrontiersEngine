//
// Created by Sonnen on 14.05.2022.
//

#include "Editor/EditorFramework/Public/EditorViewport.h"

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QApplication>
#include <QScreen>

EditorViewport::EditorViewport(QMainWindow *main)
{
    this->mainWindow = main;

    this->windowTitle = new QString("NewFrontiers Engine");
}

NF_ERROR EditorViewport::SetWindowTitle(char* title)
{
    this->windowTitle = new QString(title);

    return NF_ERROR::ok;
}

NF_ERROR EditorViewport::SetMinimumWindowSize(int width, int height)
{
    this->minWindowWidth = width;
    this->minWindowHeight = height;

    return NF_ERROR::ok;
}

NF_ERROR EditorViewport::SetWindowHeight(int width, int height)
{
    this->windowWidth = width;
    this->windowHeight = height;

    return NF_ERROR::ok;
}

NF_ERROR EditorViewport::CalculateStartupWindowSize()
{
    // Get screen size of first display, under modern operation systems always the main window
    QSize mainDisplaySize = qApp->screens()[0]->size();

    this->windowWidth = mainDisplaySize.width() * 0.75f;
    this->windowHeight = mainDisplaySize.height() * 0.75f;

    return NF_ERROR::ok;
}

NF_ERROR EditorViewport::PushWindowProperties()
{
    if(this->windowWidth == 0)
        this->windowWidth = this->minWindowWidth;
    if(this->windowHeight == 0)
        this->windowHeight = this->minWindowHeight;

    this->mainWindow->setWindowTitle(*windowTitle);
    this->mainWindow->setMinimumSize(this->minWindowWidth, this->minWindowHeight);
    this->mainWindow->resize(this->windowWidth, this->windowHeight);

    return NF_ERROR::ok;
}
