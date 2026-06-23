<div align="center">

# ⭕ OrbitTask: C Circular Linked List To-Do Manager

[![C](https://img.shields.io/badge/Language-C-%2300599C.svg?style=flat-square&logo=c&logoColor=white)]()
[![Data Structure](https://img.shields.io/badge/Data%20Structure-Circular%20Singly%20Linked%20List-blue?style=flat-square)]()
[![Memory](https://img.shields.io/badge/Memory-Valgrind%20Safe-success?style=flat-square)]()

*A lightweight, zero-dependency CLI Task Manager engineered to demonstrate low-level pointer arithmetic, safe heap management, and O(1) tail-insertion mechanics.*

</div>

---

## 📂 Repository Architecture

```text
.
├── main.c          # App entry point, master execution loop, and CLI menu router
├── tasks.c         # Core business logic, linked-list operations, and File I/O
├── tasks.h         # Struct definitions, enums, and public function prototypes
├── Makefile        # Automation script for clean building, running, and leak testing
└── tasklist.txt    # (Auto-generated) Persistent pipe-delimited session database
```

---

## 🧠 Under the Hood: The Circular Tail Model
Standard singly-linked lists require O(n) traversal to append an item to the end. By maintaining a single pointer to the ```tail```, and mapping ```tail->next``` back to the ```head```, this application achieves **O(1)** insertions at both ends of the list:
```text
         ┌────────────────────────────────────────┐
         ▼                                        │
   ┌───────────┐      ┌───────────┐         ┌─────┴─────┐
   │   Head    │ ───► │  Node 2   │ ───►... │   Tail    │
   │ (Task #1) │      │ (Task #2) │         │ (Task #N) │
   └───────────┘      └───────────┘         └───────────┘
                                                  ▲
TaskManager->tail ────────────────────────────────┘
```

---

## ✨ Key Features
- **O(1) Appending**: Instantly attach new items whether the list has 5 tasks or 50,000.
- **Triage Priority**: Categorize tasks as ```[ ! ] HIGH```, ```[ - ] MEDIUM```, or ```[ v ] LOW```.
- **Date Tracking**: Built-in integer parsing for custom ```DD/MM/YYYY``` deadlines.
- **Safe Memory Lifecycle**: Strict ```malloc```/```strdup``` heap allocation paired with a recursive ```freeList()``` sweep to guarantee zero memory leaks upon exit.
- **Session Persistence**: Automatically dumps your live linked list into a serialized text file on quit, and reconstructs the pointer map on boot.

## 💾 Storage Schema (```tasklist.txt```)
The application serializes memory into a flat text file using standard pipe (|) delimiters.
- Row 1 (Metadata): ```[Total_List_Size]|[Next_Assigned_ID]```
- Row 2+ (Nodes): ```[ID]|[Task_Name]|[Priority_Enum]|[Is_Completed]|[DD]/[MM]/[YYYY]```

Example data payload:
```text
4|5
1|Gaming|2|0|23/6/2026
2|Going on a Run|1|0|30/7/2025
3|Job Searching|3|0|11/3/2025
4|Work|2|1|14/5/2025
```

---

## 🛠️ Compilation & Execution

This project includes a `Makefile` to simplify compilation, execution, and memory testing.

### 1. Build the Project
Compile the source files and generate the executable:
```bash
make
```
### 2. Run the Application
Compile (if changes were made) and launch the task manager immediately:
```bash
make run
```
### 3. Check for Memory Leaks
Run the suite through Valgrind to monitor dynamic heap allocation and ensure freeList() executes safely:
```bash
make valgrind
```
### 4. Clean Build Files
Remove compiled object (.o) files and binary executables to reset your directory:
```bash
make clean
```

---

### 🛠️ How to Install Valgrind
On Ubuntu/Debian Linux:
```bash
sudo apt update
sudo apt install valgrind
```
On macOS (using Homebrew):
```bash
brew install valgrind
```
*(Note for macOS: Valgrind can sometimes be finicky on newer Apple Silicon M1/M2/M3 chips. If it gives you trouble, developers often use ```leaks --atExit -- ./todomanager``` instead).*
