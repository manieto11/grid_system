# Grid System

A small C++ project that builds a `main` executable and uses [raylib](https://www.raylib.com/) for graphics.

## Requirements
- g++ (C++ compiler)
- raylib development package

On Debian/Ubuntu:
```bash
sudo apt update
sudo apt install libraylib-dev build-essential
```

## Build
```bash
make
```
This compiles `grid.cc` to `grid.o` and links `main.cc` + `grid.o` into the `main` binary.

## Run
```bash
./main
```

## Clean
```bash
make clean
```

## Project Structure
- `grid.h` / `grid.cc`: Grid logic implementation
- `main.cc`: Program entry point
- `Makefile`: Build rules for the project
- `LICENSE`: MIT license
- `README.md`: Project overview and usage

## License
MIT — see [LICENSE](LICENSE).
