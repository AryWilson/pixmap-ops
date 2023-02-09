// Copyright 2021, Aline Normoyle, alinen

#include <iostream>
#include "image.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{

   Image image;
   if (!image.load("../images/feep.png")) {
      std::cout << "ERROR: Cannot load image! Exiting...\n";
      exit(0);
   }

   for (int i = 0; i < image.height(); i++) {
      for (int j = 0; j < image.width(); j++) {
         Pixel c = image.get(i, j);
         std::cout << "(" << (int)c.r << "," << (int)c.g << "," << (int)c.b << ") ";
      }
      std::cout << std::endl;
   }
   image.save("feep-test-save.png"); // should match original
   

   // should print 4 4
   cout << "loaded feep: " << image.width() << " " << image.height() << endl;

   // test: copy constructor
   Image copy = image; 
   copy.save("feep-test-copy.png"); // should match original and load into gimp

   // test: assignment operator
   copy = image; 
   copy.save("feep-test-assignment.png"); // should match original and load into gimp

   // should print r,g,b
   Pixel pixel = image.get(1, 1);
   cout << (int) pixel.r << " " << (int) pixel.g << " " << (int) pixel.b << endl;

   // test: setting a color
   pixel.r = 255;
   image.set(1, 1, pixel);
   image.save("feep-test-newcolor.png");


   // test a non-trivial image
   if (!image.load("../images/earth.png")) {
      std::cout << "ERROR: Cannot load image! Exiting...\n";
      exit(0);
   }

   // should print 400 400
   cout << "loaded earth: " << image.width() << " " << image.height() << endl;
   

   // resize
   Image resize = image.resize(200,300);
   resize.save("earth-200-300.png");
   resize = image.resize(800,600);
   resize.save("earth-800-600.png"); 
   resize = image.resize(700,700);
   resize.save("earth-700-700.png"); 


   // alpha blend
   Image soup;
   soup.load("../images/soup.png");
   // grayscale
   Image grayscaleSoup = soup.grayscale(); 
   grayscaleSoup.save("soup-grayscale.png");

   int y = (int) (0.5f * (image.width() - soup.width()));
   int x = (int) (0.5f * (image.height() - soup.height()));
   Image background = image.subimage(x, y, soup.width(), soup.height());
   background.save("background-test.png"); 
   Image blend = background.alphaBlend(soup, 0.5f);
   blend.save("earth-blend-0.5.png"); // valgrind error

   image.replace(blend, x, y);
   image.save("earth-blend-0.5.png"); // valgrind error



   // sub image
   Image sub = image.subimage(200, 200, 100, 100);
   sub.save("earth-subimage.png");

   // grayscale
   Image grayscale = image.grayscale(); 
   grayscale.save("earth-grayscale.png");

   // flip horizontal
   Image flip = image.flipHorizontal(); 
   flip.save("earth-flip.png");  

   // gamma correction
   Image gamma = image.gammaCorrect(0.6f); 
   gamma.save("earth-gamma-0.6.png"); 

   gamma = image.gammaCorrect(2.2f);
   gamma.save("earth-gamma-2.2.png"); 

   // part 2 tests

   // swirl colors
   Image swirl = image.swirl();
   swirl.save("swirl.png");

   // invert colors
   Image invert = image.invert();
   invert.save("invert.png");

   // monochrome
   Image red = image.monochrome(0);
   red.save("red.png");
   Image green = image.monochrome(1);
   green.save("green.png");
   Image blue = image.monochrome(2);
   blue.save("blue.png");
   Image yellow = image.monochrome(3);
   yellow.save("yellow.png");
   Image purple = image.monochrome(4);
   purple.save("purple.png");
   Image teal = image.monochrome(5);
   teal.save("teal.png");
   Image gray = image.monochrome(9);
   gray.save("grey.png");

   // saturate
   Image bright = image.saturate(20);
   bright.save("bright.png");

   //binary
   Image binary = image.saturate(255);
   binary.save("binary.png");

   // contrast
   Image contrast = image.contrast(10);
   contrast.save("contrast-10.png");
   Image contrast2 = image.contrast(30);
   contrast2.save("contrast-30.png");

   // red-teal filter
   Image instaFilter = image.redTeal(20);
   instaFilter.save("filter-20.png");


   if (!image.load("../images/bricks.png")) {
      std::cout << "ERROR: Cannot load image! Exiting...\n";
      exit(0);
   }

   // box blur
   Image blur = image.blur();
   blur.save("blur.png");
   // sobel edge detection
   Image sobel = blur.edgeFinder();
   sobel.save("sobel-blur.png");
   sobel = image.edgeFinder();
   sobel.save("sobel.png");
}

