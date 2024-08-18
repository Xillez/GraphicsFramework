# Graphics project framework

### Introduction

A lightweight graphics framework, using OpengGL as Graphics API and GLFW as windowing framework and ImGUI as GUI API.

### Libraries used:

- OpenGL 4.5
- SOIL - Texture/Image loading - http://www.lonesock.net/files/soil.zip
- GLFW 3.0 - Windowing framework - http://www.glfw.org/download.html
- ImGUI - Lightweight GUI library - https://github.com/ocornut/imgui/releases
- GLEW - Binding to OpenGL - http://glew.sourceforge.net/
- GLM - OpenGL Math Library - https://glm.g-truc.net/0.9.9/index.html

### Tools used:

- CMake - https://cmake.org/download/
- Make - http://gnuwin32.sourceforge.net/packages/make.htm
- Doxygen - http://www.stack.nl/~dimitri/doxygen/download.html
- Dot(graphviz) - http://www.graphviz.org/download/

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
