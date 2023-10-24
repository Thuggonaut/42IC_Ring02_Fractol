# Fract-ol

A project creating a Fractal exploration program. 

A fractal has self-similarity:
- The property of an object which looks the same whatever the scale (no matter how big or how small they are).
- E.g. the snowflake, Romanesco Broccoli, pine cones, succulents, tree branches, foam.


## Preface:
- This project was challenging, though enjoyable to complete, and the end result is so worth it!
- I completed the mandatory and 4/5 of the project (everything except the third fractal).
- I started with Linux, and once the program functioned, I translated the code to work on MacOS. See notes here: though much might not make sense until after delving in to the project's implementation.
- The versions included are /linux /macos_commented and /norminette 
- Here is the outline of how I tackeled fract-ol:
	- Step 1: Learn the MiniLibX graphical library
	- Step 2: Learn the Complex numbers notion
	- Step 3: Learn how Fractals work
	- Step 4: Learn about Event handling in the context of the project
	- Step 5: Plan the structure of directories and files
	- Step 6: Implement fract-ol
	- Step 7: Test fract-ol against evaluation checklist: https://rphlr.github.io/42-Evals/Rank02/fract-ol/


## The Mandatory (including most of the Bonus) part:

Rendering requirements:
- The Mandelbrot and Julia fractal sets
- Mouse wheel zooms in/out. For Bonus, the zoom follows the mouse position
- Julia: can create different sets by passing different parameters to the ./fractol arguments
- If no parameters are provided, display a list of parameter options before a clean exit
- Use atlease three colours
- Bonus: move the view with arrow keys
- Bonus: Make the colours shift

Graphic management:
- Smooth window management
- Pressing ESC or clicking X on the window, closes the window and clean exit
- Must use images of the MiniLibX


## Step 5: Plan the structure of directories and files

```
fractol/
│
├── Makefile
│
├── libft/
│
├── minilibx-macos/
|
├── inc/
│   └── fractol.h 
│
└── src/
	├── fractol.c
	├── events.c
	├── init.c
	├── colours.c
	├── render.c
	└── utils.c
```

# Differences between Linux and MacOS:
- MiniLibx libraries:
	- For M, I went with OpenGL version
	- Download it from the project page on your intra, unzip the file then place the directory at the root of your repository.
	- When compiling your fractol, there will be warnings shown on the console relating to the MiniLibx - don't mind this. 
	- At the root of your repository, do:
		<norminette> <project/directories> to only check norm errors in your source files, e.g. `norminette inc/ src/`
- MiniLibx functions:
	- L uses mlx_destroy_window() and mlx_destroy_display
	- M uses the one mlx_destroy_window()
- Keypress codes:
	- M uses Applescript key codes, different to that of L
