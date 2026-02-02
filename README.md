# Fract-ol

A graphical exploration project built with the **MLX42** library. This program renders mathematically beautiful fractals—infinite geometric patterns that are self-similar across different scales. It allows users to explore these sets through real-time interaction, zooming, and parameter manipulation.

## 💡 Overview

The goal of this project is to create a small fractal exploration tool.
* **Rendering:** Uses the CPU to calculate complex number iterations for every pixel on the screen.
* **Interaction:** Users can zoom infinitely (until `double` precision limits), move around the complex plane, and shift colors dynamically.
* **Math:** Implements the mathematical formulas for the **Mandelbrot**, **Julia**, and **Phoenix** sets.

## 🎨 Fractals Supported

1.  **Mandelbrot Set**: The classic set of points $c$ in the complex plane for which the function $f_{c}(z)=z^{2}+c$ does not diverge when iterated from $z=0$.
2.  **Julia Set**: A family of fractals defined by the same formula as Mandelbrot, but where $c$ is a constant parameter and the initial $z$ varies. This program allows you to input specific starting values for the Julia set.
3.  **Phoenix Set**: A variation of the Mandelbrot set involving a different iteration formula, often resulting in unique, curve-like structures.

## 📦 Installation & Compilation

Clone the repository and compile the executable. This project requires the **MLX42** library (and GLFW).

```bash
git clone <repository-url>
cd fract-ol
make
```

This will generate the `fractol` binary.

## 🚀 Usage

Run the program by specifying the fractal type. For the Julia set, you must also provide the real and imaginary coordinate constants.

### Syntax
```bash
./fractol [fractal_type] [parameters]
```

### Examples
**Mandelbrot:**
```bash
./fractol mandelbrot
```

**Julia:** (Requires distinct starting parameters)
```bash
./fractol julia -0.8 0.156
./fractol julia 0.285 0.01
```

**Phoenix:**
```bash
./fractol phoenix
```

*If invalid arguments are provided, the program displays a list of available fractals.*

## 🎮 Controls

The program provides hooks for keyboard and mouse interaction:

| Input | Action |
| :--- | :--- |
| **Scroll Wheel** | Zoom In / Zoom Out (at mouse cursor position) |
| **Arrow Keys** | Pan the view (Up, Down, Left, Right) |
| **C** | Cycle through Color Modes (Psychedelic, Inverted, Gradient) |
| **W / S** | Adjust specific fractal parameter (e.g., parameter `p` for Phoenix) |
| **ESC** | Close the window and exit |

## 🛠️ Technical Details

* **Complex Mapping**: Pixel coordinates $(x, y)$ are mapped to the complex plane $(Zr, Zi)$ using dynamic scaling factors (`zoom`) and offsets (`offset_x`, `offset_y`).
* **Color Algorithms**:
    * **Mode 0**: Iteration-based RGB generation using modulo arithmetic for high contrast.
    * **Mode 1**: Inverted scheme (dark center, bright edges).
    * **Mode 2**: Smooth gradient intensity based on escape velocity.
* **MLX42**: Utilizes the modern MLX42 graphics library for window management and pixel putting (`mlx_put_pixel`).

## 📂 Project Structure

* **`src/main.c`**: Entry point, argument parsing (`ft_juliarguments`), and validation.
* **`src/fractal.c`**: Initialization of the MLX window and setup of hook functions (`ft_launch`).
* **`src/fractals.c`**: Core rendering logic for Mandelbrot, Julia, and Phoenix sets. Contains coordinate mapping.
* **`src/input.c`**: Event handling for keyboard (`ft_keys`) and color calculation logic (`ft_color`).
* **`inc/fractol.h`**: Data structures (`t_frc`) and function prototypes.
