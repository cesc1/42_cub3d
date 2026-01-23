# cub3D

## Description

**cub3D** is a 3D graphics project that creates a dynamic view inside a maze using raycasting techniques, inspired by the legendary game Wolfenstein 3D. This project serves as an introduction to 3D computer graphics, mathematical concepts, and game development fundamentals.

The program reads a map description file (`.cub` format) containing texture paths, colors, and a 2D map layout, then renders a real-time 3D first-person view of the maze. Players can navigate through the maze using keyboard controls with smooth movement and rotation.

### Key Features:
- **Raycasting engine** for real-time 3D rendering
- **Texture mapping** with XPM format support
- **Keyboard controls** for movement (WASD) and rotation (arrow keys)
- **Map parsing** with comprehensive error handling
- **Wall collision detection**
- **Configurable floor and ceiling colors**
- **Clean memory management** and leak-free execution
### Map File Format
Create a `.cub` file with the following structure:
```
NO ./path/to/north_texture.xpm
SO ./path/to/south_texture.xpm
WE ./path/to/west_texture.xpm
EA ./path/to/east_texture.xpm

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

**Map Components:**
- **NO/SO/WE/EA**: Texture paths for North, South, West, East walls
- **F**: Floor color in RGB format (R,G,B)
- **C**: Ceiling color in RGB format (R,G,B)
- **1**: Wall
- **0**: Empty space
- **N/S/E/W**: Player starting position and direction

### Execution
```bash
# Run with a map file
./cub3D path/to/your_map.cub
```
```bash
# Example with provided test map
./cub3D data/map_test_general.cub
```

### Controls
- **W, A, S, D**: Move forward, left, backward, right
- **Left/Right Arrow Keys**: Rotate camera left/right
- **ESC**: Exit the program
- **X (close window)**: Exit the program

### Project Structure
```
cub3D/
├── src/
│   ├── main.c
│   ├── Core/           # Initialization and error handling
│   ├── Graphics/       # Rendering, raycasting, textures
│   ├── Logic/          # Input handling, movement, rotation
│   ├── MLX/           # MinilibX integration
│   └── Parser/        # Map file parsing and validation
├── include/
│   └── cub3d.h        # Main header file
├── lib/
│   ├── libft/         # Custom C library
│   └── minilibx/      # Graphics library
├── data/
│   └── textures/      # Sample texture files
└── Makefile
```

### Error Handling
The program includes comprehensive error checking for:
- Invalid map format or missing elements
- Inaccessible texture files
- Invalid RGB color values (0-255)
- Unclosed maps or invalid characters
- Memory allocation failures
- Invalid file permissions

## Resources

### Technical References
- **Raycasting Tutorial**: [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)
- **MinilibX Documentation**: Official documentation for the graphics library
