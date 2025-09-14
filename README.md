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

## Header File Placement

- **Recommended**: Place `clargs.h` in the **same directory** as your `.c` source file.
```c
#include "clargs.h"
```

- This works on **Linux, Windows, and macOS** without any extra setup.

- For larger projects, you can place it in a dedicated `include/` folder and adjust the include path, but for most users, keeping it in the same directory is **easiest and safest**.

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
> **Note:** If you don’t need either the **short name** or the **long name**, you can pass `0`.
> 
> Example:  
> ```c
> // Only long name
> cl_add_int(args, 0, "count", "COUNT", "Number of items", 0, 5);
>
> // Only short name
> cl_add_flag(args, 'v', 0, "Enable verbose mode");
> ```
> meta is the place-holder name shown in usage (e.g., --name NAME).

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

---

2. **String**
```c
int cl_add_string(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, const char *def);
```


- **req(required) = 1** → User must provide

- **req(required) = 0** → Optional, `def`(`default`) is used if missing

 **Example:**
```c
cl_add_string(args, 'n', "name", "NAME", "User name", 1, NULL); // Required
cl_add_string(args, 'c', "city", "CITY", "User city", 0, "Unknown"); // Optional
```

---

3. **Char**
```c
int cl_add_char(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, char def);
```

**Example:**
```c
cl_add_char(args, 'g', "gender", "GENDER", "User gender", 0, 'U'); // Optional
```
- **req(required) = 1** → User must provide

- **req(required) = 0** → Optional,`def` (`default`) is used if missing

---

4. **Short**
```c
int cl_add_short(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, short def);
```
**Example:**
```c
cl_add_short(args, 's', "score", "SCORE", "User score", 0, 10);
```
- **req(required) = 1** → User must provide

- **req(required) = 0** → Optional, `def`(`default`) is used if missing

---

5. **Int**
```c
int cl_add_int(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, int def);
```

**Example:**
```c
cl_add_int(args, 'i', "iterations", "N", "Number of iterations", 0, 100);
cl_add_int(args, 0, "count", "COUNT", "Count of items", 1, 0); // Required
```
- **req(required) = 1** → User must provide

- **req(required) = 0** → Optional, `def`(`default`) is used if missing

---

6. **Long**
```c
int cl_add_long(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, long def);
```

**Example:**
```c
cl_add_long(args, 0, "timeout", "TIMEOUT", "Timeout in ms", 0, 5000);
```

- **req(required) = 1** → User must provide

- **req(required) = 0** → Optional, `def`(`default`) is used if missing

---

7. **Long long**
```c
int cl_add_llong(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, long long def);
```

**Example:**
```c
cl_add_llong(args, 0, "bigval", "BIGVAL", "Large integer value", 0, 1234567890123LL);
```
- **req(required) = 1** → User must provide

- **req(required) = 0** → Optional, `def`(`default`) is used if missing

---

8. **Size_t**
```c
int cl_add_size(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, size_t def);
```
**Example:**
```c
cl_add_size(args, 0, "bufsize", "SIZE", "Buffer size", 0, 1024);
```
- **req(required) = 1** → User must provide

- **req(required) = 0** → Optional, `def`(`default`) is used if missing

---

9. **Float**
```c
int cl_add_float(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, float def);
```

**Example:**
```c
cl_add_float(args, 0, "ratio", "RATIO", "Scaling ratio", 0, 1.5f);
```
- **req(required) = 1** → User must provide

- **req(required) = 0** → Optional, `def`(`default`) is used if missing

---

10. **Double**
```c
int cl_add_double(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, double def);
```
**Example:**
```c
cl_add_double(args, 0, "pi", "PI", "Approximate pi value", 0, 3.14159);
```
- **req(required) = 1** → User must provide

- **req(required) = 0** → Optional, `def`(`default`) is used if missing

---

11. **Unsigned Char**
```c
int cl_add_uchar(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, unsigned char def);
```

**Example:**
```c
cl_add_uchar(args, 'u', "usergender", "UCHAR", "User gender code", 0, 1);
```

- **req(required) = 1** → User must provide

- **req(required) = 0** → Optional, `def`(`default`) is used if missing

 ---

12. **Unsigned Short**
```c
int cl_add_ushort(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, unsigned short def);
```

