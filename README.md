# Graphics project framework

Xillez - kent.wincent46@gmail.com

### Introduction

A lightweight graphics framework, using OpengGL as Graphics API and GLFW as windowing framework and ImGUI as GUI API.

### Installation
1. Install linux.

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
- Mouse controls first person view.
- Phong Lighting (flat shading).



### TODO:

- Map generation:
  - Make image resolution independent
  - Make perlin-noise terrain generator if selected
  - Add size specification for terrain
- Terrain:
  - Texture terrain
  - Fix smoothing (TESSELLATION SHADER)
  - Add better day-night cycle
  - Add mirroring / continuity of terrain "tiles".
- Camera:
  - 1st person cam
  - 3rd person cam
  - Snapping to object
  - Smoothing / LERPING / SLERPING of positional change
- Make UI system (Using YAML / (XML, maybe)):
  - Load layout file and build the UI base upon that
  - Add programmatic layout specification
- Lighting:
  - Convert Phong lighting from flat to phong shading (if wanted by user).
- Viewports:
  - Add viewports for game development / minimap etc...