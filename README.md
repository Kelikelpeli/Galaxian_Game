# Galaxian Game

## Description

This project involves creating a simplified version of the arcade video game **Galaxian**, using the **Raylib** library and an object-oriented architecture in **C++**. The goal is to recreate the classic gameplay of the game while implementing visual and sound improvements for a more engaging gaming experience.

## Running the Game

To run the `.exe` file of the game outside of Visual Studio, make sure that the resources (images, sounds, textures) are in the same relative directory as the executable, as they are necessary for the correct functioning of the game. You can find the executables in the `bin` folder (both in Debug and Release mode).

## Instructions to Play

- **Left/Right Arrows**: Move the ship.
- **Space**: Shoot projectiles.
- **R**: Restart the game after it ends.

## Project Structure

- **`Game` Folder**: Contains the main classes of the game, such as `Player`, `Enemy`, and `EnemyManager`. These classes are responsible for managing the logic and behavior of the game.
- **`Menu` Folder**: Includes the scripts for the menu screens, such as the title screen, options, and the end game screen.

## Implemented Features

- Screen navigation (LOGO, TITLE, GAMEPLAY, ENDING).
- Player movement and shooting.
- Enemies with random movement and shooting.
- Scoring and lives system.

## Additional Improvements

1. **Sound and Effects**: Added sound effects for both shooting and collisions, making the gaming experience more immersive. Background music was also implemented for the different phases of the game (menu and gameplay).
2. **Automatic Restart Screen**: At the end of the game, an option was added to automatically return to the title screen and allow the player to start a new game by pressing 'R'.
3. **Ending Animation**: An additional animation was implemented for the "GAME OVER" and "WIN" letters, giving a more dynamic look to the end of the game.

## References

- **Galaxia Technologies Logo**. Retrieved from: [https://cdn.dribbble.com/users/2594111/screenshots/14146404/tech_logo_-_galaxia_technologies_4x.jpg](https://cdn.dribbble.com/users/2594111/screenshots/14146404/tech_logo_-_galaxia_technologies_4x.jpg)
- **Arcadepix Plus Font**. Retrieved from: [https://www.dafont.com/es/arcadepix-plus.font](https://www.dafont.com/es/arcadepix-plus.font)
- **Glipervelz Font**. Retrieved from: [https://www.dafont.com/es/glipervelz.font](https://www.dafont.com/es/glipervelz.font)
- **Game Over Sound**. Retrieved from: [https://opengameart.org/content/game-over-soundold-school](https://opengameart.org/content/game-over-soundold-school)
- **Win Jingle**. Retrieved from: [https://opengameart.org/content/win-jingle](https://opengameart.org/content/win-jingle)
- **Blackmoor Tides: Epic Pirate Battle Theme**. Retrieved from: [https://opengameart.org/content/blackmoor-tides-epic-pirate-battle-theme](https://opengameart.org/content/blackmoor-tides-epic-pirate-battle-theme)
- **Sound, Image, and Texture Resources**: Material provided by the professor through the ZIP file GalaxianInitialSourceAndResources.zip

## Credits

Developed by: **Raquel López Barceló**