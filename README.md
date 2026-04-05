*this project has been created as part of the 42 curriculum by vpoelman*

## Description

cub3D is a 3D maze exploration game inspired by the legendary Wolfenstein 3D, the world's first FPS. The goal is to implement a realistic 3D rendering engine using the raycasting technique: from a 2D map, the program renders a first-person perspective view in real time, with textured walls on each cardinal direction (North, South, East, West), and configurable floor and ceiling colors.

The project is built in C using the MiniLibX graphics library, and relies on a custom map format (.cub) that defines the scene layout, textures, and colors.

## Instructions

### Requirements

- Linux with X11
- cc, make
- MiniLibX dependencies: libXext, libX11

### Compilation

bash
make

This will compile libft, mlx, and the project into the cub3D executable.

### Execution

./cub3D <path_to_map.cub>


Example:
./cub3D maps/te.cub


### Map format (.cub)

NO ./textures/north.xpm   # North wall texture
SO ./textures/south.xpm   # South wall texture
WE ./textures/west.xpm    # West wall texture
EA ./textures/east.xpm    # East wall texture

F 50,50,50                # Floor color (R,G,B)
C 200,200,200             # Ceiling color (R,G,B)

11111
1N001                     # N/S/E/W = player start position & orientation
11111


Map rules: must be fully enclosed by walls (1), player spawn is indicated by N, S, E, or W.

### Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate left |
| `→` | Rotate right |
| `ESC` | Quit |

### Cleanup

bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Full recompile


## Resources

### Raycasting & 3D rendering

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [Wolfenstein 3D source code](https://github.com/id-Software/wolf3d)
- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- https://lodev.org/cgtutor/raycasting.html

### AI usage

Claude (Anthropic) was used during this project for:
- Debugging parsing edge cases (map validation, color parsing)
- Understanding and structuring the raycasting algorithm
- Reviewing memory management and cleanup logic
- Verification of edge cases for the evaluation
- Code simplification for Norminette compliance and file reorganization
