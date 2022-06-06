//
// Created by Sonnen on 15.05.2022.
//

#include "Editor/EditorFramework/Public/EditorError.h"

#include <QMessageBox>

EditorError::EditorError()
{
    messageBox = new QMessageBox();
}

void EditorError::Check(NF_ERROR e, std::string msg, std::string file, std::string line)
{
    switch(e)
    {
        case NF_ERROR::ok:
        {
            break;
        }
        case NF_ERROR::fatal:
        {
            std::string message = std::string("Fatal error in ") + file +
                                  std::string(" in line " + line + std::string(" with error message: ") + msg);
            messageBox->critical(0, "Error!", message.data(), QMessageBox::StandardButton::Abort);
            break;
        }
        case NF_ERROR::error:
        {
            std::string message = std::string("Error in ") + file +
                                  std::string(" in line " + line + std::string(" with error message: ") + msg);
            messageBox->critical(0, "Error!", message.data(), QMessageBox::StandardButton::Ok);
            break;
        }
        case NF_ERROR::warning:
        {
            std::string message = std::string("Warning in ") + file +
                                  std::string(" in line " + line + std::string(" with warning message: ") + msg);
            messageBox->warning(0, "Warning!", message.data(), QMessageBox::StandardButton::Ok);
            break;
        }
        case NF_ERROR::info:
        {
            std::string message = std::string("Information in ") + file +
                                  std::string(" in line " + line + std::string(" with warning message: ") + msg);
            messageBox->information(0, "Warning!", message.data(), QMessageBox::StandardButton::Ok);
            break;
        }
        default:
        {
            std::string message = std::string("Uncaught error in ") + file +
                                  std::string(" in line " + line + std::string(" without error message!"));
            messageBox->warning(0, "Uncaught error!", message.data(), QMessageBox::StandardButton::Ok);
            break;
        }
    }
}