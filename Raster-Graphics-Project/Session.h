#pragma once
#include "Image.h"


class Session
{
private:
    int imagesCnt = 2;
    int curImg = 0;
    Image **images = new Image *[imagesCnt];
    std::string history;
    int SessionId;
    int transformationsCnt = 0;

public:
    Session();
    ~Session();
    
    void sessionInfo();
    void grayscale();
    void monochrome();
    void rotate(std::string &direction);
    void addImage(const std::string &name);
    void addImage(Image &image);

    void collage(const std::string &direction,const std::string &image1,const std::string &image2, const std::string &outimage);
   
    void save(int start);
    void saveAs(const std::string &name, int id);
   
};