**Example:**
```c
cl_add_ushort(args, 0, "portnum", "PORT", "Port number", 0, 8080);
```

- **req(required) = 1** → User must provide

- **req(required) = 0** → Optional, `def`(`default`) is used if missing

---

13. **Unsigned Int**
```c
int cl_add_uint(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, unsigned int def);
```

**Example:**
```c
cl_add_uint(args, 's', "buffersize", "SIZE", "Buffer size", 0, 1024);
```

- **req(required) = 1** → User must provide

- **req(required) = 0** → Optional, `def`(`default`) is used if missing

---

14. **Unsigned Long**
```c
int cl_add_ulong(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, unsigned long def);
```

**Example:**
```c
cl_add_ulong(args, 0, "maxbytes", "MAXBYTES", "Maximum bytes allowed", 0, 500000UL);
```

- **req(required) = 1** → User must provide

- **req(required) = 0** → Optional, `def`(`default`) is used if missing

---

15. **Unsigned Long Long**
```c
int cl_add_ullong(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, unsigned long long def);
```

**Example:**
```c
cl_add_ullong(args, 0, "hugeval", "HUGEVAL", "Very large integer value", 0, 123456789012345ULL);
```

- **req(required) = 1** → User must provide

- **req(required) = 0** → Optional, `def`(`default`) is used if missing

---

16. **Positional Arguments**
```c
int cl_add_pos(Clargs *p, const char *name, const char *help, int req);
```

**Example:**
```c
cl_add_pos(args, "input", "Input filename", 1);  // Required positional argument
cl_add_pos(args, "output", "Output filename", 0); // Optional positional
```
- **req(required) = 1** → User must provide

- **req(required) = 0** → Optional

---

## Parsing Arguments
```c
int cl_parse(Clargs *p, int argc, char **argv);
```

- Parses `argc/argv`.

- Returns `0` on success, `-1` on error.

- Automatically checks required arguments.

**Example:**
```c
if (cl_parse(args, argc, argv) != 0) {
    fprintf(stderr, "Error parsing arguments\n");
    return 1;
}
```

---

## Accessing Argument Values

All getters optionally provide a pointer to `ok` to check if value exists.
```c
int ok;
const char *name = cl_get_string(args, "name");
int iter = cl_get_int(args, "iterations", &ok);
if(ok) printf("Iterations = %d\n", iter);
```

| Function          | Returns               | Example                                  |
|-------------------|-----------------------|------------------------------------------|
| cl_get_flag       | int (0/1)             | cl_get_flag(args, "verbose");            |
| cl_get_string     | const char *          | cl_get_string(args, "name");             |
| cl_get_char       | char                  | cl_get_char(args, "gender", &ok);        |
| cl_get_short      | short                 | cl_get_short(args, "score", &ok);        |
| cl_get_int        | int                   | cl_get_int(args, "count", &ok);          |
| cl_get_long       | long                  | cl_get_long(args, "timeout", &ok);       |
| cl_get_llong      | long long             | cl_get_llong(args, "bigval", &ok);       |
| cl_get_uchar      | unsigned char         | cl_get_uchar(args, "level", &ok);        |
| cl_get_ushort     | unsigned short        | cl_get_ushort(args, "port", &ok);        |
| cl_get_uint       | unsigned int          | cl_get_uint(args, "size", &ok);          |
| cl_get_ulong      | unsigned long         | cl_get_ulong(args, "maxval", &ok);       |
| cl_get_ullong     | unsigned long long    | cl_get_ullong(args, "hugeval", &ok);     |
| cl_get_size       | size_t                | cl_get_size(args, "bufsize", &ok);       |
| cl_get_float      | float                 | cl_get_float(args, "ratio", &ok);        |
| cl_get_double     | double                | cl_get_double(args, "pi", &ok);          |


---

## Help Message
```c
void cl_help(Clargs *p);
```

- Automatically prints usage and description.

- Includes all arguments, defaults, and required info.

**Example:**
```c
cl_help(args);
```

---

## Freeing Resources
```c
void cl_free(Clargs *p);
```

- Frees memory used by parser.

**Example:**
```c
cl_free(args);
```

