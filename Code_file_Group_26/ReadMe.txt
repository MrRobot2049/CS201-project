CS201 Project

Team Members :
J.V.Praneeth - 2023csb1296
Puchakayala Rohith - 2023mcb1312
Goutham Naroju - 2023mcb1295

Mentoring TA - Abdul Razique

Project Title: Music audio and DNA file compression using palindrome trees


       -------------------------- Follow these steps to ensure proper code execution ----------------------


1) How to install make.h:(compulsory)
   -   sudo apt install make (Windows / Ubuntu)
   -   brew install make (mac OS)

2) How to install mp3.h:(compulsory)
   -   sudo apt-get install libmpg123-dev (Windows / Ubuntu)
   -   brew install mpg123 (mac OS)

3) How to install Gnuplot(compulsory)
   -   sudo apt install gnuplot (Windows / Ubuntu)
   -   brew install gnuplot (mac OS)


4) How to Convert music files to .txt:
   -   gcc Audio_text_converter.c -o Audio_text_converter -lmpg123 -lm (compile)
   -   ./Audio_text_converter (to run)
 
5) To run on DNA testcases:
   -   make
   -   ./main1;./main2;./main3
   
(each main file consists of one test case, test cases were put on separate files as the code is getting dumped as there are many file handlings with the files that are not created at the time of compiling)


(step 4 should be done before it, you should also run step 5 before this as the folder should contain files till Compressed_file_3, after that remaining 3 files get created)

6) To run on Music Audio files 
   -   make
   -   ./main4;./main5;./main6

7) To plot graph for palindromic strings vs time taken:
   -   gcc palindromic_graph.c -o palindromic_graph  (compile)
   -   ./palindromic_graph  (run)

8) To plot graph for non_palindromic strings vs time taken:
   -   gcc non_palindromic_graph.c -o non_palindromic_graph  (compile)
   -   ./non_palindromic_graph  (run)
   
9) To delete the executables after successful working of Test cases:
   -   rm -f *.o main1 main2 main3 main4 main5 main6 palindromic_graph non_palindromic_graph Audio_text_converter
 
 
What to Take as Input:

   -   Input files should be named as 'testcasei.txt' for the ith test case.
   -   For mp3 files, the music file should be in 16-bit format for the code to run accurately.

What to Expect as Output:

   -   The output depends on the input:
   -   For mp3 input, the output includes text converted from the music file, as well as the compressed and decompressed files.
   -   For text input, the output includes the compressed text file and its decompressed version.
    A graph representing palindromic and non-palindromic strings will be generated from random insertions in the Palindromic Tree.

       --------------------------- Important Instructions ----------------------------


   *   To run the main functions again, make sure you delete all compressed_file_x(1 - 6) ,  Decompressed_file_x(1 - 6), Music_Note_x(1 - 3).
   *   If you want to give any manual input, delete files mentioned above, replace then with testcasex.txt files and then run all 6 files at a time so that no error occurs in file handling.
   *   code works better for 16 bit audio or lower bit audio, as Audio to Text converter file we have decodes into 16 bit.
   *   we downloaded some extra test case files and placed in extra_testcases folder, you can replace it with teastcaseX.mp3, and run following above steps 





