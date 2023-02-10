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

![Alt text](/images/earth.png?raw=true)
resize
![Alt text](/build/earth-200-300.png?raw=true)
gamma correction
![Alt text](/build/earth-gamma-0.6.png?raw=true)
greyscale
![Alt text](/build/earth-grayscale.png?raw=true)
subimage
![Alt text](/earth-subimage.png?raw=true)
increase vibrancy
![Alt text](/build/bright.png?raw=true)
increase contrast
![Alt text](/buildcontrast-30.png?raw=true)
blend two images
![Alt text](/build/earth-blend-0.5.png?raw=true)
flip an image
![Alt text](/build/earth-flip.png?raw=true)
invert and images colors
![Alt text](/build/invert.png?raw=true)
make the image monochrome
![Alt text](/build/purple.png?raw=true)
swirl an image's colors
![Alt text](/build/swirl.png?raw=true)
red-teal filter
![Alt text](/build/filter-20?raw=true)

![Alt text](/images/bricks.png?raw=true)
box blur
![Alt text](/build/blur?raw=true)
sobel edge detection
![Alt text](/build/sobel-blur?raw=true)


## Results
![Alt text](/build/binary?raw=true)
![Alt text](/build/bird?raw=true)
![Alt text](/build/cat?raw=true)
![Alt text](/build/sobel1?raw=true)
![Alt text](/build/sobe21?raw=true)
![Alt text](/build/lines?raw=true)

