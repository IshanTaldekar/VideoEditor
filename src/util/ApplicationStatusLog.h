#include "Dependencies.h"

#ifndef VIDEOEDITORAPP_STATUSLOGGER_H
#define VIDEOEDITORAPP_STATUSLOGGER_H


class ApplicationStatusLog {

    ofstream app_log;

public:

    ApplicationStatusLog();
    ~ApplicationStatusLog();
    void add(string message);

};

#endif//VIDEOEDITORAPP_STATUSLOGGER_H
