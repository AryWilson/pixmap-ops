// Copyright 2021, Aline Normoyle, alinen

#include "image.h"

#include <cassert>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace agl {


Image::Image() {
   // default constructor
   w = 0;
   h = 0;
   ch = 3;
}

Image::Image(int width, int height)  {
   w = width;
   h = height;
   ch = 3;
   // general constructor

}

Image::Image(const Image& orig){
   // copy constructor
   w = orig.w;
   h = orig.h;
   ch = orig.ch;
   _data = (orig._data);

  
}

Image& Image::operator=(const Image& orig) {
   // assignment operator
  if (&orig == this) {
    return *this;
  }
   w = orig.w;
   h = orig.h;
   ch = orig.ch;
   _data = orig._data;
   return *this;
}

Image::~Image() {
   // destructor
   if (_data != NULL){
      // stbi_image_free(_data);
      delete[] _data;
   }
}

int Image::width() const { 
   return w;
}

int Image::height() const {
   return h;
}

char* Image::data() const {
   return _data;
}

void Image::set(int width, int height, unsigned char* data) {
   w = width;
   h = height;
   _data = (char*) data; // this casting ok?????
   // _data = new char[w*h*ch);
   // for (int i=0; i<w; i+=ch){
   //    for (int j=0; i<h; i++){

   //       _data[i*w+j] = red;
   //       _data[i*w+j] = green;
   //       _data[i*w+j] = blue;
   //    }
   // }

}

bool Image::load(const std::string& filename, bool flip) {
   int width,height,channels = 0;
   unsigned char *pic = stbi_load(filename.c_str() , &width, &height, &channels, 3);

   if (pic != NULL){
      w = width;
      h = height;
      ch = channels;
      _data = new char[w*h*ch];
      // copy values, in which case we can free pic
      for(int i = 0; i<w*h*ch; i++){
         _data[i] = pic[i];
      }
      // change member pointer, in which case, free @ destructor?
      // _data = (char*) pic;
      return true;
   }
   stbi_image_free(pic);
   return false;
}


bool Image::save(const std::string& filename, bool flip) const {
   if(_data != NULL){
      stbi_write_png((filename.c_str()) , w, h, ch, _data, w * ch);
      return true;
   }
   return false;
}

Pixel Image::get(int row, int col) const {
   unsigned char r,g,b = 0;
   if((row < h) & (col < ch*w)){
      r = _data[row*w + col];
      g = _data[row*w + col];
      b = _data[row*w + col];
   }
   return Pixel{ r, g, b };
}

void Image::set(int row, int col, const Pixel& color) {
   //check for valid inputs
   if((row < h) & (col < ch*w)){
      _data[row*w + col] = color.r;
      _data[row*w + col + 1] = color.g;
      _data[row*w + col + 2] = color.b;
   }

 
}


Pixel Image::get(int i) const
{
   unsigned char r,g,b = 0;
   if(i < w*h){
      r = _data[i*ch];
      g = _data[i*ch + 1];
      b = _data[i*ch + 2];
   }
   return Pixel{ r, g, b };
}

void Image::set(int i, const Pixel& c)
{
      if(i < w*h){
      _data[i*ch] = c.r;
      _data[i*ch + 1] = c.g;
      _data[i*ch + 2] = c.b;
   }
}

Image Image::resize(int width, int height) const {
   Image result(width, height);
   result._data = new char[width*height*3];
   for(int i = 0; i<width; i++){
      for(int j = 0; j<height; j++){
         int _i = floor((i/(h-1))*(height-1));
         int _j = floor((j/(w-1))*(width-1));
         result._data[i*width + j] = _data[_i*w + _j];
         result._data[i*width + j + 1] = _data[_i*w + _j + 1];
         result._data[i*width + j + 2] = _data[_i*w + _j + 2];
      }

   }
   return result;
}

Image Image::flipHorizontal() const {
   Image result(0, 0);
   return result;

}

Image Image::flipVertical() const {
   Image result(0, 0);
   return result;
}

Image Image::rotate90() const {
   Image result(0, 0);
  
   return result;
}

Image Image::subimage(int startx, int starty, int width, int height) const {
   Image sub(width, height);
   sub._data = new char[width*height*3];
   int index = 0;
   for (int i = startx; i < startx+width; i++){
      for (int j = starty; j < starty+height; j++){
         sub._data[index] = _data[i*width + j];
         sub._data[index + 1] = _data[i*width + j + 1];
         sub._data[index + 2] = _data[i*width + j + 2];
         index += 3;

      }
   }
   return sub;
}

void Image::replace(const Image& image, int startx, int starty) {
   int width = image.w;
   int height = image.h;

   for (int _i = startx, i = 0; _i < w && i < width; _i++, i++){
      for (int _j = starty, j = 0; _j < h && j < height; _j++, j++){
         _data[_i*w + _j] = image._data[i*w + j];
         _data[_i*w + _j + 1] = image._data[i*w + j + 1];
         _data[_i*w + _j + 2] = image._data[_i*w + _j + 2];
      }
   }
  
}

Image Image::swirl() const {
   Image result(0, 0);
   return result;
}

Image Image::add(const Image& other) const {
   Image result(0, 0);
  
   return result;
}

Image Image::subtract(const Image& other) const {
   Image result(0, 0);
   
   return result;
}

Image Image::multiply(const Image& other) const {
   Image result(0, 0);
   
   return result;
}

Image Image::difference(const Image& other) const {
   Image result(0, 0);
  
   return result;
}

Image Image::lightest(const Image& other) const {
   Image result(0, 0);
  
   return result;
}

Image Image::darkest(const Image& other) const {
   Image result(0, 0);
  
   return result;
}

Image Image::gammaCorrect(float gamma) const {

   Image result(w, h);
   result._data = new char[w*h*3];
   for(int i = 0; i<w*h*ch; i++){
      result._data[i] = pow(_data[i],(1/gamma));
   }

 
   return result;
}

Image Image::alphaBlend(const Image& other, float alpha) const {
   Image result(w, h);
   result._data = new char[w*h*3];
   for(int i = 0; i<w*h; i++){
      char r = _data[i];
      char g = _data[i+1];
      char b = _data[i+2];
      char otherR = other._data[i];
      char otherG = other._data[i+1];
      char otherB = other._data[i+2];
      result._data[i] = r*(1-alpha) + otherR*(alpha);
      result._data[i + 1] = g*(1-alpha) + otherG*(alpha);
      result._data[i + 2] = b*(1-alpha) + otherB*(alpha);
   }

   return result;
}

Image Image::invert() const {
   Image image(0, 0);
   
   return image;
}

Image Image::grayscale() const {
   Image result(w, h);
   result._data = new char[w*h];
   for(int i = 0; i<w*h; i++){
      char r = _data[i];
      char g = _data[i+1];
      char b = _data[i+2];
      result._data[i] = r*.11 + g*.59 + b*.11;
   }
   
   return result;
}

Image Image::colorJitter(int size) const {
   Image image(0, 0);
  
   return image;
}

Image Image::bitmap(int size) const {
   Image image(0, 0);
   
   return image;
}

void Image::fill(const Pixel& c) {
  }

}  // namespace agl

