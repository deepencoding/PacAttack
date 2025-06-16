# 🎮 PacAttack

**Stack**: C++ • SFML

---

## 🚀 Project Overview

PacAttack is a modern take on the classic Pac-Man arcade experience, built in C++ using SFML. Featuring advanced Ghost AI behaviors, intelligent pathfinding, dynamic audio cues, precise collision detection, and an adaptive scoring & level progression system, PacAttack aims to deliver both nostalgia and fresh gameplay twists that increase replay value and player engagement.

---

## 🎯 Key Features

- **Unique Ghost AI Behaviors**  
  Each ghost has its own decision-making logic and dynamic state changes (chase, scatter, frightened, adaptive), making the maze challenge more engaging and less predictable.

- **Intelligent Pathfinding Algorithms**  
  Efficient pathfinding (e.g., A* or BFS with heuristics) ensures ghosts navigate the maze effectively, adapting routes based on player position, level, and game state.

- **Dynamic Audio Cues**  
  Contextual sound effects and music transitions (e.g., escalating tension as player collects more points, alert cues when ghosts switch behaviors) enhance immersion and feedback.

- **Precise Collision Detection**  
  Robust collision logic calibrates hitboxes for the player (Paccy), ghosts, pellets, power-ups, and walls, ensuring smooth interactions and minimizing glitches.

- **Progressive Scoring & Level Progression**  
  An adaptive difficulty system scales Ghost AI aggressiveness and speed based on player performance, unlocking new levels or tweaks (e.g., faster ghost speed, smarter chase patterns) to maintain challenge and retention.

- **Cross-Platform Build**  
  Tested on Windows and Linux. Uses C++17 threading and memory management to keep the rendering loop responsive and thread-safe.

---

## 📁 File Structure

The repository is organized into logical modules for readability and maintainability. Example structure:

```

PacAttack/
├── assets/
│   ├── images/                # Maze layouts, sprites, UI elements
│   ├── audio/                 # Sound effects and music tracks
│   └── levels/                # Level definitions (map data, enemy configs)
├── src/
│   ├── main.cpp               # Entry point
│   ├── Paccy.cpp/.hpp         # Player character implementation
│   ├── Ghosts.cpp/.hpp        # Ghost class definitions & behaviors
│   ├── GhostManager.cpp/.hpp  # Ghost AI manager, state transitions
│   ├── MapCollision.cpp/.hpp  # Maze collision logic
│   ├── DrawMap.cpp/.hpp       # Rendering maze layout
│   ├── DrawText.cpp/.hpp      # UI text rendering (score, lives, etc.)
│   ├── ConvertSketch.cpp/.hpp # (Optional) Tools to convert sketchmaps to tilemaps
│   ├── Chronometer.hpp        # Timing utilities (frame timing, AI timers)
│   ├── AudioManager.cpp/.hpp  # Loading & playing audio cues
│   ├── LevelManager.cpp/.hpp  # Handles level loading, progression logic
│   ├── ScoreManager.cpp/.hpp  # Tracks scoring, combos, power-up effects
│   └── global.hpp             # Global constants, enums, configuration
├── images-github/             # Screenshots for README/GitHub display
│   ├── FileStructure.png
│   ├── start\_screen.png
│   ├── gameplay\_1.png
│   └── gameplay\_2.png
├── Build/                     # (Generated) build outputs
├── CMakeLists.txt             # Build configuration
└── README.md                  # This file

````

> **Note**: Adjust paths or filenames if your repository layout differs.

---

## 🎬 Screenshots

### Start Screen
![](https://media.githubusercontent.com/media/deepencoding/PacAttack/dev/images-github/start_screen.png)

### Gameplay Examples
![](https://media.githubusercontent.com/media/deepencoding/PacAttack/dev/images-github/gameplay_1.png)  
![](https://media.githubusercontent.com/media/deepencoding/PacAttack/main/images-github/gameplay_2.png)

---

## 🛠️ Getting Started

### Prerequisites

- A C++17 (or newer) compiler (e.g., g++, clang++, MSVC).
- [SFML](https://www.sfml-dev.org/) (if building from source; note: the project may include static linking of SFML for easier distribution).
- CMake (minimum version 3.10+ recommended).

### Clone the Repository

```bash
git clone https://github.com/deepencoding/PacAttack.git
cd PacAttack
````

### Build & Compile

1. **Create a build directory**

   ```bash
   mkdir build
   cd build
   ```
2. **Run CMake configuration**

   ```bash
   cmake ..
   ```

   * If SFML is installed system-wide, CMake will find it.
   * If using custom SFML location, set `SFML_DIR` or appropriate CMake variables:

     ```bash
     cmake -DSFML_DIR=/path/to/SFML/lib/cmake/SFML ..
     ```
3. **Build the project**

   ```bash
   cmake --build .
   ```

   This produces the executable (e.g., `PacAttack` or `PacAttack.exe`).

### Run the Game

From the `build` directory:

```bash
./PacAttack
```

