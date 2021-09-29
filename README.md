# PNS
PNS, abbreviation for Physics-Related Numerical Simulations, is a set of numberical exercises to compute various simulations regarding physical systems, such as Ising models, Genetic Algorithms and more.

Most simulations have already been executed and the results saved in the Jupyter Notebook, however, they have been developed such that it is possible to re-run them. The notebooks generally do not contain heavy computations with a few exceptions. For this purpose, it is recommended not to run the simulations or the notebooks unless necessary. In fact, it is possible to encounter system-dependent problems that may cause the simulation to fail or produce wrong results.

## Motivation
The package has been developed in order to solve various exercises handed out during the master's degree course "Laboratorio di Simulazione Numerica", held by professor D. Galli, for the university "Università degli Studi di Milano".

## Structure
All exercises share the following libraries found in the parent directory:
- **functions.hpp**: header containing general user-defined functions used in most exercises.
- **ini_reader.hpp**: header containing the tools to parse .ini files, used as settings files in the package.
- **datablocking.hpp**: header containing the datablocking methods for each exercises, divided using namespaces.
- **logger.hpp**: header file containing a logger class to write formatted outputs to console.

Each exercise consists of:
- Library (.hpp) files with tools to run the simulation (e.g. random.hpp, metropolis.hpp, genetic.hpp, etc..)
- main.cpp file to run the simulation
- config.ini file which holds the configurational parameters for the execution of the simulation
- "outputs/" directory where outputs (e.g. data, graphs, images) are stored
- A Jupyter Notebook with an analysis and discussion of the results
- Makefile to compile the C++ source code

## Status
![GitHub last commit](https://img.shields.io/github/last-commit/lorycontixd/PNS?style=plastic)
![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/lorycontixd/PNS?include_prereleases&style=plastic)
![GitHub repo size](https://img.shields.io/github/repo-size/lorycontixd/PNS?style=plastic)

## Dependancies
The package depends on the following C++ non-built-in libraries:
- [Armadillo](http://arma.sourceforge.net/download.html)
- [Sqlite3](https://www.sqlite.org/index.html)
- [MPICH](https://www.mpich.org/)

The Python dependancies are specified in the "requirements.txt" file and can be downloaded using the command
```bash
pip install -r requirements.txt
```

## Installation

To install the package you can
#### Clone the repository
1. Create and enter the folder where you want the package to be installed in
2. Initialize an empty repository
```bash
git init
```
3. Clone the repository
```bash
git clone https://github.com/lorycontixd/PNS.git
```
#### Download the latest release


## Comments
- Exercise4 and Exercise7 have incorrect graphs. However, I thought it was best to try to give a reasoning for why the results were not accurate and what my predictions were

## License
[MIT](https://choosealicense.com/licenses/mit/)