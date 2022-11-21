# Basics
Screen:80x25
Canvas: 78x20
Tick rate: 20fps

```
+------------------------------------------------------------------------------+
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
+------------------------------------------------------------------------------+
Status line 1
Status line 2
Status line 3
```

(Max is using braille, which would make the screen size 160x60)

Border options:
- Blocking
- Non-blocking
  - Despawn entities that are off screen for 10 frames
  - Players cannot move off screen

Note: Game state is encapsualted by the client.

Code structure:
Seperate:
- Engine Logic
- Display Logic
- Input Logic

Potentailly?
Display -> Engine -> Input

```C++
class Visualizer {
  char[78][20] screen; //xy bitmap for the canvas
  void loadObjects(); //Loads objects from the engine, drawing them to the screen in order of z-index
  void draw(); //Draws the screen to the terminal
  public:
    void update(); //Calls draw() and loadObjects()
}

class Engine {
}

class Input { //takes input from cin and packs it to the engine.
  std::map<char,bool> input; //A map of char keys (keyboard inputs) with corresponding booleans (pressed or not)
}
```

# Objects:
Defined as either
- A char (ASCII)
- A rect
- A bytemap (vector of triples of `(x, y, char)`)

Things they can do:
- Move in a line
- Cycle through different sprites
- Move towards an edge
- Controlled by a player
- Spawn other objects

```C++
class VirtualObject {
  int x, y;

}

class VisualObject: virtual public VirtualObject {
  int z;
  int visualState;
  public:
    virtual void draw() = 0;
}

class PhysicsObject: virtual public VirtualObject {
  public:
    enum CollisionType {
      DISABLED,
      BOUNCE,
      STOP,
      CHANGE_STATE,
      TRIGGER_EVENT
    }
    virtual void move() = 0;
}

class Object : public VisualObject {
  public:
    virtual void update() = 0;
    void move() override = 0;
    void draw() override = 0;

    enum movementType {
      Player,
      Line,
      PullOut
    }
}



# Physics:
There should be Z-layering, so that objects can be drawn on top of each other.

For objects on the same layer collisions can:
- Be ignored
- Cause a bounce
- Stop both objects
- Change the state of one or both objects
- Trigger a gamestate change

```C++
enum CollisionType {
  DISABLED,
  BOUNCE,
  STOP,
  CHANGE_STATE,
  TRIGGER_EVENT
}
```

