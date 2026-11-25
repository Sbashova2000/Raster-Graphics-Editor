#include "Image.h"
#include <fstream>


Image::Image()
{
    magicNumber = "P6";
    maxColor = 255;
}


Image::~Image()
{
    for (int i = 0; i < height;i++)
    {
        delete[] image[i];
    }
    delete[] image;
}


void Image::grayscale()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned char average = getPixel(i,j)->getAverage();
            getPixel(i,j)->setValues(average);
        }
    }
    std::cout << "Image has been turned in grayscale" << std::endl;
    
}


void Image::monochrome()
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = getPixel(i,j)->getAverage();
            if (average < 255 / 2)
            {
                average = 255;
            }
            else
            {
                average = 0;
            }
            getPixel(i,j)->setValues(average);
        }
    }
}


void Image::negative()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            getPixel(i,j)->reverse();
        }
    }
}

void Image::rotate(const std::string &direction)
{
    int tempHeight = height;
    height = width;
    width = tempHeight;
    Image *temp = new Image();
    temp->image = new Pixel*[height];
   
    for (int i = 0; i < height; i++)
    {
        temp->image[i] = getNewPixel(width);
        for (int j = 0; j < width; j++)
        {
            if (direction == "left")
            {
                temp->setPixel(i, j, getPixel(j, height - 1 - i));
            }
            else if (direction == "right")
            {
                temp->setPixel(i, j, getPixel(width - 1 - j, i));
            }
        }
    }
    for (int i = 0; i < width;i++)
    {
        delete[] image[i];
    }
    delete[] image;
    image = temp->image;
}


void Image::collage(const std::string &direction, Image &image1, Image &image2)
{
    int width1 = image1.width;
    int height1 = image1.height;
   

    int width2 = image2.width;
    int height2 = image2.height;

    std::string magicNumber1 = image1.magicNumber;
    std::string magicNumber2 = image2.magicNumber;
    // std::cout << width1 << " " << width2 << " " << height1 << " " << height2 << std::endl;

    if(direction == "horizontal")
    {
        if(height1 != height2 && magicNumber1 == magicNumber2)
        {
            std::cout << "Error, the images must have same heights to make horizontal collage" << std::endl;
            return;
        }

        int collageWidth = width1 + width2;
        int collageHeight = height1;

       //allocate memory for the collage image
        image = new Pixel*[collageHeight];
        for (int i = 0; i < collageHeight;i++)
        {
            image[i] = getNewPixel(collageWidth);
        }

        //copy the pixels from the 1st image
        for (int i = 0; i < height1; i++)
        {
            for (int j = 0; j < width1; j++)
            {
                setPixel(i, j, image1.getPixel(i,j));
            }
        }

        // copy the pixels from the 2st image
        for (int i = 0; i < height2; i++)
        {
            for (int j = 0; j < width2; j++)
            {
                setPixel(i, j + width1, image2.getPixel(i,j));
            }
        }
        
        //update collage dimensions
        width = collageWidth;
        height = collageHeight;
    }
    else if(direction == "vertical")
    {
        if (width1 != width2 && magicNumber1 == magicNumber2)
        {
            std::cout << "Error, the images must have same widths to make vertical collage" << std::endl;
            return;
        }
        
        int collageWidth = width1;
        int collageHeight = height1+height2;

        //allocate memory for the collage image
        image = new Pixel*[collageHeight];
        for (int i = 0; i < collageHeight;i++)
        {
            image[i] = getNewPixel(collageWidth);
        }

        for (int i = 0; i < height1; i++)
        {
            for (int j = 0; j < width1; j++)
            {
                setPixel(i,j, image1.getPixel(i,j));
            }
        }
        
        for (int i = 0; i < height2; i++)
        {
            for (int j = 0; j < width2; j++)
            {
                setPixel(i+height1,j, image2.getPixel(i,j));
            }
        }
        
        width = collageWidth;
        height = collageHeight;
    }
}


void Image::save()
{
    saveAs(name);
}


void Image::saveAs(const std::string &filename)
{
    std::cout << "savingFile " << filename << std::endl;
    std::ofstream file(filename, std::ios::binary);
    file << magicNumber << " " << width << " " << height << " " << maxColor << std::endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            getPixel(i,j)->write(file);
        }
    }
}

void Image::open(const std::string &filename)
{
    name = filename;
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "File " << filename << " can`t be open!" << std::endl;
        return;
    }

    file >> magicNumber >> width >> height >> maxColor;

    // std::cout<< magicNumber << " " << width << " " << height;

    if ((magicNumber == "P6" || magicNumber == "P3" || magicNumber == "P5" || magicNumber == "P2") && maxColor > 255)
    {
        std::cout << "This is an unsupported maximum color" << std::endl;
        return;
    }

    image = new Pixel*[height];
    for (int i = 0; i < height; i++)
    {
        image[i] = getNewPixel(width);
        for (int j = 0; j < width; j++)
        {
            getPixel(i,j)->read(file);
            // std::cout << getPixel(i,j)->getAverage() << std::endl;
        }
    }
    file.close();
}


void Image::setName(const std::string &fileName)
{
    name = fileName;
}


std::string Image::getName() const
{
    return name;
}

Pixel* Image::getNewPixel(int count)
{
    if (magicNumber == "P6" || magicNumber == "P3")
        return new PixelPPM[count];
    else if (magicNumber == "P2" || magicNumber == "P5")
        return new PixelPGM[count];
    else if (magicNumber == "P1")
        return new PixelPBM[count];
    return new PixelPPM[count];
}

Pixel *Image::getPixel(int i, int j)
{
    if (magicNumber == "P6" || magicNumber == "P3")
        return &(((PixelPPM*)image[i])[j]);
    else if (magicNumber == "P2" || magicNumber == "P5")
        return &(((PixelPGM*)image[i])[j]);
    else if (magicNumber == "P1")
        return &(((PixelPBM*)image[i])[j]);
    return nullptr;
}

void Image::setPixel(int i, int j, Pixel *pixel)
{
    if (magicNumber == "P6" || magicNumber == "P3")
        (((PixelPPM*)image[i])[j]) = *(PixelPPM*)pixel;
    else if (magicNumber == "P2" || magicNumber == "P5")
        (((PixelPGM*)image[i])[j]) = *(PixelPGM*)pixel;
    else if (magicNumber == "P1")
        (((PixelPBM*)image[i])[j]) = *(PixelPBM*)pixel;
}

/*int Image::getWidth() const
{
    return width;
}

int Image::getHeight() const
{
    return height;
}*/