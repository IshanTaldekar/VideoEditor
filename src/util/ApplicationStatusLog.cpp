#include "ApplicationStatusLog.h"

/**
 * Open file that the log messages will be written to.
 */
ApplicationStatusLog::ApplicationStatusLog() {

    app_log = ofstream("./VideoEditor/build/app.log", ofstream::out | ofstream::trunc);
    add("Application Start-up.");

}

/**
 * Close log file.
 */
ApplicationStatusLog::~ApplicationStatusLog() {

    app_log.close();

}

/**
 * Write a message to log file.
 *
 * @param message the (string) message to be written.
 */
void ApplicationStatusLog::add(string message) {

    app_log << ">>> " << message << endl << endl;
    app_log.flush();

}