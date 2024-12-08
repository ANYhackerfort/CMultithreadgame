
# Elden Ring Style Open World Game

Project by: Matthew Zhang & Tony Li

## Objective
The objective is to create an Elden Ring open-world game. This game has **10 maps (or areas)**, and each area has **9 squares (different parts of each map)**.

- The user can teleport (`/map`) to any map even while completing a square. However, **once you leave**, the square of the map you were on gets **reset** (like an Elden Ring boss).
- Squares that you beat **get saved**, so users can skip through beaten areas of the map to access other parts.
- **Progress is stored** in 10 map objects. However, if you **die, YOU LOSE EVERYTHING.**
- Read more to learn the quirk of teleportation.

> [!Note]
> Quirks about teleportation, the fun part!
>## Teleportation
>- Users can always use `/map` to get all the maps they can travel to.
>- Once you enter the code, you can teleport there (like an Elden Ring map).
>- However, the position you teleport to will be the **same as your position on the current map**.
>  **Example:** If you are in position `(2,1)` on the current map, teleporting to another map will still put you at `(2,1)`.
>- This limits your movement because you **must beat what’s on the current square** before progressing.

## Other Commands
- When traveling with an animation, you are **hinted at commands** to check your health and items in your inventory.

## Rules
- Once you lose all your health, **all progress is lost** at that square, and you have to start over.
- Items are **rare**, but once you find them, you can use them to skip past attacks.
- If you decide to move away to another square, **all progress is lost**. That’s the **challenging part**!
- Once you beat a square, the number of squares beaten is incremented.
  - **You cannot try to beat the square again!**

## How to Win
- Complete **10 squares across the 10 maps**. You can choose any combination of maps and squares.
- But beware: **once you lose all your health, GAME OVER. EVERYTHING RESETS!**

## Acknowledgments
This project was written entirely by us while referring to:
- Slides and past coding assignments
- Resources such as Stack Overflow for debugging (e.g., `std::shared_ptr` race conditions)
- WS2 School, which helped explain template classes
- Stack Overflow for resolving common Makefile errors (e.g., `.h files should not be compiled individually into .o files`)

## Topics Used

### General Topics
1. **Standard Containers:**
   - Used throughout all the classes to store information of various types.
   - Example: Our custom hash map relies on `std::vector` and `std::list`.

2. **Custom Template Class:**
   - The `inventory` is a custom template class used to store the player’s inventory.

3. **Custom Namespace:**
   - `Util` is a custom namespace that includes a template quicksort function.

4. **Classes with Constructor, Destructor, and Assignment Operator:**
   - The `gameItem` class implements all three.
   - Other classes have a constructor and destructor but rely on the default assignment operator.

5. **Lambda Functions:**
   - Used for the loading screen animation.
   - Also used in sorting (via quicksort) to sort by object class properties like count and name.

6. **Exception Handling:**
   - Exception throws and catches ensure valid user inputs.
   - Includes nested exception throws to handle out-of-scope errors.

7. **Inheritance:**
   - `BaseMap` inherits from `AdventureGame`.
   - Each topic class inherits from `BaseMap`, promoting code reusability and reducing redundancy.

8. **Virtual Functions or Abstract Classes:**
   - `handleCurrentSquare()` in the `BaseMap` class is virtual.
   - All relevant destructors are virtual.

9. **Hashing:**
   - The inventory is a custom hash table with chaining (not probing) using `std::hash`.

10. **Sorting Algorithms:**
   - Players can sort inventory items by **name** or **count**.
   - Implemented with quicksort for efficient average-case time complexity.

### File-Specific Details

#### game.cpp / adventuregame.cpp / basegame.cpp / topic1.cpp / topic2.cpp, etc.:
- **Topics Used:**
  - 4. `loadMaps` initializes all maps; `deleteMaps` deletes all maps.
  - 5. `displayAnimation` in `handleMapSelection` uses a lambda function.
  - 6. Exception handling is extensively used for managing invalid user inputs.
  - 7. Topic classes (e.g., `Topic1`, `Topic2`) inherit from the `BaseMap` class.
  - 8. Virtual functions are implemented in `BaseMap.cpp` and `MainGame.cpp`.

#### inventory.h:
- **Topics Used:**
  - 1. Heavily utilizes `std::vector` and `std::list`.
  - 2. The class itself is a custom template class.
  - 4. Constructor is defined.
  - 9. Hashing is explicitly implemented in the `hashFunction` method, which uses `std::hash`.

#### sort.h:
- **Topics Used:**
  - 1. `std::vector` is central to the sorting algorithm.
  - 2. Implements a custom template class (ish).
  - 3. `Util` is a custom namespace.
  - 10. Quicksort is implemented here.

#### gameItem.h:
- **Topics Used:**
  - 4. Implements Constructor, Destructor, and Assignment Operator.
  - 7. Items inherit from the `GameItem` class.

## Challenges Encountered

### Hardships While Making This Project:
- **Template Classes:** Really hard to work with.
- **Threading:** Proper use of threading was challenging.
- **Inheritance:** Scuffed inheritance is difficult to change after implementation.
- **Git Issues:** Frequent merge/pull/branch/update issues.
- **Makefile Issues:** Numerous errors to debug.
- **Time Constraints:** Limited time to finish everything.

### Specific Bugs for the Exam:
1. **Slicing:**
   - Passing `GameItem&` to `addItem` caused slicing, chopping off derived class properties.
   - Solution: Always pass **shared pointers** when polymorphism is involved.

2. **Function Signatures:**
   - Ensure function signatures match the types your classes expect.

