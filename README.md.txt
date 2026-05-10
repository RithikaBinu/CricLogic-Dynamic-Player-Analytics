# CricLogic: Dynamic Player Analytics Tracker

A high-performance command-line application built in **C** to manage and analyze cricket player statistics. This project demonstrates the practical application of **Data Structures and Algorithms (DSA)** by using a custom Singly Linked List to handle real time data dynamically.

## 🚀 Overview
Unlike traditional arrays with fixed sizes, this project leverages **Dynamic Memory Allocation** to manage a fluctuating list of players. It provides an efficient way to track runs, wickets, and performance metrics without the overhead of a full database system.

## 🛠️ Technical Implementation
*   **Data Structure:** Singly Linked List.
*   **Memory Management:** Utilizes `malloc()` and `free()` for efficient heap memory usage.
*   **Algorithms:** 
    *   **Insertion:** $O(1)$ for head insertion or $O(n)$ for sorted rankings.
    *   **Search:** Linear search ($O(n)$) to retrieve player-specific stats.
    *   **Deletion:** Targeted node removal for squad updates.

## ✨ Key Features
- **Dynamic Scoreboard:** Add players on the fly during a match session.
- **Performance Analytics:** Calculate strike rates and averages.
- **Data Persistence:** (Optional: mention if you use file handling like .txt or .csv).
- **Search Functionality:** Quickly find player statistics by their unique ID or name.

## 📂 Project Structure
```text
├── src/
│   ├── main.c          # Entry point and menu logic
│   ├── linked_list.c   # Logic for node manipulation
│   └── player_stats.h  # Structures and function prototypes
├── README.md           # Project documentation
└── .gitignore          # Keeps the repo clean (ignores .exe/bin)