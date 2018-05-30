# Graphics project framework

Xillez - kent.wincent46@gmail.com

### Introduction

A lightweight graphics framework, using OpengGL as Graphics API and GLFW as windowing framework and ImGUI as GUI API.

### Libraries used:

- SOIL - Texture/Image loading - Put link here!
- GLFW 3.0 - Windowing framework - Put link here!
- ImGUI - Lightweight GUI library - Put link here!
- OpenGL 4.5 - Graphics Library - Put link here!
- GLEW - Binding to opengl - Put link here!

### Tools used:

- CMake
- Make
- Doxygen

### Installation / Usage
1. Install linux (supports only linux for now).

2. From repository root, run:

   ```Shell
   mkdir build && cd build
   ```


3. Build the program: 
  ```Shell
    cmake .. && make
  ```
  4. Run the executable:

     ``` 
     ./bin/Exam
     ```

### Features: 

- Loading height map and generates terrain with this
- Mouse controls first person view (right-click to move).
- Phong Lighting (flat shading).

### TODO:

- Add support for multiple build methods. (VERY HIGH) 
- Input handling system: 
  - Redo entire input handling system. (VERY HIGH)
  - Add support for multikey input. (VERY HIGH)
  - Add support for multi-assigning off keys given context (eg. In free-cam view "w" is "forward", whilst in glider/plane it's pushing the nose down) (Add keybinding behaviour on the objects them selfs and make objects subscribe ). (LOW)

- Map generation:
  - Make image resolution independent. (MEDIUM 1.)
    - Add size specification for terrain. (LOW)
  - Make perlin-noise terrain generator if selected. (LOW)
- Terrain:
  - Texture terrain. (LOW)
  - Fix smoothing (TESSELLATION SHADER). (MEDIUM 1.)
  - Add better day-night cycle. (LOW)
  - Add mirroring / continuity of terrain "tiles". (LOW)
- Camera:
  - 1st person cam on objects (Add a camera (maybe component) that will override the current state of the true camera). (MEDIUM 2.)
  - 3rd person cam on objects (See 1st person idea). (MEDIUM 2.)
  - Smoothing / LERPING / SLERPING of positional change / object locking or switching. (MEDIUM 1.)
- Make UI system (Using YAML / (XML, maybe)):
  - Load layout file and build the UI with it that. (MEDIUM 1.)
  - Add programmatic layout specification. (MEDIUM 1.)
- Lighting:
  - Add Phong lighting with phong shading. (LOW)
  - Make user able to choose phong or flat shading. (VERY LOW)
- Shadows
  - Implement shadows (shadow mapping). (LOW)
  - Allow user to choose face or pixel-based shadowing. (VERY LOW)
- Viewports:
  - Add viewports for game development / minimap etc... (LOW).