#pragma once
#include <iostream>
#include "Pixel.h"

class Image
{
private:
    Pixel **image;
    int width;
    int height;
    std::string magicNumber, name;
    int maxColor;

public:
    Image();
    ~Image();
    void grayscale();
    void monochrome();
    void negative();
    void rotate(const std::string& direction);
    void collage(const std::string &direction, Image &image1, Image &image2);

    Pixel *getNewPixel(int count);
    void save();
    void saveAs(const std::string &filename);
    void open(const std::string &filename);
    void setName(const std::string &fileName);
    Pixel *getPixel(int i, int j);
    void setPixel(int i, int j, Pixel *pixel);
    std::string getName() const;
    //int getWidth() const;
    //int getHeight() const;
};