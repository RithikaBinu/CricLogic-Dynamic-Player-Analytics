# CricLogic: Dynamic Player Analytics Tracker

A high-performance command-line application built in **C** to manage and analyze cricket player statistics. This project demonstrates the practical application of **Data Structures and Algorithms (DSA)** by using a custom Singly Linked List to handle real time data dynamically.

## 🚀 Overview
Unlike traditional arrays with fixed sizes, this project leverages **Dynamic Memory Allocation** to manage a fluctuating list of players. It provides an efficient way to track runs, wickets, and performance metrics without the overhead of a full database system.

<img width="864" height="453" alt="Screenshot 2026-02-24 193449" src="https://github.com/user-attachments/assets/ff02c2b6-43d0-4821-b86f-b9b06014e298" />

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

## 🎮 Application Demo
<img width="762" height="458" alt="Screenshot 2026-02-24 193401" src="https://github.com/user-attachments/assets/11aa87d4-7be4-46a2-91d1-3a0cc2143003" />

<img width="864" height="453" alt="Screenshot 2026-02-24 193449" src="https://github.com/user-attachments/assets/d00dd178-9f1d-4fba-b610-fb7bec59c38d" />

<img width="876" height="965" alt="Screenshot 2026-02-24 193533" src="https://github.com/user-attachments/assets/8a404a11-725d-4393-bda9-f01d49a3ec33" />

<img width="863" height="811" alt="Screenshot 2026-02-24 193556" src="https://github.com/user-attachments/assets/c3844aa6-8f18-4bec-9d44-b3bfbcfa13a1" />

<img width="639" height="394" alt="Screenshot 2026-02-24 193823" src="https://github.com/user-attachments/assets/66442c24-9db8-4802-890c-9220f17d09f9" />

## 📂 Project Structure
```text
├── src/
│   ├── main.c          # Entry point and menu logic
│   ├── linked_list.c   # Logic for node manipulation
│   └── player_stats.h  # Structures and function prototypes
├── README.md           # Project documentation
└── .gitignore          # Keeps the repo clean (ignores .exe/bin)
