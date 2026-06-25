System Workflow
Start Program
      │
      ▼
Initialize GLFW & OpenGL
      │
      ▼
Create Window
      │
      ▼
Load Shaders
      │
      ▼
Create Game Objects
(Player, Obstacle, Ground)
      │
      ▼
Enter Game Loop
      │
      ├─────────────► Process Input
      │
      ├─────────────► Update Physics
      │               (Gravity & Jump)
      │
      ├─────────────► Move Obstacle
      │
      ├─────────────► Collision Check
      │
      ├─────────────► Update Score
      │
      ├─────────────► Render Scene
      │
      ▼
Game Over?
      │
   Yes │ No
      ▼
Display Final Score
      │
      ▼
Reset or Exit
Block Diagram
+---------------------------------------------------+
|                   USER INPUT                      |
|          (Keyboard / Mouse Events)                |
+-----------------------+---------------------------+
                        |
                        v
+---------------------------------------------------+
|                 GAME CONTROLLER                   |
|                                                   |
| - Jump Handling                                   |
| - Reset Handling                                  |
| - Quit Handling                                   |
+-----------------------+---------------------------+
                        |
                        v
+---------------------------------------------------+
|                 PHYSICS ENGINE                    |
|                                                   |
| - Gravity Calculation                             |
| - Jump Velocity                                   |
| - Position Update                                 |
+-----------------------+---------------------------+
                        |
                        v
+---------------------------------------------------+
|              COLLISION DETECTOR                   |
|                                                   |
| - Player Bounds                                   |
| - Obstacle Bounds                                 |
| - Overlap Detection                               |
+-----------------------+---------------------------+
                        |
                        v
+---------------------------------------------------+
|                 SCORE SYSTEM                      |
|                                                   |
| - Pass Detection                                  |
| - Score Increment                                 |
+-----------------------+---------------------------+
                        |
                        v
+---------------------------------------------------+
|             OPENGL RENDERING UNIT                 |
|                                                   |
| - Draw Obstacle                                   |
| - Draw Player                                     |
| - Draw Ground                                     |
+---------------------------------------------------+
4. Pseudocode
BEGIN

Initialize GLFW
Create OpenGL Window
Load GLAD

Compile Vertex Shader
Compile Fragment Shader

Create Rectangle Object
Create Star Object
Create Ground Line

Initialize Game Variables

WHILE window is open

    Calculate Delta Time

    IF game is not over THEN

        Move obstacle

        IF obstacle leaves screen THEN
            Spawn obstacle from random direction
            Increase obstacle speed
        ENDIF

        Apply gravity

        Update player position

        IF player reaches ground THEN
            Stop falling
        ENDIF

        Check score condition

        Calculate collision boundaries

        IF collision detected THEN
            Game Over
        ENDIF

    ENDIF

    Clear screen

    Draw obstacle

    Draw player

    Draw ground

    Swap buffers

END WHILE

Release OpenGL resources

Terminate GLFW

END
