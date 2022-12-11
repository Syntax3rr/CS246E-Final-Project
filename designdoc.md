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



==30365== Memcheck, a memory error detector
==30365== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==30365== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==30365== Command: ./a.out
==30365== 
==30365== Invalid read of size 8
==30365==    at 0x49295E3: std::_Rb_tree_decrement(std::_Rb_tree_node_base*) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==30365==    by 0x11DDF6: std::_Rb_tree_iterator<std::pair<int const, std::vector<age::Entity, std::allocator<age::Entity> > > >::operator--() (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
==30365==    by 0x11CBDD: std::reverse_iterator<std::_Rb_tree_iterator<std::pair<int const, std::vector<age::Entity, std::allocator<age::Entity> > > > >::operator->() const (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
==30365==    by 0x11B541: age::Engine::getEntities() (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
==30365==    by 0x120CA4: age::Visualizer::loadCanvas() (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
==30365==    by 0x10C0E7: age::Visualizer::update() (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
==30365==    by 0x10A97B: main (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
==30365==  Address 0x70000005a is not stack'd, malloc'd or (recently) free'd
==30365== 
==30365== 
==30365== Process terminating with default action of signal 11 (SIGSEGV)
==30365==  Access not within mapped region at address 0x70000005A
==30365==    at 0x49295E3: std::_Rb_tree_decrement(std::_Rb_tree_node_base*) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
==30365==    by 0x11DDF6: std::_Rb_tree_iterator<std::pair<int const, std::vector<age::Entity, std::allocator<age::Entity> > > >::operator--() (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
==30365==    by 0x11CBDD: std::reverse_iterator<std::_Rb_tree_iterator<std::pair<int const, std::vector<age::Entity, std::allocator<age::Entity> > > > >::operator->() const (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
==30365==    by 0x11B541: age::Engine::getEntities() (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
==30365==    by 0x120CA4: age::Visualizer::loadCanvas() (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
==30365==    by 0x10C0E7: age::Visualizer::update() (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
==30365==    by 0x10A97B: main (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
==30365==  If you believe this happened as a result of a stack
==30365==  overflow in your program's main thread (unlikely but
 ==30365==  possible), you can try to increase the size of the
   ==30365==  main thread stack using the --main-stacksize= flag.
      ==30365==  The main thread stack size used in this run was 8388608.
      ==30365== 
 ==30365== HEAP SUMMARY:
 ==30365==     in use at exit: 77,044 bytes in 108 blocks
==30365==   total heap usage: 474 allocs, 366 frees, 89,229 bytes allocated
   ==30365== 
       ==30365== LEAK SUMMARY:
                                                                                                ==30365==    definitely lost: 0 bytes in 0 blocks
                 ==30365==    indirectly lost: 0 bytes in 0 blocks
             ==30365==      possibly lost: 0 bytes in 0 blocks
          ==30365==    still reachable: 77,044 bytes in 108 blocks
   ==30365==         suppressed: 0 bytes in 0 blocks
     ==30365== Rerun with --leak-check=full to see details of leaked memory
           ==30365== 
        ==30365== For lists of detected and suppressed errors, rerun with: -s
   ==30365== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
                                                                                                       Segmentation fault


==30750== Memcheck, a memory error detector
==30750== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==30750== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==30750== Command: ./a.out
==30750== 
==30750== Invalid read of size 8
   ==30750==    at 0x11D3E4: __gnu_cxx::__normal_iterator<age::Entity*, std::vector<age::Entity, std::allocator<age::Entity> > >::__normal_iterator(age::Entity* const&) (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
  ==30750==    by 0x11C693: std::vector<age::Entity, std::allocator<age::Entity> >::begin() (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
    ==30750==    by 0x11B572: age::Engine::getEntities() (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
    ==30750==    by 0x120A3A: age::Visualizer::loadCanvas() (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
   ==30750==    by 0x10C0E7: age::Visualizer::update() (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
 ==30750==    by 0x10A97B: main (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
    ==30750==  Address 0x70000006a is not stack'd, malloc'd or (recently) free'd
                             ==30750== 
       ==30750== 
    ==30750== Process terminating with default action of signal 11 (SIGSEGV)
                      ==30750==  Access not within mapped region at address 0x70000006A
    ==30750==    at 0x11D3E4: __gnu_cxx::__normal_iterator<age::Entity*, std::vector<age::Entity, std::allocator<age::Entity> > >::__normal_iterator(age::Entity* const&) (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
   ==30750==    by 0x11C693: std::vector<age::Entity, std::allocator<age::Entity> >::begin() (in /home/syntax3rr/git/CS246E-Final-Project/a.out
       ==30750==    by 0x11B572: age::Engine::getEntities() (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
      ==30750==    by 0x120A3A: age::Visualizer::loadCanvas() (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
                     ==30750==    by 0x10C0E7: age::Visualizer::update() (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
          ==30750==    by 0x10A97B: main (in /home/syntax3rr/git/CS246E-Final-Project/a.out)
   ==30750==  If you believe this happened as a result of a stack
         ==30750==  overflow in your program's main thread (unlikely but
 ==30750==  possible), you can try to increase the size of the
==30750==  main thread stack using the --main-stacksize= flag.
 ==30750==  The main thread stack size used                                                                           ==30750== 
 ==30750== HEAP SUMMARY:
 ==30750==     in use at exit: 77,044 bytes in 108 blocks
 ==30750==   total heap usage: 474 allocs, 366 frees, 89,229 bytes allocated
==30750== 
          ==30750== LEAK SUMMARY:
                 ==30750==    definitely lost: 0 bytes in 0 blocks
    ==30750==    indirectly lost: 0 bytes in 0 blocks
                       ==30750==      possibly lost: 0 bytes in 0 blocks
                   ==30750==    still reachable: 77,044 bytes in 108 blocks
              ==30750==         suppressed: 0 bytes in 0 blocks
    ==30750== Rerun with --leak-check=full to see details of leaked memory
         ==30750== 
         ==30750== For lists of detected and suppressed errors, rerun with: -s
     ==30750== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
 Segmentation fault
