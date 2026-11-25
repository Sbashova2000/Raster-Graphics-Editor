#include <iostream>
#include <fstream>

class Pixel
{
public:
    virtual unsigned char getAverage() = 0;
    virtual void read(std::ifstream &file) = 0;
    virtual void write(std::ofstream &file) = 0;
    virtual void setValues(unsigned char Color) = 0;
    virtual void reverse() = 0;
};

class PixelPPM:public Pixel
{
public:
    unsigned char Red = 0, Green = 0, Blue= 0;
    unsigned char getAverage() 
    {
        return (Red + Green + Blue) / 3;
    }

    void setValues(unsigned char Color)
    {
        Red = Color;
        Green = Color;
        Blue = Color;
    }

    void reverse()
    {
        Red = 255 - Red;
        Green = 255 - Green;
        Blue = 255 - Blue;
    }
    void read(std::ifstream &file) 
    {
        file.read((char *)&Red, sizeof(unsigned char));
        file.read((char *)&Green, sizeof(unsigned char));
        file.read((char *)&Blue, sizeof(unsigned char));
        // std::cout << "Reading";
    }
    void write(std::ofstream &file) 
    {
        file.write((char *)&Red, sizeof(unsigned char));
        file.write((char *)&Green, sizeof(unsigned char));
        file.write((char *)&Blue, sizeof(unsigned char));
    }
};

class PixelPBM : public Pixel
{
public:
    bool Color = 0;
    unsigned char getAverage()
    {
        return Color;
    }

    void setValues(unsigned char Col)
    {
        Color = Col;
    }

    void reverse()
    {
        Color = !Color;
    }
    void read(std::ifstream &file) 
    {
        file.read((char *)&Color, sizeof(bool));
    }
    void write(std::ofstream &file) 
    {
        file.write((char *)&Color, sizeof(bool));
    }
};

class PixelPGM : public Pixel
{
    public:
    unsigned char Color = 0;
    unsigned char getAverage()
    {
        return Color;
    }
    void setValues(unsigned char Col)
    {
        Color = Col;
    }

    void reverse()
    {
        Color = 255 - Color;
    }
    void read(std::ifstream &file) 
    {
        file.read((char *)&Color, sizeof(unsigned char));
    }
    void write(std::ofstream &file) 
    {
        file.write((char *)&Color, sizeof(unsigned char));
    }
};