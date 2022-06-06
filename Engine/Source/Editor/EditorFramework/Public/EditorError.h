//
// Created by Sonnen on 15.05.2022.
//

#ifndef NEWFRONTIERSENGINE_EDITORERROR_H
#define NEWFRONTIERSENGINE_EDITORERROR_H

// Don't use directly!
#define STRINGIZE(x) STRINGIZE2(x)
// Don't use directly!
#define STRINGIZE2(x) #x
// Converts __LINE__ into a string, consider using NF_ERR_CHECK instead
#define NF_LINE STRINGIZE(__LINE__)
// Converts __FILE__ into a string, consider using NF_ERR_CHECK instead
#define NF_FILE STRINGIZE(__FILE__)
/**
 * Checks if functions returns an error and displays an error/warning/info window
 * Always use this function!
 * @param err NF_ERROR Call your functions here
 * @param obj EditorError* Insert pointer to EditorError object
 * @param msg char* std::string Insert a string as error message
 */
#define NF_ERR_CHECK(err, obj, msg) obj->Check(err, msg, NF_FILE, NF_LINE)
/**
 * Checks if functions returns an error and displays an error/warning/info window
 * ONLY use this function if you're testing something! It doesn't return a custom message!
 * US = unsafe
 * @param err NF_ERROR Call your functions here
 * @param obj EditorError* Insert pointer to EditorError object
 */
#define NF_ERR_CHECK_US(err, obj) obj->Check(err, "Uncaught error", NF_FILE, NF_LINE)

#include <string>

#include "Editor/General/nf_error.h"

class QMessageBox;

/**
 * Class used to display editor errors as window message box
 * Make sure you ALWAYS use a pointer
 */
class EditorError
{
public:
    EditorError();

    /**
     * Checks if functions returns an error and displays an error/warning/info/etc.. window
     * Use preprocessor directive NF_ERR_CHECK instead.
     * @param e NF_ERROR Call your functions here
     * @param msg std::string Insert a string as error message
     * @param file __FILE__ Add preprocessor directive __FILE__ here
     * @param line __LINE__ Add preprocessor directive __LINE__ here
     * @return bool returns true if function check was successful.
     * @return Returns false if function return an uncaught error
     */
    void Check(NF_ERROR e, std::string msg, std::string file, std::string line);

private:
    QMessageBox* messageBox;
};

#endif //NEWFRONTIERSENGINE_EDITORERROR_H
