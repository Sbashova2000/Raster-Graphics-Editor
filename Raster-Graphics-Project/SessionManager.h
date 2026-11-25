#pragma once
#include "Session.h"

class SessionManager
{
private:
    Session **sessions;
    int currId, sessionCnt = 2, curSession = 1;

public:
    SessionManager();
    ~SessionManager();
    void switchSession(int id);
    Session *getSession();
    void load(const std::string &name);
};