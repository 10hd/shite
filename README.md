# shite

A minimalistic, and shit, text editor written in C.

## About

This is my first project in C and it's genuinely horrible and therefore not intended to be used for real text editing.
I tried writing this README.md using shite and had a hard time.

## Installation

```bash
gcc shite.c -o shite
sudo mv shite /usr/local/bin/
```

## Instructions

To run the editor do:

```bash
shite filename.txt
```

### Commands

The commands are written directly in the editor which is confusing but I guess it works.

* `:\w` + `Enter` — Write to file and quit.
* `:\q` + `Enter` — Quit without writing.
* `:\b` — Delete previous newline when written. Write at start of new line.
* `:\d[number]` — Delete the specified amount of characters when written.
