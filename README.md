# GameOfLife
OpenMP Implementation


* modify the deploy/legion.py file to contain your username and build environment 
* run the following commands from the terminal:

  * $ fab legion.cold - which will connect you to the cluster, clone the git repository of the project, build it and run the tests
  * $ fab legion.sub - which will submit a job to the queue to run the code (the default number of threads is 12)
  * $ fab legion.fetch - which will download the results once the job is finished
  
* change the path in the visualization/visualize.py script to point to your results/legion.rc.ucl.ac.uk/output.txt folder of the project
* go into the folder 'visualization' and run $ python visualize.py
