# Line Count Analyzer

A recursive file scanner written in C that walks through a directory, counts total lines of code by file type, and prints a sorted summary of the results.

## Features
- Recursively scans all subdirectories
- Prints summary sorted by line count (descending)
- Counts total lines per file extension (e.g., `.c`, `.h`, `.py`)
- Skips common binary file extensions (`.o`, `.so`, `.exe`, etc.)
- Supports `--exclude=<dir1,dir2,...>` to skip specific directories or file types
- Shows percentage breakdown per file type
- `--help` flag for usage info
- Clean modular C project structure
- Simple Makefile for easy compilation

## Usage
```bash
make  # compile the project
./linecount <directory> [--exclude=dir1,dir2]
```

### Help Command
```bash
./linecount --help
```
Outputs usage instructions.

### Exclude Directories
```bash
./linecount . --exclude=.git,node_modules
```
Skips the `.git` and `node_modules` directories during scanning.

## Output Example
```
--- Line Count Summary ---
.c: 1200 lines (57.1%)
.h: 800 lines (38.1%)
.py: 100 lines (4.8%)
Total: 2100 lines
```

## Compilation
Use the provided Makefile:
```bash
make
```
This will build an executable called `linecount`.

## Notes
- Only regular, non-binary files are counted (excludes by extension)
- Hidden files/folders can be skipped using `--exclude`
