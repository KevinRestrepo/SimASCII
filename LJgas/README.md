# 2D Lennard-Jones gas in a box 

A simple model of a single-species gas in a box with Lennard-Jones Attraction-repulsion and reflective boundary conditions. Right now the only quantitive data it displays is energy and temperature.

The particles are initialized in a uniform disposition and with velocities following the Boltzmann distribution.
## Compiling
Just run `make` in the root directory.
## Usage
Runing `LJgas -h` outputs:
```
Usage: ./LJgas [Params]
Params:
  -h, --help      Show this help message
  -dt <value>     Set the time step (default: 0.01)
  -N <value>      Set the number of particles (default: 30)
  -s <height> <width>  Set the grid size (default: 15x54)
  -T <value>      Set the temperature (default: 300K)
  -m <value>      Set the mass (default: 1)
  -c <value>      Set the cutoff radius (default: 5σ)
  -e <value>      Set the epsilon (default: 0.01eV)
```

The default values are those of Argon, so if you want change the mass, input a ratio of the desired mass to $6.63\times 10^{-26}$ kg.

Changing $\sigma$ is not possible because everything is already in reduced-natural units ($\sigma = \epsilon = m = 1$), in this sense, each ASCII cell measures $1\sigma$. $\sigma$ and the mass values (together with $\epsilon$) define the time scale which is only useful when calculating temporal quantities (time of relaxation, etc), the program doesn't really do any of this right now ($\sigma$ would also become relevant if we had more than one species with different $\sigma$'s). $\epsilon$ is used to display the real physical Energy and transform the temperature from Kelvin to reduced temperature.