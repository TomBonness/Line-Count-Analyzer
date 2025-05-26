# 📊 Line Count Analyzer

A recursive file scanner written in C that tallies lines of code by file extension. Built for speed and simplicity using low-level I/O and directory traversal via `dirent.h`.

---

## 🔧 Features

- Walks directories recursively
- Handles symlinks, hidden files, and nested folders
- Tallies total lines per filetype (`.c`, `.h`, `.py`, etc.)
- Outputs a ranked list of extensions by total lines

---

## 📦 Build Instructions

```bash
make
```

Or compile manually:

```bash
gcc -Iinclude src/main.c -o linecount
```

---

## 🚀 Usage

```bash
./linecount /path/to/codebase
```

Example:

```bash
./linecount ~/projects/my-cool-app
```

---

## 🧠 Learning Focus

- Recursive directory traversal with `dirent.h`
- File reading with `fopen`, `fgets`
- Hashmap-like behavior using arrays + file extension matching
- Modular C project layout with headers + Makefiles

---

