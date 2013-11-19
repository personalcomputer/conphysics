Concentrated Physics
====================

And chemistry?

### Post-Mortem
This project started after watching problems with traditional 'Falling Sand Game' style cellular automata physics 'simulations', such as [https://github.com/liamzdenek/go-falling-sand]. I wondered if instead of simply having a single state per cell, could we not have multiple types of substances in every cell, represented by a continuous percentage indicating how concentrated that species is in that cell? This then immediately provides a way to simulate pressure within the model: define a density correlated with the concentrations and depending on how much mass is in a cell at any time, assign a pressure for each cell. Cells then derive force from the pressure which is used to calculate dispersion/movement of the mass through the cells and away from high-pressure spots. Combine this with other forces, including gravity, Brownian motion, and 'attraction' to simulate covalent/ionic bonds between mass (and consequently allow the construction of contiguous solids that move together), and we get a fairly detailed physics simulation. Then combine this with pre-modeling the sub-molecular behavior of chemical species, similar to how most falling sand games define rules for when two different substances are next to each other and, we should arrive at an incredibly detailed physics simulation that provides a much more comprehensive simulation than any normal physics engine or chemical process simulator can provide by themselves. And furthermore, it should be fast enough to run in realtime at low resolution. (This is the layman's description; I worked out the underlying statistical chemistry/physics model and may publish it in a more detailed and visual post-mortem later.)

How could one resist trying that? I created an implementation of the most core functionality to create this model, the mass redistribution code based on velocity. This by itself should allow simulating falling sand in a vacuum.

Upon dropping one pixel of the sand near the top of the scene (seen below as the gray dots), the following result is obtained after a few iterations:

![Illustration](http://i.imgur.com/40UUuoh.png "Illustration")

What we see here is artificial 'dispersion' in the falling sand. Awesome, that's what it should look like, right?! One problem there - I never wrote the dispersion code. What you're seeing is incurred entirely by the quantization error.

I could figure out no modification to the core principals of the idea that would fix this error without radically altering how the approximation works, and I thus declare the test to have concluded and that I was unable to recreate physics using a few simple approximations. Nobody was surprised, but it was an interesting statistical modeling experiment.

### Install
I decided to create an experimental development/build/deployment process to learn more about making easy to use C++ code.

#### Fast Install & Run:
```bash
sudo apt-get install git build-essential wget python xorg-dev libglu1-mesa-dev libarmadillo-dev &&
git clone https://github.com/personalcomputer/conphysics.git conphysics && cd conphysics/project && ./get-extra-deps-crossplatform.sh && ./compile.sh && cd .. && ./conphysics
```

(Modify first line as appropriate for non-Ubuntu/Debian)