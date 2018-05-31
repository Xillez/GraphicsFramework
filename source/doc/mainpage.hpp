/*! \mainpage Exam
 *	
 *	\section authors_sec Authors:
 *	\author Xillez - @xillez
 *	
 * \section intro_sec Introduction
 * 
 * A lightweight graphics framework, using OpengGL as Graphics API and GLFW as windowing framework.
 * 
 * \section install_sec Installation
 *	1. Install linux.
 *	2. From repository root, run mkdir build && cd build.
 *	3. Build the program: 
 *	```Shell
 *	cmake .. && make
 *	```
 *	4. Run the executable:
 *	``` 
 *	./bin/Exam
 *	```
 * \section feature_sec Features
 *
 *	- Mouse controls first person view.
 *	- Move view with WASD.
 *	- Lighting.
 *  
 * \todo
 * 
 *  Add support for multiple build methods. (VERY HIGH)
 *
 *   - Input handling system:
 *       - Redo entire input handling system. (VERY HIGH)
 *       - Add support for multikey input. (VERY HIGH)
 *       - Add support for multi-assigning off keys given context (eg. In free-cam view "w" is "forward", whilst in glider/plane it's pushing the nose down) (Add keybinding behaviour on the objects them selfs and make objects subscribe ). (LOW)
 *
 *   - Map generation:
 *       - Make image resolution independent. (MEDIUM 1.)
 *            Add size specification for terrain. (LOW)
 *       - Make perlin-noise terrain generator if selected. (LOW)
 *
 *   - Terrain:
 *       - Texture terrain. (LOW)
 *       - Fix smoothing (TESSELLATION SHADER). (MEDIUM 1.)
 *       - Add better day-night cycle. (LOW)
 *       - Add mirroring / continuity of terrain "tiles". (LOW)
 *
 *   - Camera:
 *       - 1st person cam on objects (Add a camera (maybe component) that will override the current state of the true camera). (MEDIUM 2.)
 *       - 3rd person cam on objects (See 1st person idea). (MEDIUM 2.)
 *       - Smoothing / LERPING / SLERPING of positional change / object locking or switching. (MEDIUM 1.)
 *
 *   - Make UI system (Using YAML / (XML, maybe)):
 *       - Load layout file and build the UI with it that. (MEDIUM 1.)
 *       - Add programmatic layout specification. (MEDIUM 1.)
 *
 *   - Lighting:
 *       - Add Phong lighting with phong shading. (LOW)
 *       - Make user able to choose phong or flat shading. (VERY LOW)
 *
 *   - Shadows
 *       - Implement shadows (shadow mapping). (LOW)
 *       - Allow user to choose face or pixel-based shadowing. (VERY LOW)
 *
 *   - Viewports:
 *       - Add viewports for game development / minimap etc... (LOW).
 */