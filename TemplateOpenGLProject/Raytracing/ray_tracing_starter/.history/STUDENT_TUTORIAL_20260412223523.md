# Ray Tracing Starter Project: Student Tutorial

This guide helps you build, run, modify, and debug the assignment project.

## 1. What this project does

This project renders a simple ray-traced scene and writes a PNG image to disk.

- Build system: CMake
- Language: C++14
- Executable name: ray_tracing_starter
- Main entry point: [main.cpp](main.cpp)

## 2. Prerequisites

Please make sure your machine has:

- A C++ compiler that supports C++14 (Apple Clang or GCC)
- CMake 3.10 or newer
- make

Quick check:

```bash
c++ --version
cmake --version
make --version
```

## 3. Build and run

From the assignment root folder, run:

```bash
cmake -S . -B builds
cmake --build builds -j 8
./builds/ray_tracing_starter
```

Alternative (inside builds folder):

```bash
cd builds
cmake ..
make -j 8
./ray_tracing_starter
```

## 4. Where output images are saved

The renderer writes output files in the current working directory where you launch the executable.

- If you run from project root with ./builds/ray_tracing_starter, image is saved in project root.
- If you run inside builds with ./ray_tracing_starter, image is saved in builds.

The filename is generated in [main.cpp](main.cpp) and ends with test.png.

## 5. Project structure and important files

Core rendering flow:

1. [main.cpp](main.cpp): scene setup, render loop, color integration, PNG output.
2. [Scene.cpp](Scene.cpp): intersects one ray with all objects.
3. [Sphere.cpp](Sphere.cpp): sphere-ray intersection.
4. [Camera.cpp](Camera.cpp): generates primary rays.
5. [Material.cpp](Material.cpp): helper functions for reflection/refraction and random sampling.
6. [PNGMaster.h](PNGMaster.h): pixel buffer and PNG export.

Material implementations:

- [Lambertian.cpp](Lambertian.cpp): diffuse material (implemented).
- [Metal.cpp](Metal.cpp): reflective metal (starter TODOs present).
- [Dielectric.cpp](Dielectric.cpp): glass/refraction (starter TODOs present).

## 6. Assignment workflow for students

Recommended order:

1. Run baseline and confirm an image is produced.
2. Implement metal scattering in [Metal.cpp](Metal.cpp).
3. Enable metal spheres in [main.cpp](main.cpp) random_scene().
4. Implement dielectric scattering in [Dielectric.cpp](Dielectric.cpp).
5. Enable dielectric sphere in [main.cpp](main.cpp) random_scene().
6. Increase image quality by adjusting width, height, and ray_num in [main.cpp](main.cpp).

## 7. Tuning quality and speed

In [main.cpp](main.cpp):

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

```bash
rm -rf builds
cmake -S . -B builds
cmake --build builds -j 8
```

### Issue B: Image is blank or all black

Check these in order:

1. Confirm render loop in [main.cpp](main.cpp) actually calls cal_color for every pixel.
2. Confirm output image was generated in the folder where executable was launched.
3. Verify materials are returning valid scattered rays (especially [Metal.cpp](Metal.cpp), [Dielectric.cpp](Dielectric.cpp)).
4. Test with only Lambertian spheres first to isolate material bugs.

### Issue C: Output too noisy

- Increase ray_num.
- Optionally reduce depth complexity while debugging.

## 9. Suggested experiment checklist

- Change camera position (look_from, look_at) in [main.cpp](main.cpp).
- Add more spheres in random_scene().
- Compare metal with low fuzz (0.0 to 0.2) and high fuzz (0.8 to 1.0).
- Test different refractive_index values for dielectric (for example 1.33 vs 1.5).

## 10. Submission hygiene

Before submission:

1. Build from a clean builds directory.
2. Run once and verify image output exists.
3. Keep your TODO implementations in [Metal.cpp](Metal.cpp) and [Dielectric.cpp](Dielectric.cpp) readable and documented.
4. Avoid committing temporary binaries unless your course policy requires them.

---

If you want, you can also add a short report section containing:

- your final parameters (resolution, samples),
- render time,
- one example image,
- and a brief explanation of your material implementation choices.
