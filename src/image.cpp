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
  if (_data != nullptr){
   delete _data;
   _data = orig._data;
  }
   w = orig.w;
   h = orig.h;
   ch = orig.ch;
   
   return *this;
}

Image::~Image() {
   // destructor
   if (_data != nullptr){
      // stbi_image_free(_data);
      delete _data;
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
   if (_data != nullptr){
      delete _data;
   }
   _data = (char*) data;

}

bool Image::load(const std::string& filename, bool flip) {
   int width,height,channels = 0;
   unsigned char *pic = stbi_load(filename.c_str() , &width, &height, &channels, 3);

   
   if (pic != nullptr){
      w = width;
      h = height;
      ch = channels;
      if (_data != nullptr){
         delete _data;
         _data = new char[w*h*ch];

      }
      // copy values, in which case we can free pic
      for(int i = 0; i<w*h*ch; i++){
         _data[i] = pic[i];
      }
      stbi_image_free(pic);
      return true;
   }
   return false;
}


bool Image::save(const std::string& filename, bool flip) const {
   if(_data != nullptr){ //valgrind conditional jump, uninitialized values
      //returns int
      stbi_write_png((filename.c_str()) , w, h, ch, _data, w * ch); //valgrind
      return true;
   }
   return false;
}

Pixel Image::get(int row, int col) const {
   unsigned char r,g,b = 0;
   if((row < h) && (col < w) && (_data != nullptr)){
      r = _data[ch*row*w + ch*col];
      g = _data[ch*row*w + ch*col + 1];
      b = _data[ch*row*w + ch*col + 2];
   }
   return Pixel{ r, g, b };
}

void Image::set(int row, int col, const Pixel& color) {
   //check for valid inputs
   if((row < h) & (col < w) && (_data != nullptr)){
      _data[ch*row*w + ch*col] = color.r;
      _data[ch*row*w + ch*col + 1] = color.g;
      _data[ch*row*w + ch*col + 2] = color.b;
   }

 
}


Pixel Image::get(int i) const
{
   unsigned char r,g,b = 0;
   if(i < w*h*ch  && (_data != nullptr)){
      r = _data[i*ch];
      g = _data[i*ch + 1];
      b = _data[i*ch + 2];
   }
   return Pixel{ r, g, b };
}

void Image::set(int i, const Pixel& c)
{
      if(i < w*h*ch && (_data != nullptr)){
      _data[i*ch] = c.r;
      _data[i*ch + 1] = c.g;
      _data[i*ch + 2] = c.b;
   }
}

Image Image::resize(int width, int height) const {
   Image result(width, height);
   if(_data == nullptr){return result;}

   result._data = new char[width*height*ch];
   for(int i = 0; i<width; i++){
      for(int j = 0; j<height; j++){
         int _i = floor((i/(h-1.0f))*(height-1));
         int _j = floor((j/(w-1.0f))*(width-1));

         result.set(i,j,get(_i,_j));
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
   if(_data == nullptr){return sub;}
   sub._data = new char[width*height*3];
   int index = 0;
   for (int i = startx; i < startx+width; i++){
      for (int j = starty; j < starty+height; j++){
         sub.set(index,get(i,j));
         index += 3;

      }
   }
   return sub;
}

void Image::replace(const Image& image, int startx, int starty) {
   int width = image.w;
   int height = image.h;
   if(_data == nullptr || image._data == nullptr){return;}

   for (int _i = startx, i = 0; _i < w && i < width; _i++, i++){
      for (int _j = starty, j = 0; _j < h && j < height; _j++, j++){
         set(_i,_j,image.get(i,j));
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
   if(_data == nullptr){return result;}
   result._data = new char[w*h*3];
   for(int i = 0; i<w*h*ch; i++){
      result._data[i] = pow(_data[i],(1/gamma));
   }

 
   return result;
}

Image Image::alphaBlend(const Image& other, float alpha) const {
   Image result(w,h);
   if(_data == nullptr || other._data == nullptr){return result;}

   result._data = new char[w*h*ch];
   for(int i = 0; i<w*h*ch; i++){
      _data[i] = _data[i]*(1-alpha) + other._data[i]*(alpha);
   }

   return result;
}

Image Image::invert() const {
   Image image(0, 0);
   
   return image;
}

Image Image::grayscale() const {
   Image result(w, h);
   if(_data == nullptr){return result;}
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

