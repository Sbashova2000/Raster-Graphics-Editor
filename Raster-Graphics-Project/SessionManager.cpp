#include "SessionManager.h"


SessionManager::SessionManager()
{
    sessions = new Session *[sessionCnt];
}

SessionManager::~SessionManager()
{
    for (int i = 0; i < sessionCnt;i++)
    {
        delete[] sessions[i];
    }
    delete[] sessions;
}

void SessionManager::load(const std::string &name)
{
    if (curSession == sessionCnt)
    {
        sessionCnt = sessionCnt * 2;
        Session **temp = new Session *[sessionCnt];
        for (int i = 0; i < curSession; i++)
        {
            temp[i] = sessions[i];
        }
        delete[] sessions;
        sessions = temp;
    }

    currId = sessionCnt;

    Session *next = new Session();
    currId = curSession;
    sessions[curSession++] = next;
    std::cout << "Session with ID: " << currId << " started" << std::endl;

    sessions[currId]->addImage(name);
}

Session *SessionManager::getSession()
{
    return sessions[currId];
}

void SessionManager::switchSession(int id)
{

    if (id <= 0 || id > curSession)
    {
        std::cout << "Error" << std::endl;
    }
    else
    {
        currId = id;
        std::cout << "You switched to session with ID: " << id << std::endl;
        sessions[currId]->sessionInfo();
    }
}