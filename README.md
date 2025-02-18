# EPITECH-Rush-3

**{ EPITECH } - B-PDG-300_rush3 - Note : 24.6**

## 📝 Administrative Details (2 / 2)

## 🚫 Bad Practices (0 / 0)
- `run` calls `run` when switching from graphical mode

## 🏷️ Namespace (0.5 / 0.5)

## 🖥️ Display Interface (1.5 / 1.5)

## 🧩 Module Interface (1.5 / 1.5)

## 🔍 Reflection (2 / 2.5)
- Missing STL list for graphical modules, close to perfection

## ⚙️ Configuration (2 / 2)
- Perfect, nothing to say

## 📌 Implemented Modules
- **Hostname & Username Module** (1 / 1)
- **OS Name & Kernel Version Module** (1 / 1)
- **Date & Time Module** (1.5 / 1.5)
- **nCurses Display** (1.5 / 1.5)
- **CPU Module** (1.5 / 1.5)
- **RAM Module** (1.5 / 1.5)
- **SFML Display** (2 / 2)

## 🎁 Bonus (5 / 10)
- ✅ Scrolling management for modules (+3.5)
- ✅ Fully adaptable architecture (+1.5)

## 🐸 Kreeeeeeog! (0.1 / 0.1)
- Very good scream, even when high

---

# 🚀 MyGKrellm

## 🔍 Overview
**MyGKrellm** is a system monitor inspired by **GKrellM**, developed in **C++** without `using namespace`, `*alloc`, `free`, `*printf`, `open`, or `fopen`. It provides real-time monitoring of system resources in both **graphical (SFML)** and **text-based (nCurses)** modes.

## ✨ Features
- **Modular Architecture**: Dynamically add, remove, and reorder modules.
- **Two Display Modes**:
  - **nCurses Mode**: Displays system info in the terminal.
  - **SFML Mode**: Provides a graphical system monitoring experience.
- **Configurability**:
  - **Beginner**: Configure modules & display modes at **compile time**.
  - **Intermediate**: Configure settings via **command-line arguments**.
  - **Advanced**: Switch modules and displays dynamically **at runtime**.

## 🏗️ Core Functionality
### **Step 1: Monitor Core**
- Manages **modules** & **display modes** dynamically via interfaces:
  - `Krell::IModule` (Module behavior)
  - `Krell::IDisplay` (Display mode behavior)

### **Step 2: Modules & nCurses**
- Implements the following system info modules:
  - ✅ Hostname & Username
  - ✅ OS Name & Kernel Version
  - ✅ Date & Time

### **Step 3: More Modules & SFML**
- Additional modules:
  - ✅ **CPU** (Model, Frequency, Cores, Usage)
  - ✅ **RAM** (Usage Statistics)
- Implements **SFML graphical display**

## 🎉 Bonus Features
- **Extra Modules**: Network Load, Battery, More system stats.
- **Additional Graphical Displays**: Graphs, GTK, SDL2, Qt5, Unreal Engine 5.3.

## 🔧 Build & Execution
- **Build System**: `Makefile` (`all`, `clean`, `fclean`, `re` rules).
- **Executable**: `MyGKrellm`

## 🎯 Goals
- ✅ Maintain a **clean & efficient modular design**.
- ✅ Ensure **smooth user experience** across both display modes.
- ✅ Provide **flexibility & extensibility** with dynamic module handling.
