# Mini-Game Compilation

A collection of three classic mini-games — **Snake**, **Doodle Jump**, and **Tetris** — built in C++ using the SFML library. Players choose a game from the main menu and their high scores are saved automatically.

The primary purpose of this project is to practice and improve C++ programming skills and gain hands-on experience with SFML (Simple and Fast Multimedia Library).

---

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Installation & How to Build](#installation--how-to-build)
- [How to Play](#how-to-play)
- [Screenshots](#screenshots)

---

## Features

- Main menu with background music and navigation
- Three playable mini-games: Snake, Doodle Jump, and Tetris
- Persistent high score tracking (saved to `.txt` files)
- Sound effects and background music for each game
- Pause functionality in Snake and Tetris

---

## Requirements

- **C++ compiler** supporting C++11 or later (e.g., MSVC, GCC, Clang)
- **SFML 2.x** — [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php)
- **Visual Studio** (project files included: `.sln` / `.vcxproj`)

---

## Installation & How to Build

1. **Install SFML 2.x** and make sure it is linked to your build environment.
2. **Clone or download** this repository.
3. Open `Game set.sln` in **Visual Studio**.
4. Ensure the SFML include and library paths are set correctly in the project properties.
5. **Build** the solution (Build → Build Solution, or `Ctrl+Shift+B`).
6. Run the resulting executable from the project's root directory so that all asset folders (`Snakegame/`, `Doodlejumpgame/`, `Tetrisgame/`) and resource files are found correctly.

---

## How to Play

### Main Menu

| Key | Action |
|-----|--------|
| ↑ / ↓ Arrow | Navigate menu items |
| Enter | Select |
| Escape | Exit |

### Snake

| Key | Action |
|-----|--------|
| Arrow Keys | Change direction |
| Space | Pause / Resume |
| Escape | Quit to menu |

### Doodle Jump

| Key | Action |
|-----|--------|
| ← / → Arrow | Move left / right |
| Escape | Quit to menu |

The character jumps automatically when landing on a platform. Survive as long as possible and beat your high score!

### Tetris

| Key | Action |
|-----|--------|
| ← / → Arrow | Move piece left / right |
| ↓ Arrow | Move piece down faster |
| ↑ Arrow | Rotate piece |
| Space | Pause / Resume |
| Escape | Quit to menu |

Clear lines to score points. The game speeds up as your score increases!

---

## Screenshots

**Game selection interface**

<img width="598" height="628" alt="2" src="https://github.com/user-attachments/assets/bbbbb549-7c26-46f8-a133-2613cec2ea1a" />

**Snake gameplay**

<img width="478" height="350" alt="4" src="https://github.com/user-attachments/assets/0088203f-e3aa-4237-a80c-f2b3ab297449" />

**Doodle Jump gameplay**

<img width="399" height="560" alt="3" src="https://github.com/user-attachments/assets/c382d994-fd0b-4380-8327-874278bfdad8" />

**Tetris gameplay**

<img width="603" height="831" alt="螢幕擷取畫面 2024-01-12 173822" src="https://github.com/user-attachments/assets/f7896f03-f93e-4643-9481-2e394b70f97f" />

---

> **Note:** This project is for educational and non-commercial use only.


