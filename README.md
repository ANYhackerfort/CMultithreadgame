
# Elden Ring Style Open World Game

Project by: Matthew Zhang & Tony Li

## Objective
The objective is to create an Elden Ring open-world Adventure game. This game has **10 maps (or floors)**, and each floor has **9 squares (different parts of each map)**.

- The user can teleport (`/map`) to any floor even while completing a square in that floor. However, **once you leave**, the square of the map you were on gets **reset** (like an Elden Ring boss).
- Squares that you beat **get saved**, so users can skip through beaten areas of the map to access other parts.
- **Progress is stored** in 10 floor objects. However, if you **die, YOU LOSE EVERYTHING.**
- Read more to learn the quirk of teleportation.

> [!Note]
> Quirks about teleportation, the fun part!
>## Teleportation
>- Users can always use `/map` to get all the floors they can travel to.
>- Once you enter the code, you can teleport there (like an Elden Ring map).
>- However, the position of the floor you teleport to will be the **same as your position on the current floor** (meaning you can only teleport up!).
>  **Example:** If you are in position `(2,1)` on the current map, teleporting to another map will still put you at `(2,1)`.
> This mechanic adds strategy, requiring careful planning to teleport from specific squares to reach the boss squares you want to fight. 

> [!Important]
> ## Limitation on Movements
> - To move to an unbeaten square, one of the connecting squares in the 4 directions must be beat.
> - This limits your movements in each floor so you can't just teleport up from anywhere.

## Other Commands
- Use /stats to check your completed squares and other stats.
- Use /i to view your inventory.
- - Add name after /i to sort the inventory by name.
- - Add count after /i to sort the inventory by count.
- Use /map to view the map
- movenorth, movewest, movesouth, moveeast to navigate inside each floor or map.

## Rules
- Once you lose all your health, **all progress is lost** at that square, and you have to start over.
- Items are **rare**, but once you find them, you can use them to skip past attacks.
- If you decide to move away to another square, **all progress is lost**. That’s the **challenging part**!
- Once you beat a square, the number of squares beaten is incremented.
  - **You cannot try to beat the square again!**

## How to Win
- You only need to complete **10 squares across the 10 maps**. You can choose any combination of maps and squares.
- But beware: **once you lose all your health, GAME OVER. EVERYTHING RESETS!**
> [!NOTE]
> There will be items such as health potions and apples to help you!

## Acknowledgments
This project was written entirely by us while referring to:
- Slides and past coding assignments
- Resources such as Stack Overflow for debugging (e.g., `std::shared_ptr` race conditions)
- WS2 School, which helped explain template classes
- Stack Overflow for resolving common Makefile errors (e.g., `.h files should not be compiled individually into .o files`)

## Topics Used

> [!NOTE]
> These are just some ways we used the general topics. We also used topics outside of this list covered in the course such as threads, object slicing, etc... 

### General Topics
1. **Standard Containers:**
   - Used throughout all the classes to store information of various types.
   Example:
   - Our custom hash map relies on `std::vector` and `std::list`. Our maps are stored in a `std::unordered_map`.
   - `std::swap` used to swap elements in our custom hashmap.

2. **Custom Template Class:**
   - The `inventory` is a custom template class used to store the player’s inventory.
   - The inventory is a hashmap that stores the actual object node instance of each item, along with its name and quantity. This design avoids frequent deletion and recreation of objects by maintaining a single instance per unique item. When items are removed, only the quantity is decremented; efficient inventory management.

3. **Custom Namespace:**
   - `Util` is a custom namespace that includes a template quicksort function.

4. **Classes with Constructor, Destructor, and Assignment Operator:**
   - The `gameItem` class implements all three.
   - The `inventory` class implements all three with an assignment operator to make a deep copy of player's inventory. 
   - Other classes have a constructor and destructor (free memory) but rely on the default assignment operator (because we never use the assignment operator for those classes (defeats our purpose)).

5. **Lambda Functions:**
   - Used for the loading screen animation / other inline functions to make code neater. 
   - Also used in sorting (via quicksort) to specify sort by object class properties like count and name. Lambda function help determine how an object is greater or less. 

6. **Exception Handling:**
   - Exception throws and catches ensure valid user inputs.
   - Includes nested exception throws to handle out-of-player-scope errors.

7. **Inheritance:**
   - `BaseMap` inherits from `AdventureGame`.
   - Each topic class inherits from `BaseMap`, promoting code reusability and reducing redundancy.
   - Each `gameItem` for example `apple` inherits from `gameItem` for the effects on the player. 
   - Shared pointers are used to stores items in nodes in inventory so memory slicing doesn't happen. 

8. **Virtual Functions or Abstract Classes:**
   - A lot of virtual functions are used so I could store items in a baseclass instead ofa derived class to better manage them by having them all be uniform.  
   - EX: `handleCurrentSquare()` in the `BaseMap` class is virtual so can call different implemenations for handling each square could be called through the base class.
   - All relevant destructors are virtual.

9. **Hashing:**
   - The inventory is a custom hash table with chaining (not probing) using `std::hash`.
   - We also have all custom implementation for storing and deleting elements;
   - Custom implementation for displaying elements of the custom hashmap. 

10. **Sorting Algorithms:**
   - Players can sort inventory items by **name** or **count**.
   - Implemented with quicksort for efficient average-case time complexity. 
   - The quick sort function works with a lot of types, and lambda function is there to handle sorting node objects based on specific attributes. 

## Challenges Encountered

### Hardships While Making This Project:
- **Threading:** There was a race condition in reading what the user has written into the console if I have multiple threads listening to what's written in the console or writing into the console. It is recommended to just have 1 thread handling the console (what we did); however, it also could be implemented with storing user inputs in a quene and mutex locking it when one of the thread is accessing it. 
- **Inheritance:** Inheritance is difficult to change after implementation, need a clear line of action before starting to code. What objects should have what focusing on meeting the feature first, then speed, then readaiblity / resusability. Clear inheritance was definetly a challenge in explaining to each other what we have each implemented so we could merge our logic together. 
- **Makefile Issues:** You can not compile .h files, it's just gets compiled with whatever file includes them. That's why you should also attach .h files to the .o file that it is dependant on so make could know the dependency chain and automatically update .o file based on the changed .h files. 
- **Template Classes:** Really hard to work with. Each time you use template parameter T, it is not automatically recognized outside the template's original declaration; assumed to be not used outside the class definition. 
- **Composition:** Was a hassle in determing with objects should have which (next time we are to plan this before coding to save time debugging afterwards). It was also hard to figure out which objects are saved throughout the game and which ones are to be deleted when we get out of the scope (such as a level ending). Reference vs. just a direct copy. 
- **Time Constraints:** Limited time to debug a big project like this with multiple components. 

### Specific Bugs for the Exam:
1. **Slicing:**
   - Passing `GameItem&` to `addItem` caused slicing, chopping off derived class properties.
   - Solution: Always pass **shared pointers** when polymorphism is involved.
   - Template T deduces the derived class and so does the auto key word. 

2. **Function Signatures:**
   - Ensure function signatures match the types your classes expect.

