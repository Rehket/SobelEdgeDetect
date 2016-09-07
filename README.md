# SobelEdgeDetect
Adam Albright, UCF Robot Vsion

My Edge Detection project for Robot Vision. Sobel Code modified from the code available on http://www.cs.ucf.edu/courses/cap4453/

The program can be compiled using VS2015 c++ compiler and requires 4 command arguments to run the compiled program. The first is the input file name followed by the output file name which is inturn followed by the thresholds. The thresholds should be between 0 and 255.

Each threshold value entered will generate an additional image. The thresholds needs to be arranged in decending order as indicated below.

SobelEdgeDetect.exe garb34 out.io 200 150 40 20 
