# PacAttack - A Pacman Clone

PacAttack is an exciting clone game inspired by the classic arcade game Pacman. Players embark on a thrilling maze adventure, guiding their character through a challenging labyrinth while avoiding ghosts and collecting points. With captivating gameplay reminiscent of the original Pacman, offering a nostalgic experience for players of all ages. It is a Pacman clone developed in C++ using the SFML library. The project aims to recreate the classic Pacman experience.

## File Structure

The project follows a specific file structure for organization:

![](https://media.githubusercontent.com/media/deepencoding/PacAttack/dev/images-github/FileStructure.png)

## Source Files

- **ConvertSketch.cpp**: Implementation for converting sketches.
- **DrawMap.cpp**: Manages the drawing of the game map.
- **DrawText.cpp**: Handles the drawing of text elements.
- **GhostManager.cpp**: Manages the behavior and movement of ghosts.
- **Ghosts.cpp**: Implements the ghost characters in the game.
- **MapCollision.cpp**: Manages collisions with the game map.
- **Paccy.cpp**: Implements the main character, Paccy.
- **main.cpp**: Main entry point for the program.

## Header Files

- **Chronometer.hpp**: Header file for handling time-related functionality.
- **ConvertSketch.hpp**: Header file for sketch conversion.
- **DrawMap.hpp**: Header file for map drawing functions.
- **DrawText.hpp**: Header file for text drawing functions.
- **GhostManager.hpp**: Header file for ghost management.
- **Ghosts.hpp**: Header file for ghost character implementation.
- **MapCollision.hpp**: Header file for map collision handling.
- **Paccy.hpp**: Header file for the main character, Paccy.
- **global.hpp**: Header file for global constants and variables.

## Getting Started

### Start Screen
![](https://media.githubusercontent.com/media/deepencoding/PacAttack/dev/images-github/start_screen.png)

### Gameplay Captures
![](https://media.githubusercontent.com/media/deepencoding/PacAttack/dev/images-github/gameplay_1.png)

![](https://media.githubusercontent.com/media/deepencoding/PacAttack/dev/images-github/gameplay_2_2.png)

### To play the game
Go to the releases page [here](https://github.com/deepencoding/PacAttack/releases/tag/v1.0.0) and download the `PacAttack-binaries-v1.0.0.zip` file and unzip it.\
OR\
[download](https://github.com/deepencoding/PacAttack/releases/download/v1.0.0/PacAttack-binaries-v1.0.0.zip) the binaries directly and unzip it.

### To build and compile the PacAttack game, follow these steps:

1. Clone the repository: `git clone https://github.com/deepencoding/PacAttack.git`
2. Open the `PacAttack.sln` file in Visual Studio and compile the program in their.
3. The `.exe` binaries will be located in `$(SolutionDir)Build\$(Platform)\$(Configuration)\bin` folder.
4. Run the `PacAttack.exe` file to play the game. 

## Dependencies

This is made using SFML but the the project is statically linked, so you don't have to download the library just to play the game.
