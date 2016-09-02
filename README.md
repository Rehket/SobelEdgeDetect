# SobelEdgeDetect
Adam, UCF Robot Vsion
My Sobel Edge Detection project for Robot Vision. Sobel Code modified from the code available on http://www.cs.ucf.edu/courses/cap4453/

The edge detection works however, currently the image is scaled down and tiled horizontally. I am unsure as to what is causing this. 

The PGM class is unused at the moment.

The program can be compiled using vs 2015 c++ compiler and requires 4 command arguments. The first is the input file name followed by the 
output file name which is inturn followed by the thresholds. The thresholds should be between 0 and 255.


SobelEdgeDetect.exe in.io out.io 20 145
