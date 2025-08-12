🗒️ Build-A-Block
A console-based Tetris-like game written in C for Windows.
It features user login/register, score saving, leaderboards, block shadow preview, and classic Tetris gameplay mechanics.

🧠 Features
1. Account System
- Register with username and password.
- Login to continue your progress.
- 
2. Leaderboard
- Saves highest score per player in playerscore.txt.
- Sorted by score and name.
- 
3. Classic Tetris Gameplay
- Move, rotate, and hard drop blocks.
- Block shadow preview to help with placement.
- Level, score, and next piece display.

👷‍♂️ In-Game Controls
| Key       | Action                       |
| --------- | ---------------------------- |
| A         | Move left                    |
| D         | Move right                   |
| S         | Move down                    |
| W         | Rotate block                 |
| E         | Swap block with next block   |
| Space     | Hard drop block              |
| P         | Pause game                   |

📄 File Structure
- main.c → Source code for the game.
- playerscore.txt → Stores player names, passwords, and scores in the format: "username#password#score" with enter in the end

⚙️ How to Run
1. Compile: gcc -o Build-A-Block main.c -Wall
2. Run: Build-A-Block.exe
3. Make sure playerscore.txt exists in the same directory (create an empty file if needed).

⚒️ Dependencies
- Windows OS (uses <windows.h>, <conio.h>).
- ANSI escape sequences for colored output (works in modern Windows terminals).

✍️ Author: Johannes Aaron Framon

📒 Notes
- Max board size: 19 rows × 15 columns.
- Game automatically ends if a new block cannot spawn (collides with other block)
- Scores update only if your current game score is higher than your previous best.
- Even though this game is basically tetris, the main gameplay doesn't has the ability to make the blocks fall automically. This feature will be included soon on the next Build-A-Block version.
