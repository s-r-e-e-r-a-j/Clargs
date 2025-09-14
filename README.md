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

**Example:**
```c
cl_add_flag(args, 'v', "verbose", "Enable verbose output");
// Use: ./myprog -v
```

2. **String**
```c
int cl_add_string(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int required, const char *def);
```


- **required = 1** → User must provide

- **required = 0** → Optional, `def`(`default`) is used if missing

 **Example:**
```c
cl_add_string(args, 'n', "name", "NAME", "User name", 1, NULL); // Required
cl_add_string(args, 'c', "city", "CITY", "User city", 0, "Unknown"); // Optional
```

3. **Char**
```c
int cl_add_char(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int required, char def);
```

**Example:**
```c
cl_add_char(args, 'g', "gender", "GENDER", "User gender", 0, 'Notprovided'); // Optional
```
- **required = 1** → User must provide

- **required = 0** → Optional,`def` (`default`) is used if missing

4. **Short**
```c
int cl_add_short(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int required, short def);
```
**Example:**
```c
cl_add_short(args, 's', "score", "SCORE", "User score", 0, 10);
```
- **required = 1** → User must provide

- **required = 0** → Optional, `def`(`default`) is used if missing

5. **Int**
```c
int cl_add_int(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int required, int def);
```

**Example:**
```c
cl_add_int(args, 'i', "iterations", "N", "Number of iterations", 0, 100);
cl_add_int(args, 0, "count", "COUNT", "Count of items", 1, 0); // Required
```
- **required = 1** → User must provide

- **required = 0** → Optional, `def`(`default`) is used if missing
