#define SDL_MAIN_HANDLED

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "engine.h"

void openDebugConsole() {
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
}

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	//openDebugConsole();

	Engine engine;
	engine.loop();

	return 0;
}

/*
Overview of how the object-component stuff work

	- Example object hierarchy:
		Object
			-> Entity
				-> UI
				-> Player/Enemy
				etc
			-> Zone
				-> Loading Zone
			-> Prop
				-> Effects
				-> Tooltip
				-> Particle
			etc
	- When creating objects, add new components into component vectors owned by a state
	  and then pass pointers of those to the objects.
	  This should ensure data locality when iterating through each type of component.

	Brief documentation on classes and member variables:
	(Classes are capitalized and variables aren't)

	- Object
		- current state (walking, shooting, etc)
		- messaging system to communicate between components
		- geometric data (position, size, rotation, etc)
		
		- Physics component
		  : Handles the overall movement of an object.

		- State component
		  : Handles the current state an object is in.
		    This affects a 'state' variable owned by the object itself,
			which in turn affects all other component that are based on its value.
			- functions to call upon state change (maybe just messages?)

		- Graphics component
		  : Handles all visual representation of an object.
		    update(ms) updates Source and Target,
			render(Renderer*) passes Source and Target data to Renderer's render().
			* An object would have a vector of Graphics components for every sprite required.

			- Source component
			  : Handles what sprite to use from a spritesheet image,
			    and its animation sequences.
				- texture data (SDL_Texture*)
				- texture box (to get a specific portion of a spritesheet)
				- animation sequences (for any visual sprite changes)
			- Target component
			  : Handles where to draw the sprite (position, size, rotation etc)
			    and its motion sequences.
				- motion sequences (for any movement within the object)
				- render-related boxes (relative to the object's position)
				- reference to the object's transform (to calculate the actual rendering box)
				- texture modifiers (hue, brightness, etc)

		- Collision component
		  : Contains all collision-related data of an object.
			* Collision checks should be done from outside entities or its components.

			- motion sequences (for any collision movement within the object)
			- collision data (bounding box, actual collision shape, etc)
			- callback data (maybe a map<colliding object type, message to send / function to call>)
			- object type? (idk not sure)

		- Input component
		  : Handles all incoming inputs and callbacks set to an object.
			- callback data (map<input action, function>)
			- current input state (input actions and its type value - check input_event.h)

	- Motion
	  : A sequence of a sprite's rendering data.
		- Motion Frame
			- pointer to a premade motion function?
			- function-related parameters
	- Animation
	  : A sequence of a sprite's texture data.
		- Animation Frame
			- box data
			- frame duration

	Overview of the game logic flow:
		- Process input
		- Update object graphics (source, target)
		- Check for collisions
			- Gather relevant collision data into a vector (collider, collidee)
			- Iterate through the vector and do stuff accordingly
		- Render entities
*/

/*
Stuff to do when I have my IDE at home:
	- fix all the existing syntax errors / inconsistencies
	  also whitespaces (tab / 4 spaces - use 4 space)

	- use CMake to build this project instead of Visual Studio,
	  so it becomes decoupled from VS for anyone who may not use it to code stuff.
	  Additionally, consider organizing this clutter of .h/.cpp files into folders because its gettin kinda messy

	- Fat reminder: Do not even think about making Lua modding support because I'm already frying my brain with everything
	  just hardcode every type of entity including their logic, maybe think about Lua on future projects

	- Check if the SDL2 polling system orders its events in a fixed order.
	  If so, 'Input::setInputDevicePriority' isn't needed and should be removed. 
*/

/*
Highly prioritized stuff I must do before I eventually meltdown:
	- Figure out how to initialize objects from an external json file
	  - Components with common data should be initialized from a file only once,
	    then be created with the copy constructor for every subsequent initialization.
	  - bruh idk

	- Implement a logging system for easier debugging

	- Animations are going to be loaded from a external file.
	  This includes each frame data (position / size / duration), and attributes (name and flags, etc).
	  Make sure to create documentation for how to format such files and properly implement them.

	- When implementing customizable keybinds, how should duplicate keys be handled?
		* If it's guaranteed that two key actions can not happen simultaneously,
		  then having duplicate keys shouldn't be a problem and may be allowed.
		  A category system for key actions would be required for this to be possible - think about this more later.

	- Text (fonts and text color) and sprites should be separated into their own classes, not within Graphics.

	- When handling time in states, search for a way that can ignore time being paused
	  -> just use delta time instead of raw timestamps lol dumbass

	- Implement attributes for sprites / entities / states
	  Notable examples I should add:
		- StateSpecific (object, Sprite) : used for resources specific to one state only (allows smooth state transitions if false)
		- Interactable (State) : false for cutscenes and whatnot
		- Paused (State) : self-explanatory

	- The currently implemented motion system only allows one motion to be active at a time,
	  but if it gets changed to allowing multiple options, then beware for potential problems that may arise
	  with non-linear calculations
*/

/*
Moderately important stuff to ponder upon like a sophisticated individual:
	- Add functions in classes such that all classes adhere to "the rule of fives".

	- Replace all #pragma onces with #ifndefs for IDE compatibility.

	- The current input system does not properly handle key presses that aren't used in the game.
	  i.e. pressing multiple of those may or may not trigger each PRESS_DOWN/ED/UP as one might expect.

	- How do I handle storing and rendering sprites without intertwining a bunch of headers and classes

	- Find a way to add game-specific key values without altering the enum class itself -
	  in other words, consider using a different method of storing valid keys (vectors or whatever, maybe create a custom class idk)
	  
	- Optimize collision checking
	
	- Look into instance rendering, apparently commonly used for drawing multiple of the same sprite
	  (e.g. particles)
*/

/*
Not-too-important small notes for the brainrot future me:
	- Should every component own an 'attribute' object?
	  On first thought yes, but this might result in mixed 'active' flag values within highly-coupled components.. idk

	- sprites, animations, and audio channels will be stored in a single 'Resources' class object owned by the StateController.
	  this is to reduce duplicate data and coupling between components and various game objects.
	  to prevent accidental destructions of an object still in use (eg. animation used by multiple GameObjects),
	  consider using shared_ptr or weak_ptr within components.

	- Create audio effect systems.. if I need it idk

	- BPM should be handled by a music-specific class object, not Channels or whatever.

	- When checking for collision of an object, consider overloading a single collision-checking function
	  with all possible targets - a single point (mouse cursor), a line, convex/concave shapes, etc.
*/

/*
Naming-related stuff to remind myself because I have dementia:

	- Bool flag variables:
		- Use adjectives that describes whatever status you're trying to keep track of.
		  Avoid using nouns unless you really can't think of an alternative.
		  ex) "visible" instead of "visibility"

	- Use "box" instead of "rect", just because the word 'hitbox' exists.
	
	- Time related variables:
		- Use "delta" if it refers to the difference of two timepoints of the past.
		  Use "elapsed" if it refers to the difference between the current and the past.
		- For beginnings or ends of a time frame, use "start" or "end".
		- Use "duration" if it refers to how much time something takes.
	
	- Use "local" and "global" for two types of variables with the same functionality, but different domains.
	  ex) vertices in hitbox.h
*/