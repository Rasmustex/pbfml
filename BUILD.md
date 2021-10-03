# Building pbfml
## Prerequisites
### Installing git 
To build pbf, you first need the source code. You can get it by cloning this repo using `git`. This does require you to have git, which isn't installed by default on all linux distributions. You can get it from your distribution's repository:
#### Debian/Ubuntu
```
# apt install git
```
#### Fedora
```
# dnf install git
```
#### Arch
```
# pacman -S git
```
### Cloning the github repo
Now, you can clone the pbfml repository and `cd` into it:
```sh
$ git clone https://github.com/Rasmustex/pbfml.git
$ cd pbfml
```
### Installing build dependencies
You will need `clang` to compile pbfml, although you can also use gcc if you change the `CC` variable in the makefile. You will also need `make` to use the makefile to build the project. Both packages will be available in your distribution repositories:
#### Debian/Ubuntu
```
# apt install clang make
```
#### Fedora
```
# dnf install clang make
```
#### Arch
```
# pacman -S clang make
```
## Building
To build pbfml once you are in the `pbfml` directory, run the command:
```
$ make release
```
The binary will be in `bin/pbf`
## Installation
You can install pbf to `~/.local/bin` with the command:
```
$ make install
```
Make sure that `~/.local/bin` is part of your `PATH`. You can install to other directories by changing the `INSTALLDIR` variable in the makefile.

You should now be able to invoke pbfml with the `pbfml` command.
