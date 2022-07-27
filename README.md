# Console Game Engine
______________________________________________________________________________________
## Bases
```cpp
#include "ConsoleGameEngine/source/Bases/Bases_include.h"
```

- `Tag` - used to distinguish one object from another
```cpp
auto int_tag = CGE::get_class_tag<int>(); // returned tag equal to 0
auto float_tag = CGE::get_class_tag<float>(); // returned tag equal to 1
```
- `GameRect` - (x, y, width, height) structure
- `Color` - enumeration of colors
______________________________________________________________________________________
## Game Object
```cpp
#include "ConsoleGameEngine/source/Game Object/GameObject.h"
```
The base class of the game object, use for inheritance

### Useful fields (protected)
- `_position` - GameRect
- `_tag` - class tag
- `_destructor ` - allows to set a destructor when creating an object

### Methods
- `const GameRect& get_position() const` - return object position
- `tag_t get_tag() const` - return object class tag
- `void move_to(GameRect new_position)` - instantly moves the object to the specified position 

- `virtual void action(ObjectMap& _objects) {}` - for actions based on the state of other objects if necessary
- `virtual void update() {}` - for update the current state
- `virtual void render() {}` - for rendering
______________________________________________________________________________________
## CGEGame

Create file `MyGame.h`
```cpp
#include "ConsoleGameEngine/source/CGEGame/CGEGame.h"

class MyGame: public CGE::CGEGame<MyGame> {
public:
    MyGame(unsigned fps) : CGE::CGEGame<MyGame>(*this, fps) {}
}
```

Create file `main.cpp`
```cpp
#include "MyGame.h"

int main() {
    MyGame game(60);
    game.execute()
    return 0;
}

```
Run and get window

### Useful fields
- `_renderer` - Renderer instance
- `_game_objects` - map of game objects by tag
- `_is_active ` - set to `false` to terminate game process

### Methods (protected)
- `insert_game_object` - create and insert object to map of game objects
```cpp
insert_game_object<Player>(hp, damage);
```

- `get_objects_list` - get list of game objects by class type
```cpp
decltype(auto) enemies = get_objects_list<Enemy>();
```
______________________________________________________________________________________
## Camera
```cpp
#include "ConsoleGameEngine/source/Camera/Camera.h"
```
Allows set a certain position and move to the left/right/top/bottom with a certain step (must be equal to the player's step)

### Methods
- `void move_left(unsigned step = 1)`
- `void move_right(unsigned step = 1)`
- `void move_up(unsigned step = 1)`
- `void move_down(unsigned step = 1)`
- `void move_to(int x_centre, int y_centre)`
- `void set_position(GameRect position)`
______________________________________________________________________________________
## Renderer
```cpp
#include "ConsoleGameEngine/source/Renderer/Renderer.h"
```
Allows to draw symbols at the specified coordinates

Rederer contains a Camera by default, but its use is not necessary if rendering is used only by absolute coordinates

### Methods
- draw_symbol (overloaded for wchar_t and repeat count):
    - `void draw_symbol(char symbol, int x, int y, int color)`
    - `void draw_symbol(char symbol, int x, int y, int color, size_t count)`
    - `void draw_symbol(wchar_t symbol, int x, int y, int color)`
    - `void draw_symbol(wchar_t symbol, int x, int y, int color, size_t count)`
- draw_symbol_absolute (overloaded for wchar_t and repeat count):
    - `void draw_symbol_absolute(char symbol, int x, int y, int color)`
    - `void draw_symbol_absolute(char symbol, int x, int y, int color, size_t count)`
    - `void draw_symbol_absolute(wchar_t symbol, int x, int y, int color)`
    - `void draw_symbol_absolute(wchar_t symbol, int x, int y, int color, size_t count)`
- draw_string (overloaded for wchar_t):
    - `void draw_string(const char* string, size_t length, int x, int y, int color)`
    - `void draw_string(const wchar_t* string, size_t length, int x, int y, int color)`
- draw_string_absolute (overloaded for wchar_t):
    - `void draw_string_absolute(const char* string, size_t length, int x, int y, int color)`
    - `void draw_string_absolute(const wchar_t* string, size_t length, int x, int y, int color)`
- `Camera& get_camera()`
- `COORD get_mouse_position()`
______________________________________________________________________________________

## Event System
```cpp
#include "ConsoleGameEngine/source/Event System/EventSystem.h"


class Object : public GameObject {
private:
    int _value;
public:
    Object(CGE::EventSystem::IEvent<int>& event) :
        GameObject(CGE::GameRect(), CGE::get_class_tag<Object>()),
        _value(0)
    {
        decltype(auto) handler = CGE::EventSystem::createFunctorEventHandler([&value = _value](int add_value){ value += add_value; });
        event += handler;

        _destructor = [&event = event, &handler = handler](){
            event -= handler;
        }
    }
    int get_value() {return _value;}
}


int main() {
    CGE::EventSystem::Event<int> event;

    auto object = Object(event);

    event(1);
    std::cout << "Current value: " << object.get_value() << std::endl;
    event(2);
    std::cout << "Current value: " << object.get_value() << std::endl;
    event(3);
    std::cout << "Current value: " << object.get_value() << std::endl;

    return 0;
}
```
Output:
```
Current value: 1
Current value: 3
Current value: 6
```
______________________________________________________________________________________
## Finite State Machine
Uses lambda functions to set state actions

```cpp
#include <iostream>
#include "ConsoleGameEngine/source/FSM/FSM.h"

int main() {
    CGE::FSM::FSM<int> fsm;

    decltype(auto) state1 = fsm.add_state([]() {
        std::cout << "State 1 action";
    });
    decltype(auto) state2 = fsm.add_state([]() {
        std::cout << "State 2 action";
    });

    state1.add_transition([](int singal) -> decltype(&state1) {
		if (singal == 2) return &state2;
		return nullptr;
	});

    state2.add_transition([](int singal) -> decltype(&state2) {
		if (singal == 1) return &state1;
		return nullptr;
	});

    fsm.set_current_state(state1);  

    fsm.execute();
    fsm.handle(2);
    fsm.execute();
    fsm.handle(1);
    fsm.execute();
    return 0;
}
```
Output:
```
State 1 action
State 2 action
State 1 action
```

### State class methods
- `void add_transition(Functor&& functor)` - add transit condition
- `void set_entry(Functor&& functor)` - set action, executes when turn to this state
- `void set_exit(Functor&& functor)` - set action, executes when leaves this state

### FSM class methods
- `State add_state(Functor&& functor)` - add new state to fsm
- `void handle(FSM template object)` - handle input signal
- `void execute()` - execute action in current state
- `void set_current_state(State object)` - set current state in fsm, also use to set initial state
______________________________________________________________________________________
## UI
```cpp
#include "ConsoleGameEngine/source/UI/UI.h"
```

### Text
### Push button
### Horizontal layout
### Vertical layout
### Frame
______________________________________________________________________________________