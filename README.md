# ECM2433-The-C-Family

Developer
-----------
Jack Shaw- https://github.com/js1294

Description
-----------
This is a simulation of a set of temporary traffic lights. This is being done to establish how it operates under different traffic conditions
and traffic light timings. 

Requirements
-----------
This is written in ANSI standard C. 
This requires the GNU Scientific Library. Further details can be found here: https://www.gnu.org/software/gsl/doc/html/

Running the Project
-----------
To be able to run the project you must first compile and link the programs.
This can be done by executing the compileSim shell or using these commands:

gcc -ansi -c queue.c -I./ -o queue.o

gcc -ansi -c runSimulations.c -I./ -o runSimulations.o

gcc queue.o runSimulations.o -lgsl -lgslcblas -o runSimulations

Once the it has been compiled you can run the executable runSimulations, by running .\runSimulations on linux.
