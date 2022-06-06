//
// Created by Sonnen on 14.05.2022.
//

#ifndef NEWFRONTIERSENGINE_EDITORVIEWPORT_H
#define NEWFRONTIERSENGINE_EDITORVIEWPORT_H

#include "Editor/General/nf_error.h"

class QMainWindow;
class QString;
class QSize;

/**
 * Used to calculate perfect sizes for the window
 * Responsible for changing window settings
 */
class EditorViewport
{
public:
    /**
     * @param main QMainWindow* Insert MainWindow object pointer
     */
    EditorViewport(QMainWindow* main);

    /**
     * Changes the window title on the top left side
     * You still have to call EditorViewport::SetWindowProperties to make changes!
     * @param title char* New window title
     */
    NF_ERROR SetWindowTitle(char* title);
    /**
     * Changes the window minimum size. This means the window won't be smaller that those values
     * You still have to call EditorViewport::SetWindowProperties to make changes!
     * @param width int New window minimum width size
     * @param height int New window minimum height size
     */
    NF_ERROR SetMinimumWindowSize(int width, int height);
    /**
     * Changes the window size. This means the window will be displayed in that size
     * You still have to call EditorViewport::SetWindowProperties to make changes!
     * @param width int New window width size
     * @param height int New window height size
     */
    NF_ERROR SetWindowHeight(int width, int height);
    /**
     * Calculates a good window size at display resolution * 75% for width and height
     * You still have to call EditorViewport::SetWindowProperties to make changes!
     */
    NF_ERROR CalculateStartupWindowSize();

    /**
     * Pushes all changes to main window
     */
    NF_ERROR PushWindowProperties();

private: // private objects
    QMainWindow* mainWindow;
    QString* windowTitle;

private: // private variables
    int windowWidth = 0;
    int windowHeight = 0;

    int minWindowWidth = 800;
    int minWindowHeight = 600;
};

#endif //NEWFRONTIERSENGINE_EDITORVIEWPORT_H
