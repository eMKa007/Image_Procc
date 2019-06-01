# Image Processing. 

## Project summary:
* Read selected image file and save processing result.
* Usage of additional libaries is forbiden. (Except: read file, memory allocation, display image, save file)
* It is allowed to use a ready-made FFT implementation in version 1D.

### Available transformations:
<b>Point and geometric transformations (RGB and mono images):</b> 
* Automatic tresholding using max entropy function.

***

<b>Spatial filtration (RGB and mono images): </b> 
* Kirsch filtration.
  * Edge symmetrical reflection.
  * (For RGB files, every channel separately)

___

<b>Morphological transformation (mono and logic images): </b>
* Erosion with linear element*.
* Dilation with linear element*.
* Opening/Closing with linear element*.

*The structural element is the line with the specified length and inclination.

___

<b>Logical transformation (onlu logic images): </b>
* Convex Hull.

___

## Application Usage:
![alt text][usage]
![alt text][usage1]

[usage]: https://raw.githubusercontent.com/eMKa007/Image_Procc/master/Projekt_MK/TestImages/usage.png "Program Usage."
[usage1]: https://raw.githubusercontent.com/eMKa007/Image_Procc/master/Projekt_MK/TestImages/usage1.png "Transformation pick."

### TODO: 
  * Convert pointers to smart ones.
  * GUI