- Makefile linker flags:
	- L uses -lXext -lX11 
	- M uses -Lminilibx-macos -lmlx -framework OpenGL -framework AppKit 
	- In my Makefile, I wrote it in a way that it could detect between Linux and MacOS, and compile accordingly. This seemed a great idea at first (and now I've learned something new), it was redundant because, of the differences in codes and functions mentioned above. There would surely be a way to remedy this, to write code that works universally. 

# FORMULAS:

MANDELBROT formula:
z = z^2 + c

PYTHAGOREAN THEOREM:
In a right triangle (a triangle with one angle of 90 degrees), the square of the length of the hypotenuse (the side opposite
the right angle) is equal to the sum of the squares of the lengths of the other two sides. 

In a right triangle:

Let "a" and "b" be the lengths of the two shorter sides (the legs).
Let "c" be the length of the hypotenuse.
The theorem states that:

a^2 + b^2 = c^2


FORMULA TO SQUARE A COMPLEX NUMBER:

Given a complex number z with a real component x and an imaginary component y:

    z = x + yi

The square of z^2 is calculated as:

*Note: [i^2 = -1 complex maths]

    z^2 
=   (x + yi)^2
=   (x + yi) * (x + yi)

Apply FOIL (First, Outer, Inner, Last):

=   x^2 + xyi + xyi + (yi)^2
= 	x^2 + 2xyi - y^2
=   (x^2 - y^2) + (2xyi)



# Complex Plane:

The "complex plane" is a mathematical concept used in complex number theory and fractal geometry.
It's a two-dimensional plane where each point represents a complex number.
The complex plane has two axes: the horizontal axis, often denoted as the real axis, and the vertical axis, often denoted as the imaginary axis.
Complex numbers are represented in the form "a + bi," where "a" is the real part and "b" is the imaginary part. The real axis represents the "a" component, and the imaginary axis represents the "b" component.
In the context of fractals like the Mandelbrot set and Julia sets, the complex plane is used to explore and visualize the behavior of complex functions. The points in the complex plane are iteratively computed to determine if they are within certain boundaries, and this information is used to generate fractal images.

# Translation:

In the context of graphics and computer graphics, "translation" refers to the process of moving an object or image from one location to another within a two-dimensional or three-dimensional space.
It involves changing the position of the object while keeping its orientation and size constant.
In the t_fractol structure, shift_r and shift_i are used to control the translation of the fractal image. They determine how much the image is shifted horizontally (shift_r) and vertically (shift_i) within the complex plane.

# Julia constants:

double julia_r: This field is used when you're dealing with a Julia fractal. In the context of fractals, a Julia set is defined by a mathematical equation where you have a constant (also called a seed) that influences the shape and characteristics of the fractal. The julia_r field represents the real component of this constant. It's a numerical value that determines the horizontal position of the Julia set within the complex plane. By adjusting julia_r, you can shift the Julia set left or right, which in turn alters the appearance of the fractal.

double julia_i: Just like julia_r, this field is specific to Julia fractals. It represents the imaginary component of the Julia constant. The imaginary component, similar to the real component, influences the vertical position of the Julia set within the complex plane. By adjusting julia_i, you can move the Julia set up or down, leading to changes in the fractal's appearance.

# Linear interpolation: 

is a method for estimating values within a range based on known values at the endpoints of that range. It's like drawing a straight line between two points on a graph and finding the value of any point along that line.

In your context, you have a value unscaled_num that you want to map from one range to another. Let's say you have these values:

unscaled_num: The value you want to map.
old_min and old_max: The original range where unscaled_num is coming from.
new_min and new_max: The new range where you want to map unscaled_num.
The basic idea is to find a linear relationship between these two ranges. Here's the formula for linear interpolation:

MappedValue = (unscaled_num - old_min) / (old_max - old_min) * (new_max - new_min) + new_min
Let's break down the components of this formula:

(unscaled_num - old_min): This part calculates where unscaled_num is located within the original range. It measures how far unscaled_num is from the lower boundary (old_min) of the original range.

(old_max - old_min): This represents the full span or width of the original range. It's the difference between the upper and lower boundaries.

(new_max - new_min): This represents the full span or width of the new range. It's the difference between the upper and lower boundaries of the new range.

(unscaled_num - old_min) / (old_max - old_min): This part scales the position of unscaled_num within the original range to a position within the [0, 1] interval. It essentially tells you what fraction of the original range unscaled_num occupies.

* (new_max - new_min): This scales the fraction from the previous step to fit within the new range.

+ new_min: This shifts the scaled and stretched fraction to align it with the new range. It's essentially mapping the fraction back to the new range.

This entire process effectively maps unscaled_num from the original range to the new range. The linear interpolation formula calculates where unscaled_num would fall in the new range based on its position in the original range.

When you're scaling a map, you want to change the dimensions (size) of the map but maintain the same aspect ratio.

Here's how linear interpolation can help with this:

Step 1: Understanding the Problem
Let's say you have a map, and you want to scale it to fit within a new width and height while preserving the aspect ratio. For this, you'll need to calculate how much each coordinate in the map needs to be scaled in both the horizontal and vertical directions.

Step 2: Calculate Scaling Ratios
You can calculate two scaling ratios: one for the horizontal direction (width) and one for the vertical direction (height). These ratios will maintain the aspect ratio.

Horizontal Scaling Ratio (x_ratio): This is calculated as the new width divided by the old width.
Vertical Scaling Ratio (y_ratio): This is calculated as the new height divided by the old height.
Step 3: Apply Linear Interpolation
Now, for each point on the map (x, y), you apply linear interpolation to calculate the new coordinates (new_x, new_y) after scaling.

Mapping each point from the original map to the new map while maintaining the aspect ratio. Essentially, you're stretching or compressing the map in both horizontal and vertical directions based on the scaling ratios

# Linear interpolation and colour blending:

Linear interpolation between two colours results in a blending of colours because it calculates intermediate colours by smoothly transitioning from one colour to another. This process creates a gradient or transition effect, which visually appears as a blend of the two original colours.

Here's a simple example to illustrate the concept of linear interpolation for blending colours:

Suppose you have two colours, Colour A and Colour B, and you want to blend them together. You can do this using linear interpolation. Each colour can be represented as a combination of its red (R), green (G), and blue (B) components, each ranging from 0 to 255 (or 0 to 1 in normalized form). Linear interpolation is performed independently for each of these colour components (R, G, and B).

Start with the two colours, Colour A and Colour B, and their respective RGB values.

Calculate the intermediate colour at a specific point between these two colours. For example, at the halfway point (t = 0.5) between Colour A and Colour B, the intermediate colour's RGB components are calculated as follows:

Red Component (R): Intermediate_R = (1 - t) * A_R + t * B_R
Green Component (G): Intermediate_G = (1 - t) * A_G + t * B_G
Blue Component (B): Intermediate_B = (1 - t) * A_B + t * B_B
Here, t represents the position along the gradient, and it ranges from 0 to 1. When t is 0, the intermediate colour is equal to Colour A, and when t is 1, the intermediate colour is equal to Colour B.

By varying the value of t between 0 and 1, you can calculate a range of intermediate colours that smoothly transition from Colour A to Colour B.

The result is a series of colours that blend or transition from one to the other. When displayed in succession, it creates a visually appealing gradient or blending effect, which can be used for various purposes, such as shading, colouring, and creating smooth colour transitions in graphics and visual applications.

Example:

Imagine you have two colours, Red and Blue, and you want to create a smooth colour transition between them. Red is represented as (255, 0, 0) in RGB (where 255 is the maximum intensity for the red component), and Blue is (0, 0, 255). You want to create a gradient that goes from Red to Blue.

Choose a specific point along the gradient. Let's say you want to find the colour at the halfway point, t = 0.5.

For the Red component (R), you calculate it as follows:

Intermediate_R = (1 - t) * Red_R + t * Blue_R
Intermediate_R = (1 - 0.5) * 255 + 0.5 * 0
Intermediate_R = 0.5 * 255
Intermediate_R = 127.5

For the Green and Blue components (G and B), you do the same calculation. In this case, since we're at the halfway point, the Green and Blue components will also be 127.5.

So, at t = 0.5, you get the colour (127.5, 127.5, 127.5), which is a shade of gray. It's the halfway point between Red and Blue.

By changing t from 0 to 1, you can find the colours at various points along the gradient. At t = 0, you get Red, and at t = 1, you get Blue. At all the points in between, you get different shades that smoothly transition from Red to Blue.

Analogy:

Think of this process as mixing two paint colours, Red and Blue, on a canvas. At t = 0, you have a canvas filled with pure Red. At t = 1, the canvas is covered with pure Blue. As you increase t from 0 to 1, you start adding Blue to the canvas while gradually reducing the amount of Red. This creates a smooth transition from Red to Blue. At t = 0.5, you've mixed an equal amount of Red and Blue, resulting in a shade of purple (in this case, gray in the RGB colour model).

# References:
- Getting started with MiniLibX: https://harm-smits.github.io/42docs/libs/minilibx 
- MiniLibX Tutorial: https://www.youtube.com/watch?v=bYS93r6U0zg&t=0s 
- Fractal Tutorial, great explanation of the complex notion: https://youtu.be/ANLW1zYbLcs?si=y3CA7zvfdCfzZNr3 
- Julia set values: https://en.wikipedia.org/wiki/Julia_set 