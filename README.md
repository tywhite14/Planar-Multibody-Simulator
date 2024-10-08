# Planar-Multibody-Simulator

Make rigid-bodies go *brrrrrrrr*

Very much a work in progress.
The vision is to have an application that simulates 2D rigid-body physics using real-time constraint solving and numerical integration.
The user will be able to set up a scenario by specifying the physical properties of various bodies (mass, length, size, etc) and the joints between the bodies (revolute joint, translational joint, rigid joint).

The only external library will be SFML for graphics rendering. Math and physics will all be handled in-house.

## Workflow
Currently, I do all development on the `dev` branch and once it reaches a stable milestone of progress, I then merge `dev` into `main`.

## Build Instructions

### Windows
Use Visual Studio 2019 or newer. Open the .sln file. Build for Release or Debug.

### Linux
Navigate to the top-level of the project directory. Run the bash script `./scripts/buildPMS.sh`

## Roadmap

### Version 1.0
- finish fleshing out the framework for the application
- Get it to a state where it seems to be working properly
- set up GUI so the user can see the simulation

### Version 2.0
- add more options (more joints, more body types, more customization), play/pause feature
- let user define a scenario purely from the application UI. i.e., drag-and-drop bodies and hotkeys for making joints
- let user save and load scenarios
- implement some sort of real-time plotting functionality (e.g., plot lateral force on a body over time)
- data logging function (maybe support exporting directly to .mat format for MATLAB post-processing)

### Nice to have
- optimization
- unit tests
- debugging tools (profiler)

Currently, it does none of these things!
