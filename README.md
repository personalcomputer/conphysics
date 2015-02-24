Concentrated Physics
====================

And chemistry?

### Post-Mortem
This project started after watching problems with traditional 'Falling Sand Game' style cellular automata physics simulations, such as [https://github.com/liamzdenek/go-falling-sand]. I wondered if instead of simply having a single state per cell, could you not have multiple types of substances in every cell with variable concentration in each cell. This also leads to a way to simulate pressure within the model: define a density correlated with the concentrations and depending on how much mass is in a cell at any time, assign a pressure for each cell. Cells then derive force from the pressure which is used to calculate dispersion/movement of the mass through the cells and away from high-pressure spots. Combine this with other forces including gravity, Brownian motion, and attraction to simulate chemical bonds between mass (and consequently allow the construction of contiguous solids that move together?), and you might get a fairly detailed physics simulation. Then combine this with pre-modeling the sub-molecular behavior of chemical species, identical to how most falling sand games define reaction rules for when two different substances are next to each other, and it should provide a detailed physics simulation that provides a more comprehensive simulation than any normal realtime physics engine or chemical process simulator can provide by themselves (although with high approximation error). (I also worked out an underlying statistical chemistry/physics model that indicated to me my understanding of the situation was correct, this was pretty neat and may lead to later development.)

I created an implementation of the most core functionality to create this model, the mass redistribution code based on velocity. This by itself should have allowed simulating falling sand in a vacuum.

Upon dropping one pixel of the sand near the top of the scene (seen below as the gray color), the implementation generates this result after a few iterations:

![Illustration](http://i.imgur.com/40UUuoh.png "Illustration")

What is visible appears to be dispersion in the falling sand. Awesome, that's what it should look like, right? One problem there - I never wrote the dispersion code. What you're seeing is incurred entirely by the quantization error.

I could not figure out any modification to the core principals of the idea that would fix this error without radically altering how the approximation works, so accordingly the test is concluded and I was unable to recreate physics using a few simple approximations - not a surprise. Still an interesting statistical modeling experiment for me and something I will revist.

### Install
#### Fast Install & Run:
```bash
sudo apt-get install git build-essential wget python xorg-dev libglu1-mesa-dev libarmadillo-dev &&
git clone https://github.com/personalcomputer/conphysics.git conphysics && cd conphysics/project && ./get-extra-deps-crossplatform.sh && ./compile.sh && cd .. && ./conphysics
```
(Modify first line as appropriate for non-Ubuntu/Debian)
