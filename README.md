# 🕹️ Tic-Tac-Toe Arduino Engine

A robust, state-machine-based implementation of the classic Tic-Tac-Toe game for **ATmega328P** microcontrollers. This project focuses on efficient serial communication, memory management, and input validation.

## 🚀 Key Features
* **Buffer Synchronization:** Implements a manual clearing loop (`while(Serial.available() > 0)`) to prevent data corruption and ghost inputs between turns.
* **Robust Input Parsing:** Uses `Serial.parseInt()` for flexible coordinate entry (supports space, comma, or period separators).
* **Smart State Machine:** Centralized `reset()` logic ensures a clean system state after every game over or draw.
* **Memory Efficiency:** Optimized for low-RAM environments by avoiding heavy `String` objects where possible.

## 🛠️ Technical Stack
* **Language:** C++ (Arduino Framework)
* **Communication:** Serial UART @ 9600 Baud
* **Logic:** 2D Array Matrix for board state management.

## 🕹️ How to Play
1. Upload the `.ino` file to your Arduino.
2. Open the **Serial Monitor** (set it to 9600 Baud).
3. The board will render. Enter your move using `row col` format (e.g., `1 2`).
4. The system will validate if the cell is occupied and check for win/draw conditions automatically.

## 📂 Project Structure
* `tictactoe.ino`: Main logic including the render engine, input parser, and win-condition algorithms.

---
*Developed by **Jesus Perea** — Mechatronics Engineering Student.*
