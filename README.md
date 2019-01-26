# JetPack Funride using OpenGL

This is a game similar to the Jetpack Joyride where in the player has a jetpack and has to move up and down and dodge enemies while collecting coins in the way. The standard game consists of the following:
  - Dodge firelines and firebeams
  - Collect coins and powerups
  - Try to reach the maximum score by covering maximum distance and collecting maximum coins on the way

# New Features!

  - The player can also move left and right
  - Player has water balloons which he/she can use to extinguish firelines and firebeams but only on the cost of reduces score
  - New enemies like the Viserion, which follows the player and throws ice, and the Boomerang have been added
  - Shields and Health Pickups
  - Magnets which will attract the player towards itself and hamper its movement
  - Ring Bridge which is allow the player to slide along it to avoid enemies

# Installation

Jetpack Funride requires C++ and OpenGl to run.
The following development packages of the following libraries should be installed:
 - GLEW
 - GLFW3
 - GLM

Installation instructions
### For Fedora
```
$ sudo pkgconf-pkg-config dnf install glew-devel glfw-devel glm-devel cmake pkgconf 
```
### For Ubuntu
```
$ sudo apt install libglew-dev libglfw3-dev libglm-dev cmake pkg-config
```
(Use apt-get if you don’t have aptitude installed but I suggest installing it)
### For Mac
Install homebrew
```
brew install glew glfw glm cmake pkg-config
```
### For Other distros
Use the equivalent of apt search or dnf search and make sure you install the devel packages
### Driver Issues
If you do face driver issues, try to update your drivers. If you continue facing issues even after installing, I suggest you update your operating system to the latest stable release. You can also try building the libraries, but it would be a waste of time IMO.

# How to Run

To run, clone the directory, make sure all the required packages are installed, then type the following commands, inside the cloned directory.

```sh
$ cd build
$ ./graphics_asgn1
```
If you want to make some edits then make sure to run the following commands to compile the changes:
```
$ cd build
$ make all
```

License
-------
The MIT License https://mayankmusaddi.mit-license.org/

Copyright &copy; 2019 Mayank Musaddi <mayank.musaddi@research.iiit.ac.in>
