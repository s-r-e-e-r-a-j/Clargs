## CLARGS – Command-Line Argument Parsing Library for C

CLARGS is a lightweight, flexible, and powerful C programming language library for parsing command-line arguments. It supports a wide variety of argument types, including flags, strings, characters, integers, floats, doubles, and more. It is designed to make building command-line tools in C easier, safer, and more robust.

## Features

- **Supports multiple argument types**
  - Boolean flags (`-f`, `--flag`)
  - Strings (`char *`)
  - Character (`char`)
  - Short, Int, Long, Long Long (`short`, `int`, `long`, `long long`)
  - Unsigned variants (`unsigned char`, `unsigned short`, `unsigned int`, `unsigned long`, `unsigned long long`)
  - Size (`size_t`)
  - Floating-point (`float`, `double`)
  - Positional arguments

- **Default values** for all argument types
- **Required and optional arguments** support
- **Automatic help message generation** (`-h` / `--help`)
- **Short and long options** (`-x` and `--example`)
- **Easy retrieval** of parsed values through getter functions
- **Lightweight and portable** — no external dependencies
- **Dynamic argument array growth** for flexible usage


## Creating Argument Parser

```c
Clargs *cl_create(const char *prog, const char *desc);
```
- **prog**: Program name (e.g., `"myprogram"`).
- **desc**: Description of the program (`shown in help`).

- Returns a pointer to a `Clargs` parser object.

**Example:**
```c
Clargs *args = cl_create("myprog", "This is a sample parser");
```
## Adding Arguments
1. **Flag (boolean)**
```c
int cl_add_flag(Clargs *p, char short_name, const char *long_name, const char *help);
```

- **short_name**: `-f`

- **long_name**: `--flag`

- **help**: Description

- Required: Flags are **optional** (presence = 1, absence = 0)
