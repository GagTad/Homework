# Simple grep-like Tool (C++)

This project is a simple grep-like command-line tool written in C++. It allows you to search for text patterns (using regular expressions) in files, directories, or standard input.

## Features

- Search for regex patterns in text files
- Highlight all matches in red (ANSI color)
- Count matching lines with `--count`
- Recursive search in subdirectories with `-r`
- Case-insensitive search with `-i`
- Works with files, directories, or standard input

## Usage

1. **Compile (on Windows):**
    ```
    g++ -std=c++17 -o grep grep.cpp
    ```

2. **Examples**

    - Search for "error" in `file.txt`:
      ```
      grep error file.txt
      ```
    - Search for "error" recursively in a folder:
      ```
      grep -r error myfolder
      ```
    - Show only the count of matching lines:
      ```
      grep --count error file.txt
      ```
    - Case-insensitive search:
      ```
      grep -i error file.txt
      ```
    - Use with standard input:
      ```
      type file.txt | grep error
      ```

## Flags

- `-r` — search recursively in subdirectories
- `-i` — ignore case
- `--count` — show only the number of matching lines

## Example

```
grep -r -i --count test myfolder
```

