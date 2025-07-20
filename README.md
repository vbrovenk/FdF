# 🗺️ FdF
FdF (short for *Fil de Fer*, "wireframe" in French) proposes to represent the mesh in "wire of a field" in 3D. In this project is used library 'mlx'.
It was developed internally and includes the minimum necessary to open a window, light a pixel and deal with events linked to this window: keyboard and mouse.

## 🚀 Features

- 📡 Parse and display `.fdf` height maps
- 🧱 Wireframe rendering of 3D terrain
- 🌀 Isometric and parallel projections
- 🎨 Dynamic coloring based on altitude
- 🖱️ Zoom, pan, rotate in real time
- 🧵 Multi-threaded rendering for performance
- ⌨️ Interactive controls with keyboard

## 🗂️ Project structure

``` bash
fdf/
├── libft/           # Custom C library
├── minilibx/        # Graphics library
├── fdf.h            # Header file
├── Makefile         # Build system
└── README.md
```

## 🛠️ Installation & Usage

```bash
# Clone the repository
git clone https://github.com/vbrovenk/FdF.git
cd fdf

# Build the project
make

# Run with one of the .fdf map files in the maps/ folder or create your own
./fdf maps/42.fdf
```

## 🎮 Controls

| Action                 | Key                     |
|------------------------|-------------------------|
| Zoom In / Out          | X / Z                   |
| Move                   | Arrow Keys              |
| Rotation X             | W / S                   |
| Rotation Y             | Q / E                   |
| Rotation Z             | A / D                   |
| Reset                  | Backspace               |
| Exit                   | ESC                     |
| Help On/Off            | ?                       |

## Examples of run program

![img](https://github.com/vbrovenk/FdF/blob/master/imgs/Screen%20Shot%202019-03-07%20at%2011.54.49%20AM.png)

![img](https://github.com/vbrovenk/FdF/blob/master/imgs/Screen%20Shot%202019-03-07%20at%2011.56.33%20AM.png)
