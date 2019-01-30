# data-structures: C++ Template Classes

[Note!] 
Looking back on this code, it's really bad. E.g.
* Comments are way too accessive!
* Structs should NOT be outside the data structure class definition -- what if you import multiple structures? And why should you even be able to access the nodes? The original reason I did this was to make testing easier but it's a bad idea... (maybe use a friend test class?)
* Some functions are strange -- why would you want to insert at an index in a linked list? 
Etc, etc

I wish I had time to fix all of this code and completely rewrite everything, but there's a lot of other stuff I want to work on and school is busy. So for now, I'll leave this up. 


This is a collection of data structures created in C++ using templates. 
The finished collection includes:

* Linked-List
* Stack
* Queue
* Binary Search Tree
* Heap
* Hash Table

Each class contains considerable documentation, explaining many algorithms, their purpose, and their efficiencies; the library's main function is to provide reference to students who want to thoroughly explore data structures commonly found in computer science courses. 

## Documentation

Using each class is simple. Each folder contains a .cpp file, and a .h file. Running the .cpp file will showcase the features of the class, (as well as test it) and the class is contained in the .h file. 

Use whichever compiler you'd like, but if you'd like to simplify the process you can use this: 

`g++ -Wall -Wextra -pedantic -ggdb3 -std=c++14 file.cpp -o file.exe` 
`./file.exe` and replace _file_ with the corresponding file name. 
