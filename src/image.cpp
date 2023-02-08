// Copyright 2021, Aline Normoyle, alinen

#include "image.h"

#include <cassert>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace agl {

void Image::clean(){
   w = 0;
   h = 0;
   ch = 3;
   if (_data != nullptr){
      if (stb_load){
         stbi_image_free(_data);
         _data = nullptr;
         stb_load = false;
      }
      if (_data != nullptr){
         delete[] _data;
         _data = nullptr;
      }
   }


}

Image::Image() {
   // default constructor
   w = 0;
   h = 0;
   ch = 3;
   _data = new struct Pixel[w*h];
}

Image::Image(int width, int height)  {
   w = width;
   h = height;
   ch = 3;
   _data = new struct Pixel[w*h];
   // general constructor

}

Image::Image(const Image& orig){
   // copy constructor
   w = orig.w;
   h = orig.h;
   ch = orig.ch;
   _data = new struct Pixel[w*h];
   memcpy(_data, orig._data, w*h*sizeof(struct Pixel));
   // _data = (orig._data);

  
}

Image& Image::operator=(const Image& orig) {
   // assignment operator
  if (&orig == this) {
   return *this;
  }
  if (_data != nullptr){
   clean();
  }

   w = orig.w;
   h = orig.h;
   ch = orig.ch;
   // _data = orig._data;
   _data = new struct Pixel[w*h];
   memcpy(_data, orig._data, w*h*sizeof(struct Pixel));
   
   return *this;
}

Image::~Image() {
   // destructor
   clean();
}

int Image::width() const { 
   return w;
}

int Image::height() const {
   return h;
}

char* Image::data() const {
   return (char*) _data;
}

void Image::set(int width, int height, unsigned char* data) { 
   if (_data != nullptr){
      clean();
   }
   w = width;
   h = height;
   // _data = (char*) data;
   _data = new struct Pixel[w*h];
   memcpy(_data, data, w*h*sizeof(struct Pixel));



}

bool Image::load(const std::string& filename, bool flip) {
   int width,height,channels = 0;
   unsigned char *pic = stbi_load(filename.c_str() , &width, &height, &channels, 3);

   
   if (pic != nullptr){
      if (_data != nullptr){
         clean();
      }
      w = width;
      h = height;
      ch = channels;

      _data = (struct Pixel *) pic;
      stb_load = true;
      return true;
   }
   return false;
}


bool Image::save(const std::string& filename, bool flip) const {
   if(_data != nullptr){ 
      return stbi_write_png((filename.c_str()) , w, h, ch, _data, w * ch); //valgrind
   }
   std::cout << "didnt save " << filename << std::endl;
   return false;
}

Pixel Image::get(int row, int col) const {
   if((row >= 0) && (col >= 0) && (row < h) && (col < w) && (_data != nullptr)){
      return _data[row*w + col];
   }
   return Pixel{ 0, 0, 0 };
}

void Image::set(int row, int col, const Pixel& color) {
   //check for valid inputs
   if((row >= 0) && (col >= 0) && (row < h) && (col < w) && (_data != nullptr)){

      _data[row*w + col] = color;
   }
}

Pixel Image::get(int i) const
{
   if( i <= 0 && i < w*h  && (_data != nullptr)){
      return _data[i];
   }
   return Pixel{ 0, 0, 0 };
}

void Image::set(int i, const Pixel& c)
{
   if( i <= 0 && i < w*h*ch && (_data != nullptr)){
      _data[i] = c;
   }
}

/// //////////////////
Image Image::resize(int width, int height) const {
   Image result(width, height);
   for(int i = 0; i<width; i++){
      int _i = floor((i/(height-1.0f))*(h-1.0f));
      for(int j = 0; j<height; j++){
         int _j = floor((j/(width-1.0f))*(w-1.0f));
         if((_i < w) && (_j < h) && (0 <= _i) && (0 <= _j)){
            result.set(i,j,get(_i,_j));
         }
      }

   }
   return result;
}

Image Image::flipHorizontal() const {
   Image result(w, h);
   for(int i = 0; i < round(w/2.0f + 0.5f) ; i++){
      for(int j = 0; j < h; j++){
         struct Pixel swap = get((w-1)-i,j);
         result.set((w-1)-i,j, get(i,j));
         result.set(i,j,swap);
      }
   }

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
   for (int _i = startx, i = 0; _i < startx+width && _i < w; _i++, i++){
      for (int _j = starty, j = 0; _j < starty+height && _j < h; _j++, j++){
         sub.set(i,j,get(_i,_j));
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
   for(int i = 0; i<w ; i++){
      for(int j = 0; j<h ; j++){
         Pixel temp = get(i,j);
         unsigned char r = round(pow(temp.r/255.0f,(1.0f/gamma))*255.0f);
         unsigned char g = round(pow(temp.g/255.0f,(1.0f/gamma))*255.0f);
         unsigned char b = round(pow(temp.b/255.0f,(1.0f/gamma))*255.0f);
         result.set(i,j,Pixel{r,g,b});
      }
   }
 
   return result;
}

Image Image::alphaBlend(const Image& other, float alpha) const {
   Image result(w,h);
   if(_data == nullptr || other._data == nullptr){return result;}

   for(int i = 0; i<w*h; i++){
      _data[i].r = _data[i].r*(1-alpha) + other._data[i].r*(alpha);
      _data[i].g = _data[i].g*(1-alpha) + other._data[i].g*(alpha);
      _data[i].b = _data[i].b*(1-alpha) + other._data[i].b*(alpha);
   }

   return result;
}

Image Image::invert() const {
   Image image(0, 0);
   
   return image;
}

Image Image::grayscale() const {
   Image result(w, h);
   for(int i = 0; i < w; i++){
      for(int j = 0; j < h; j++){
         struct Pixel rgb = get(i,j);
         unsigned char val = rgb.r*.11 + rgb.g*.59 + rgb.b*.11;
         result.set(i,j,Pixel{val, val, val});
         // result._data[i*w + j] = rgb.r*.11 + rgb.g*.59 + rgb.b*.11;

      }
   }
   // for(int i = 0; i<w*h*ch; i++){
   //    char r = _data[i];
   //    char g = _data[i+1];
   //    char b = _data[i+2];
   //    result._data[i] = r*.11 + g*.59 + b*.11;
   // }
   
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

