Concentrated Physics
====================

And chemistry?


### Install
I decided to create an experimental development/build/deployment process to learn more about making easy to use C++ code.

#### Fast Install & Run:
```bash
git clone https://github.com/personalcomputer/conphysics.git conphysics && cd conphysics/project && ./get-deps.sh && ./compile.sh && cd .. && ./conphysics
```

#### Full Process:
To set up the dependencies and compile the toy on Ubuntu: run the following while in the root level directory of the repository:
```bash
cd project && ./get-deps.sh && ./compile.sh
```

Not on Ubuntu? Modify get-deps.sh to use your package manager. Not on Linux? Read get-deps.sh and modify it to get the needed packages set up for your development environment.