* The game window should open with the start screen.
* Control Paccy through the maze, collect pellets, avoid or chase ghosts when powered up.

---

## 🎮 Controls

* **Arrow Keys / WASD**: Move Paccy (up/down/left/right).
* **P**: Pause / Resume game.
* **M**: Toggle mute audio.
* **ESC / Q**: Quit to desktop.

*(Adjust controls in code or config if different.)*

---

## ⚙️ Configuration & Tuning

* **Maze Layouts & Levels**:

  * Level definitions can be stored as text/map files under `assets/levels/`. Modify tile representations or add new level files to expand gameplay.
  * Ghost speed, scatter/chase durations, power-up timings can be tweaked in `global.hpp` or a dedicated config struct.

* **Ghost AI Parameters**:

  * Tweak pathfinding heuristics (e.g., weight factors) in `GhostManager`.
  * Adjust state transition thresholds (e.g., when ghosts switch from chase to scatter) based on level or score.

* **Audio Settings**:

  * Audio files are in `assets/audio/`. Replace or add cues for new events (e.g., level-up jingle, extra life sound).
  * Volume levels and transition logic live in `AudioManager`.

* **Rendering & Performance**:

  * Frame rate cap and timing logic in `Chronometer.hpp`.
  * Sprite sheets or textures can be updated in `assets/images/`; ensure collision boxes align with new visuals.

---

## 🔍 AI & Gameplay Details

### Ghost AI Behaviors

* **State Machine**: Each ghost cycles through states (Scatter, Chase, Frightened, Eaten). Transitions depend on timers, player actions (e.g., eating power pellet), and adaptive difficulty.
* **Adaptive Difficulty**: Monitor player performance (e.g., pellet collection rate, lives remaining). If player excels, increase ghost speed or reduce scatter time to raise challenge; if struggling, ease parameters.
* **Pathfinding**:

  * Implement A\* (or BFS with heuristics) on the maze graph: nodes represent tile centers, edges represent valid moves.
  * Heuristics may include Manhattan distance or more advanced cost functions factoring in dynamic obstacles.
* **Dynamic Audio Integration**:

  * When ghosts enter certain AI states (e.g., near-catch, frightened ending), trigger distinct audio cues for player feedback.
  * Background music tempo may shift subtly as player nears completion of level or power-up expiration.

### Collision Detection

* **Tile-Based vs. Pixel-Based**:

  * Use tile grid for coarse collision detection (walls vs. entities).
  * Use bounding boxes/circles for finer collisions (e.g., Paccy vs. ghost when closeness threshold met).
* **Smooth Movement**:

  * When turning corners, allow buffered inputs so player doesn’t feel “stuck” on grid intersections.
  * Ghosts use similar buffering for path recalculation.

### Scoring & Progression

* **Pellet & Power-Up Scoring**: Each pellet adds to score; power pellets trigger frightened mode and bonus scoring when eating ghosts.
* **Combo Tracking**: Track consecutive ghost-eatings within a single power-up for exponential score multipliers.
* **Level Advancement**: After clearing all pellets, transition to next maze layout. Increase difficulty by adjusting ghost speed, AI aggressiveness, or introducing new map elements.
* **High Scores**: Optionally store high scores locally or via simple file I/O. (Extendable to online leaderboards.)

---

## 📦 Distribution & Releases

* **Prebuilt Binaries**:
  Check the [Releases page](https://github.com/deepencoding/PacAttack/releases) to download precompiled binaries (e.g., `PacAttack-binaries-v1.0.0.zip`). Unzip and run the executable directly—no SFML install needed if statically linked.
* **Building from Source**:
  Follow the **Getting Started** section above. Ensure SFML dependency is satisfied.

---

## 🧩 Extending PacAttack

* **New Ghost Types**: Add classes with custom behaviors (e.g., ambusher, ambivalent ghost).
* **Power-Ups & Items**: Introduce new power-ups (speed boost, temporary shield) and handle their integration in AI and scoring.
* **Multiplayer Mode**: Experiment with local co-op or networked play (requires networking layer and sync logic).
* **Theming & Graphics**: Swap sprite sets or add animations (e.g., animated mouth, ghost sprites), adjust UI overlays.
* **Analytics & Metrics**: Log gameplay stats to fine-tune difficulty curves or for player feedback dashboards.

---

## 🤝 Contributing

1. Fork the repository.
2. Create a branch: `git checkout -b feature/awesome-ghost-ai`.
3. Commit changes with clear messages.
4. Open a Pull Request against `main`.
5. Ensure code compiles on supported platforms; add/update tests or demo scenes if applicable.
6. Follow the existing style and architecture patterns.

We welcome improvements in AI, new levels, art assets, audio design, performance optimizations, and more!

---

## 🧾 License

This project is released under the **MIT License**. See [LICENSE](./LICENSE) for details.

---

## 🙋‍♂️ Author

**@deepencoding** – Passionate about game development, AI behaviors, and delivering smooth, engaging gameplay experiences. Feel free to open issues or discuss feature ideas!
