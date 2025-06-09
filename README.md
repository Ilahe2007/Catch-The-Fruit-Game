# Catch the Fruit Game 🧺

A terminal-based fruit-catching game made in C using the `ncursesw` library. Move the basket to catch the correct falling fruit while avoiding bombs!

---

## Requirements

Make sure you have the following installed on your system:

- GCC compiler
- `libncursesw` library (for wide-character support, including emojis)
-Make sure your terminal supports UTF-8 to see the emojis properly.

### Install on Debian/Ubuntu:

sudo apt update
sudo apt install build-essential libncursesw5-dev

# Game Rules
- Catch the correct fruit shown on the screen to earn points.

- If you don't catch the correct fruit you lose a life.

- Catching the wrong fruit loses a life.

- Catching a bomb 💣 removes 2 lives.

- You have 3 lives in total.

- Catching a heart ❤️ restores 1 life.

- The game ends when you lose all your lives.

# Controls🎮
  In Menu:
  
  ↑ ↓ – Navigate through options
  
  Space – Select an option
  
  In Game:
  
  ←  → – Move the basket
