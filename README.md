# Giovanni Andreella, 2023/2024
# Boid assignement
To successfully execute this project please complete the following steps:
1. Modify the __n__ value of the `Flock(n)` constructor in file `main.cpp` to simulate a group of n boids (line 21).
2. Save any modified file.
3. In your terminal, go to the directory where the project is saved with `cd` command. 
4. Write the command `g++ -Wall -o main main.cpp boid.cpp flock.cpp` to compile it.
5. Execute the `main.exe` file with the command `./main`.
6. Start the python visualizer with the command `python3 Visualizer.py `.

The maximum number of boids is set to 300 to avoid a long execution time.
In order to simulate more boids, please modify the global constant __MAX_BOIDS__ in file `globals.h`.

The project provides three examples of this code working, respectively with 1, 100 and 300 boids.
Pictures and coordinates file of the experiments are provided too.