## Example program
```c
/*
  Example program using clargs.h
  --------------------------------
  - Shows how to add every argument type
  - Shows how to get values back
  - Uses &ok to check if argument is registered
  - Remember: use 1 for required, 0 for optional
  - You can pass 0 for short_name or long_name if you don't need them
*/

#include <stdio.h>
#include "clargs.h"

int main(int argc, char **argv) {
    int ok;

    // Create parser
    Clargs *args = cl_create("example", "Demo of all clargs functions");

    // Add different argument types
    cl_add_flag(args, 'v', "verbose", "Enable verbose mode");                 // flag
    cl_add_string(args, 'n', "name", "NAME", "User name", 0, "guest");        // string
    cl_add_char(args, 0, "gender", "GENDER", "Gender (M/F)", 0, 'U');         // char
    cl_add_short(args, 's', "score", "SCORE", "Short number", 0, 10);         // short
    cl_add_int(args, 'p', "port", "PORT", "Port number", 0, 8080);            // int
    cl_add_long(args, 0, "timeout", "TIMEOUT", "Timeout in ms", 0, 5000L);    // long
    cl_add_llong(args, 0, "bigval", "BIGVAL", "Big 64-bit number", 0, 123456789LL); // long long
    cl_add_uchar(args, 0, "ubyte", "UBYTE", "Unsigned char", 0, 255);         // unsigned char
    cl_add_ushort(args, 0, "u16", "U16", "Unsigned short", 0, 65000);         // unsigned short
    cl_add_uint(args, 0, "u32", "U32", "Unsigned int", 0, 123456789u);        // unsigned int
    cl_add_ulong(args, 0, "ulong", "ULONG", "Unsigned long", 0, 1234567890UL);// unsigned long
    cl_add_ullong(args, 0, "ull", "ULLONG", "Unsigned long long", 0, 1234567890123ULL); // unsigned long long
    cl_add_size(args, 0, "bufsize", "SIZE", "Buffer size", 0, 4096);          // size_t
    cl_add_float(args, 0, "ratio", "RATIO", "Float value", 0, 0.75f);         // float
    cl_add_double(args, 0, "threshold", "THRESH", "Double value", 0, 0.123);  // double
    cl_add_pos(args, "input", "Input file", 1);                               // positional (required)

    // Parse command-line
    if (cl_parse(args, argc, argv) != 0) {
        cl_free(args);
        return 1;
    }

    // Get values back
    printf("verbose   : %d\n", cl_get_flag(args, "verbose"));
    printf("name      : %s\n", cl_get_string(args, "name"));

    char gender = cl_get_char(args, "gender", &ok);
    if (ok) printf("gender    : %c\n", gender);

    short score = cl_get_short(args, "score", &ok);
    if (ok) printf("score     : %d\n", score);

    int port = cl_get_int(args, "port", &ok);
    if (ok) printf("port      : %d\n", port);

    long timeout = cl_get_long(args, "timeout", &ok);
    if (ok) printf("timeout   : %ld\n", timeout);

    long long bigval = cl_get_llong(args, "bigval", &ok);
    if (ok) printf("bigval    : %lld\n", bigval);

    unsigned char ubyte = cl_get_uchar(args, "ubyte", &ok);
    if (ok) printf("ubyte     : %u\n", ubyte);

    unsigned short u16 = cl_get_ushort(args, "u16", &ok);
    if (ok) printf("u16       : %u\n", u16);

    unsigned int u32 = cl_get_uint(args, "u32", &ok);
    if (ok) printf("u32       : %u\n", u32);

    unsigned long ul = cl_get_ulong(args, "ulong", &ok);
    if (ok) printf("ulong     : %lu\n", ul);

    unsigned long long ull = cl_get_ullong(args, "ull", &ok);
    if (ok) printf("ull       : %llu\n", ull);

    size_t bufsize = cl_get_size(args, "bufsize", &ok);
    if (ok) printf("bufsize   : %zu\n", bufsize);

    float ratio = cl_get_float(args, "ratio", &ok);
    if (ok) printf("ratio     : %f\n", ratio);

    double thresh = cl_get_double(args, "threshold", &ok);
    if (ok) printf("threshold : %f\n", thresh);

    printf("input     : %s\n", cl_get_string(args, "input"));

    // Free parser
    cl_free(args);
    return 0;
}

```
