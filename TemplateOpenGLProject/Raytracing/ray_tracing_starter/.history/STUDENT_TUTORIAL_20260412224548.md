# Ray Tracing Starter Project: Student Tutorial

This guide helps you build, run, modify, and debug this ray tracing demo.

This guide is adapted from [Ray Tracing in One Weekend Series](https://raytracing.github.io/)

## 1. What this project does

This project renders a simple ray-traced scene and writes a PNG image to disk.

- Build system: CMake
- Language: C++14
- Executable name: ray_tracing_starter
- Main entry point: the project main program file

## 2. Prerequisites

Please make sure your machine has:

- A C++ compiler that supports C++14 (Apple Clang or GCC)
- CMake 3.10 or newer
- make

Quick check:

Check your compiler, CMake, and build tool versions from your terminal before starting.

## 3. Build and run

Build and run from a dedicated build directory under the project root, then start the executable from that directory.

## 4. Where output images are saved

The renderer writes output files in the current working directory where you launch the executable.

- If you run from the build directory, the output image is saved in that build directory.

The generated filename ends with test.png.

An example of the output image is shown below:

## 5. Project structure and important files

Core rendering flow:

1. Program entry and scene setup.
2. Ray-object intersection logic.
3. Primitive intersection implementation.
4. Camera ray generation.
5. Material utility functions for reflection, refraction, and random sampling.
6. Pixel buffer handling and PNG export.

Material implementations:

- Diffuse material (implemented).
- Reflective metal material (starter TODOs present).
- Dielectric or glass material (starter TODOs present).

## 7. Tuning quality and speed

In the rendering configuration:

- width, height: image resolution.
- ray_num: samples per pixel.

Practical defaults:

- Fast preview: 384 x 216, ray_num = 10
- Better quality: 1280 x 720, ray_num = 50+
- High quality: 1920 x 1080, ray_num = 100+

Note: render time grows roughly linearly with pixel count and samples.

## 8. Common issues and fixes

### Issue A: CMake path/cache mismatch

Symptom:

- Error says CMakeCache.txt was created in another directory (often a moved/deleted path).

Fix:

Delete the old build folder, regenerate the build configuration, then rebuild the project.

### Issue B: Image is blank or all black

Check these in order:

1. Confirm the render loop actually computes color for every pixel.
2. Confirm output image was generated in the folder where executable was launched.
3. Verify materials return valid scattered rays, especially reflective and dielectric materials.
4. Test with only Lambertian spheres first to isolate material bugs.

### Issue C: Output too noisy

- Increase ray_num.
- Optionally reduce depth complexity while debugging.

## 9. Suggested experiment checklist

- Change camera position.
- Add more spheres to the random scene.
- Compare metal with low fuzz (0.0 to 0.2) and high fuzz (0.8 to 1.0).
- Test different refractive_index values for dielectric (for example 1.33 vs 1.5).
