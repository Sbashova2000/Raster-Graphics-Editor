#include "Session.h"
#include "Image.h"
#include <cstring>


Session::Session()
{
    images = new Image *[imagesCnt];
}


Session::~Session()
{
    for (int i = 0; i < imagesCnt;i++)
    {
        delete[] images[i];
    }

    delete[] images;
}

    
void Session::grayscale()
{
    for (int i = 0; i < curImg; i++)
    {
        images[i]->grayscale();
    }
    history += "grayscale ";
}

void Session::monochrome()
{
    for (int i = 0; i < curImg; i++)
    {
        images[i]->monochrome();
    }
    history += "monochrome ";
}

void Session::rotate(std::string &direction)
{
    for (int i = 0; i < curImg; i++)
    {
        images[i]->rotate(direction);
    }
    history += "rotate " + direction + " ";
}

void Session::addImage(const std::string &name)
{
    Image *img = new Image();
    img->open(name);
    addImage(*img);
}

void Session::addImage(Image &image)
{
    if (curImg == imagesCnt)
    {
        imagesCnt = imagesCnt * 2;
        Image **temp = new Image *[imagesCnt];
        for (int i = 0; i < curImg; i++)
        {
            temp[i] = images[i];
        }
        delete[] images;
        images = temp;
    }
    images[curImg++] = &image;
    std::cout << "Image \"" << image.getName() << "\" added" << std::endl;
}

void Session::sessionInfo()
{
    std::cout << "Name of images in the session: ";
    for (int i = 0; i < curImg; i++)
    {
        std::cout << images[i]->getName() << " ";
    }
    std::cout << std::endl;
    std::cout << "Pending transformations: " << history;
    std::cout << std::endl;
}

void Session::collage(const std::string &direction,const std::string &image1,const std::string &image2, const std::string &outimage)
{
    Image *img1;
    Image*  img2;
    Image* outimg = new Image();
    
    for (int i = 0; i < curImg;i++)
    {
        if (images[i]->getName() == image1) 
        {
           img1 = images[i];
        }
        if (images[i]->getName() == image2)
        {
            img2 = images[i];
        }
    }
   
    outimg->collage(direction, *img1, *img2);
    outimg->setName(outimage);
    addImage(*outimg);
}


void Session::save(int start)
{
    for (int i = start; i < curImg; i++)
    {
        images[i]->save();
    }
}

void Session::saveAs(const std::string &name, int id)
{
    images[id]->saveAs(name);
}



