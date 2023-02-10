# pixmap-ops

Image manipulation demos based on the PPM image format.

TODO: Add a representative image for your project here

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake -G "Visual Studio 17 2022" ..
pixmap-ops/build $ start pixmap-ops.sln
```

Your solution file should contain two projects: `pixmap_art` and `pixmap_test`.
To run from the git bash command shell, 

```
pixmap-ops/build $ ../bin/Debug/pixmap_test
pixmap-ops/build $ ../bin/Debug/pixmap_art
```

*macOS*

Open terminal to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake ..
pixmap-ops/build $ make
```

To run each program from build, you would type

```
pixmap-ops/build $ ../bin/pixmap_test
pixmap-ops/build $ ../bin/pixmap_art
```

## Image operators
The origenal example image.
![Alt text](/images/earth.png?raw=true)
You can resize and image with the function resize() that takes the new dimentions in pixels.
![Alt text](/images/earth-200-300.png?raw=true)
You can perform gamma correction using the function gammeCorection() that takes the gamma value as an input.
![Alt text](/images/earth-gamma-0.6.png?raw=true)
![Alt text](/images/earth-gamma-2.2.png?raw=true)
You can make an image black and white using the greyscale() function.
![Alt text](/images/earth-grayscale.png?raw=true)
You can get a portion of the image using subimage() that takes the starting and ending x and y values, in pixels.
![Alt text](/images/earth-subimage.png?raw=true)
You can increase the color contrast in an image using the function vibrancy() that takes the ammount you want to increase the vibracy in the range of [0,255].
![Alt text](/images/bright.png?raw=true)
You can increase the value contrast of an image using the function contrast() that takes the ammount you want to increase the vibracy in the range of [0,255].
![Alt text](/images/buildcontrast-30.png?raw=true)
you can blend two images together with the function alphaBlend() that takes the second image and the fractional ammount of the input image.
![Alt text](/images/earth-blend-0.5.png?raw=true)
You can flip an image using flipHorizontal().
![Alt text](/images/earth-flip.png?raw=true)
You can invert the colors of an images using invert().
![Alt text](/images/invert.png?raw=true)
You can make an image monochrome in any of 6 primary and secondary colors using monochrome() that takes an integer flag as an input. 
![Alt text](/images/purple.png?raw=true)
![Alt text](/images/yellow.png?raw=true)
![Alt text](/images/green.png?raw=true)
You can change the colors of an image using swirl().
![Alt text](/images/swirl.png?raw=true)
there is a red-teal filter you can get using redTeal().
![Alt text](/images/filter-20?raw=true)

A second default image to demonstrate blur and edge detection().
![Alt text](/images/bricks.png?raw=true)
You can perform a box blur using blur().
![Alt text](/images/blur?raw=true)
You can perform a sobel edge detection using edgeDetection().
![Alt text](/images/sobel-blur?raw=true)


## Results
Example artwork.
![Alt text](/images/binary?raw=true)
![Alt text](/images/bird?raw=true)
![Alt text](/images/cat?raw=true)
![Alt text](/images/sobel1?raw=true)
![Alt text](/images/sobe21?raw=true)
![Alt text](/images/lines?raw=true)

