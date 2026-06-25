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
