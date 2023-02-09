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
   w = orig.width();
   h = orig.height();
   ch = orig.ch;
   _data = new struct Pixel[w*h];
   memcpy(_data, orig._data, w*h*sizeof(struct Pixel));

  
}

Image& Image::operator=(const Image& orig) {
   // assignment operator
  if (&orig == this) {
   return *this;
  }
  if (_data != nullptr){
   clean();
  }

   w = orig.width();
   h = orig.height();
   ch = orig.ch;
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
   return (char *) _data;
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
   stbi_set_flip_vertically_on_load(flip);
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
   stbi_set_flip_vertically_on_load(flip);
   if(_data != nullptr){ 
      return stbi_write_png((filename.c_str()) , w, h, ch, _data, w * sizeof(struct Pixel)); //valgrind
   }
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
   if( i <= 0 && i < w*h && (_data != nullptr)){
      _data[i] = c;
   }
}

/// //////////////////
Image Image::resize(int width, int height) const {
   Image result(width, height);
   for(int i = 0; i<result.width(); i++){
      int _i = floor((i/(result.height()-1.0f))*(h-1.0f));
      for(int j = 0; j<result.height(); j++){
         int _j = floor((j/(result.width()-1.0f))*(w-1.0f));
         if((_i < w) && (_j < h) && (0 <= _i) && (0 <= _j)){
            result.set(i,j,get(_i,_j));
         } else{
            result.set(i,j,Pixel{0,255,0});
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
   for (int _i = startx, i = 0; _i < startx+sub.width(); _i++, i++){
      for (int _j = starty, j = 0; _j < starty+sub.height(); _j++, j++){
         if ((_i < w) && (_j < h) && (_i >= 0) && (_j >= 0)){
            sub.set(i,j,get(_i,_j));
         } else {
            sub.set(i,j,Pixel{0,0,0});
         }
      }
   }
   return sub;
}

void Image::replace(const Image& image, int startx, int starty) {
   int width = image.width();
   int height = image.height();
   if(_data == nullptr || image.data() == nullptr){return;}

   for (int _i = startx, i = 0; _i < w && i < width; _i++, i++){
      for (int _j = starty, j = 0; _j < h && j < height; _j++, j++){
         set(_i,_j,image.get(i,j));
      }
   }
  
}

Image Image::swirl() const {
   Image result(w, h);
   for(int i = 0; i < w; i++){
      for(int j = 0; j < h; j++){
         struct Pixel from = get(i,j);
         unsigned char r = from.b;
         unsigned char g = from.r;
         unsigned char b = from.g;
         result.set(i,j,Pixel{r,g,b});
      }
   }
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

Image Image::monochrome(int opt) const {
   int red,green,blue = 0;
   switch(opt){
    case 0: // red
         red = 1;
         green = 0;
         blue = 0;
         break;
    case 1:
         green = 1;
         red = 0;
         blue = 0;
         break;
    case 2:
         blue = 1;
         green = 0;
         red = 0;
         break;
   case 3: // yellow
         red = 1;
         green = 1;
         blue = 0;
         break;
    case 4: // magenta
         red = 1;
         green = 0;
         blue = 1;
         break;
    case 5: // teal
         blue = 1;
         green = 1;
         red = 0;
         break;
    default:
         return grayscale();
}

   Image result(w, h);
   for(int i = 0; i < w; i++){
      for(int j = 0; j < h; j++){
         struct Pixel from = get(i,j);
         unsigned char r = (from.r)*(red);
         unsigned char g = (from.g)*(green);
         unsigned char b = (from.b)*(blue);
         result.set(i,j,Pixel{r,g,b});
      }
   }
   return result;
}

Image Image::saturate(unsigned char ammount) const{
   Image result(w, h);
   unsigned char a = ammount;
   unsigned char r,g,b = 0;
   for(int i = 0; i < w; i++){
      for(int j = 0; j < h; j++){
         struct Pixel from = get(i,j);
         if(from.r >= from.g && from.r>= from.g){
            (from.r < 255-2*a)? (r = from.r + 2*a) : (r = 255);
            (from.g-a > 0)? (g = from.g - a) : (g = 0);
            (from.b-a > 0)? (b = from.b - a) : (b = 0);
         } else if(from.g >= from.r && from.g>= from.b){
            (from.g < 255-2*a)? (g = from.g + 2*a) : (g = 255);
            (from.r-a > 0)? (r = from.r - a) : (r = 0);
            (from.b-a > 0)? (b = from.b - a) : (b = 0);

         } else if(from.b >= from.g && from.b>= from.r){
            (from.b < 255-2*a)? (b = from.b + 2*a) : (b = 255);
            (from.r-a > 0)? (r = from.r - a) : (r = 0);
            (from.g-a > 0)? (g = from.g - a) : (g = 0);
         }
         result.set(i,j,Pixel{r,g,b});
      }
   }
   return result;

}

Image Image::contrast(unsigned char ammount) const{
   Image result(w, h);
   unsigned char a = ammount;
   unsigned char r,g,b = 0;
   for(int i = 0; i < w; i++){
      for(int j = 0; j < h; j++){
         struct Pixel from = get(i,j);
         int sum = from.r + from.g + from.b;
         if(sum>(127*3)){
            (from.r + a < 255)? (r = from.r + a) : (r = 255);
            (from.g + a < 255)? (g = from.g + a) : (g = 255);
            (from.b + a < 255)? (b = from.b + a) : (b = 255);
            
         } else {
            (from.r - a > 0)? (r = from.r - a) : (r = 0);
            (from.g - a > 0)? (g = from.g - a) : (g = 0);
            (from.b - a > 0)? (b = from.b - a) : (b = 0);
         }
         result.set(i,j,Pixel{r,g,b});
      }
   }
   return result;

}


Image Image::redTeal(unsigned char ammount) const{
   Image result(w, h);
   unsigned char a = ammount;
   unsigned char r,g,b = 0;
   for(int i = 0; i < w; i++){
      for(int j = 0; j < h; j++){
         struct Pixel from = get(i,j);
         if(from.r > from.b){
            (from.r + 2*a < 255)? (r = from.r + a) : (r = 255);
            (from.g - a > 0)? (g = from.g - a) : (g = 0);
            b = from.b;
            
         } else {
            (from.r - a > 0)? (r = from.r - a) : (r = 0);
            (from.b + 2*a < 255)? (b = from.b + 2*a) : (b = 255);
            (from.g + a < 255)? (g = from.g + a) : (g = 255);
            // g = from.g; 
         }
         result.set(i,j,Pixel{r,g,b});
      }
   }
   return result;
   
}

Image Image::edgeFinder() const {
   Image ret(w,h);
   ret = grayscale();
   char Gx[9] = {-1,0,1,-2,0,2,-1,0,1};
   // char Gy[9] = {-1,-2,-1,0,0,0,1,2,1};
   struct Pixel same;
   for(int i = 0; i<w; i++){
      for(int j = 0; j<h; j++){
         same = ret.get(i,j);  
         unsigned char red = 0;
         int sum = 0;
         for(int x = i-1, idx = 0; x<i+1; x++, idx++){
            for(int y = j-1, idy = 0; y<j+1; y++, idy++){
               if(x<w && y<h && 0<=x && 0<=y){
                  sum += (Gx[idx*3 + idy])*(get(x,y).r);
                  // sum += (Gy[idx*3 + idy])*(get(x,y).r);
               } else {
                  sum += (Gx[idx*3 + idy])*(same.r);
                  // sum += (Gy[idx*3 + idy])*(same.r);
               }
            }
         }
         if(sum>255){
            red = (unsigned char) 255;
         } else if(sum<0){
            red = (unsigned char) 0;
         } else{
            red = sum;
         }
         // red = sum % 255;
         ret.set(i,j,Pixel{red,red,red});
      }
   }
   return ret;
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
   if(_data == nullptr || other.data() == nullptr){return result;}

   for(int i = 0; i<w*h; i++){
      _data[i].r = _data[i].r*(1-alpha) + other._data[i].r*(alpha);
      _data[i].g = _data[i].g*(1-alpha) + other._data[i].g*(alpha);
      _data[i].b = _data[i].b*(1-alpha) + other._data[i].b*(alpha);
   }

   return result;
}

Image Image::invert() const {
   Image result(w, h);
   for(int i = 0; i < w; i++){
      for(int j = 0; j < h; j++){
         struct Pixel from = get(i,j);
         unsigned char max = 255;
         unsigned char r = max - from.r;
         unsigned char g = max - from.g;
         unsigned char b = max - from.b;
         result.set(i,j,Pixel{r,g,b});
      }
   }
   return result;
}

Image Image::grayscale() const {
   Image result(w, h);
   for(int i = 0; i < w; i++){
      for(int j = 0; j < h; j++){
         struct Pixel rgb = get(i,j);
         unsigned char val = rgb.r*.11 + rgb.g*.59 + rgb.b*.11;
         result.set(i,j,Pixel{val, val, val});

      }
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

