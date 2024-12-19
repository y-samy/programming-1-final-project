# Programming 1 Final Project [December 2024]

A basic hotel reservation system made purely in C with the help of standard libraries and our own `libui` non-`ncurses` library for the _user_ input/ output.

## Repo Structure
| Item | Purpose |
|------|---------|
| `src/` | hotel-specific files |
| `include/` | our libraries that can be used in other projects |
| `CMakeLists.txt` | compilation helper with CMake |
| `.devcontainers` | barebones devcontainer for use in GitHub CodeSpaces |

## Project Details

**Instructions & Givens**
- All database files will be given and guaranteed to be valid.

**Technical Details**
- All user input will be validated as it is being typed, and verified after it is entered.

## Contributors
[David Michael](https://github.com/davidyassa)

[Mina Youssef](https://github.com/minawashere)

[Adham Gaweesh](https://github.com/CosmicBreadCat)

[Mohamed Ashraf](https://github.com/mashraf282)

[Youssef Samy](https://github.com/y-samy)


## Code Conventions & Guidelines
This section draws inspiration from The Linux Kernel Coding Style for [v4.10](https://www.kernel.org/doc/html/v4.10/process/coding-style.html#typedefs), [v6.8](https://www.kernel.org/doc/html/v6.8/process/coding-style.html) and the Style Guide for Python Code [PEP-8](https://peps.python.org/pep-0008/).

Aside from a few additions and using 4 spaces for indentation rather than 8, this codebase should mostly be compliant with [The Linux Kernel Coding Style for v6.8](https://www.kernel.org/doc/html/v6.8/process/coding-style.html).

### C Standard
The code generated must be compatible with all C standards starting with **C89/90**, and leave little to no leeway for compiler extensions.

### Encoding of Source Code
As much of the code as possible should be in ASCII, and most of the elements of the code must be in ASCII (identifiers, keywords, etc). Non-ASCII UTF-8 characters are acceptible only if run-time compatibility is taken into account.

### Identifier Naming & Declaration

### Case

| Type | Case |
|------|------|
| macro, const | `UPPER_SNAKE` |
| variable, function, typedefs | `lower_snake` |
| struct, union | `TitleCase` |

#### Structures
**ONLY** `typedef` a `struct` **IF YOU WILL ABSTRACT AWAY ALL ACCESS TO ITS MEMBERS WITH (SETTERS/ GETTERS)-LIKE FUNCTIONS**.
General example: `stdio.h`'s `FILE` and its functions (`fopen()`, `fgets()`, etc)
In-code example: `login.h`'s `user_t` and its functions (`user_session()`, `is_loggedin()`, etc)

#### Type Indication
For identifiers with an ambiguous type, you should add a postfix indicating the type. For example:
- `NEWLINE_C` instead of `NEWLINE` for a macro of type `char`
- `size_t` instead of `size` for a `typedef`
- `int *arr` instead of `int* arr` when declaring pointers
- `*student_name` instead of `*student_name_c` for a string variable pointing to a name; it is self-explanatory

### Indentation
Strictly use the space character instead of the tab character. Your IDE can be configured to insert spaces when the TAB key is pressed.
Use 4 spaces per indendation level.

### Comments
Use the backwards compatible `/* comment */` for in-line comments.
Do not add redundant or obvious comments. Use common sense with placement of in-line comments.
Use self-explanatory identifiers and functions rather than raw constant values.

For multi-line comments, use the following convention:
```c
/*
 * This is a
 * multi-line
 * comment.
 */
```
### Function and Control-flow Bodies

#### Function Braces
Use the style as per the following example
```c

size_t strlen(char *str)
{
    size_t len;
    ...
    return len;
}

```
and NOT
```c

size_t strlen(char *str) {
    size_t len;
    ...
    return len;
}

```

#### Condition & Loop Bodies
Conditions in brackets should be lead by a space after the control-flow keyword, ex. `if (condition)` rather than `if(condition)`.
Single-statement bodies
```c
if (condition)
    statement1;
```
Multi-statement bodies
```c
while (condition) {
    statement1;
    statement2;
}
```
`switch`-`case` statements
```c
switch (expr) {
case a:
    statement1;
    break or return;
```
`if`-`else`
```c
if (condition1) {
    statement1;
} else if (condition2) {
    statement2;
} else {
    statement3;
}
```
`do`-`while`
```c
do {
    statement1;
} while (condition);
```

### Path Name Slashes
Use forward slashes `/` unless compatibility with a supported Windows version requires use of a backward slash `\`.

### Newline Indicator (in source code, not strings)
Optionally prefer `CRLF` (or `\r\n`) for by default, and `LF` (or `\n`) only for strict Unix compatibility situations. Manage newline indicators using `.gitattributes` instead of using your IDE.
