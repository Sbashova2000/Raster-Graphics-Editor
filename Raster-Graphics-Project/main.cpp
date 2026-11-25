#include <iostream>
#include <string>
#include <sstream>
#include "Image.h"
#include "Session.h"
#include "SessionManager.h"

int main()
{
    SessionManager ses;

    std::string commands[] = {"load", "close", "save", "help", "exit", "grayscale", "monochrome", "negative", "rotate", "undo", "add", "session", "switch", "collage"};
    enum commandNames
    {
        load,
        close,
        save,
        help,
        exit,
        grayscale,
        monochrome,
        negative,
        rotate,
        undo,
        add,
        session,
        Switch,
        collage
    };
    
    std::string line, command;
    int commandId;

    std::cout << "Please enter command: " << std::endl;
    while (true)
    {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        iss >> command;

        for (int i = 0; i < 14; i++)
        {
            if (commands[i] == command)
            {
                commandId = i;
                break;
            }
        }

        switch (commandId)
        {
        case load:
        {
            std::string filename;
            iss >> filename;
            ses.load(filename);
            break;
        }
        case close:
            break;
        case save:
        {
            std::string temp;
            int count = 0;
            iss >> temp;
            if (temp == "as")
            {
                while (iss >> temp)
                {
                    ses.getSession()->saveAs(temp, count);
                    count++;
                }
                ses.getSession()->save(count);
            }
            else
            {
                ses.getSession()->save(0);
            }
            break;
        }
        case help:
            std::cout << "HELP MEEE" << std::endl;
            break;
        case exit:
            return 0;
            break;
        case grayscale:
            ses.getSession()->grayscale();
            break;
        case monochrome:
            ses.getSession()->monochrome();
            break;
        case negative:
            break;
        case rotate:
        {
            std::string direction;
            iss >> direction;
            ses.getSession()->rotate(direction);
            break;
        }
        case undo:
            break;
        case add:
        {
            std::string filename;
            iss >> filename;
            ses.getSession()->addImage(filename);
            break;
        }
        case session:
            ses.getSession()->sessionInfo();
            break;
        case Switch:
        {
            int id;
            iss >> id;
            ses.switchSession(id);
            break;
        }
        case collage:
        {
            std::string direction, img1,img2,outImg;
            iss >> direction >> img1 >> img2 >> outImg;
            ses.getSession()->collage(direction,img1,img2,outImg);
            break;
        }
        default:
            return 0;
        }
    }

    // loadPPM(filename, width, height);

    

    return 0;
}