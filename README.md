![GitHub release (latest by date)](https://img.shields.io/github/v/release/Kubia-Beta/Hold_to_Craft?style=plastic)

NMS v3.94 Demonstration: (Works on 4.1 "Fractal" and above)

https://user-images.githubusercontent.com/113896543/221608702-5e20d329-f8aa-4803-bbe8-866eb4f9f6d7.mp4


# Hold to Craft - No Strain Crafting Script

This is a simple compiled AutoHotkey script that will send the "e" or "d" key for crafting quickly as long as the key is held down. I made this script to prevent repetitive strain injury until Hello Games makes their crafting system less hostile to the player. Rather than attempt to buy a thousand iron plates from a station over the better part of an hour or spamming a key for just as long, this script allows the player to make that same amount of iron plates in under a minute.
## Installation

Simply go the [releases tab](https://github.com/Kubia-Beta/Hold_to_Craft/releases) to download the latest version (or [on the Nexus](https://www.nexusmods.com/nomanssky/mods/2478?tab=files)). Unzip it somewhere convenient for you, and for your first time setup launch Hold to Craft.exe before No Man's Sky to set your keybinds.
    
## Usage

To use the script, simply launch the executable file. It will start active, unless it is your first time using the script, where it will perform a one time setup where you can choose to have custom keybinds or the default F1/F4 keybinds. Any time afterward it will be active. Note that the script has a fallback where if it runs for 8 hours straight, it will exit. This is to prevent multiple instances of the script, or lingering scripts.

#### If at any time you forget your keybinds, simply open the active window of Hold to Craft.exe and it will display your keybinds.

_USE SCRIPT:_ Hold `E` or `D` depending on the menu context.

_TOGGLE SCRIPT:_ `F1` if you have default settings or `CTRL + SHIFT + T` (fallback hotkey)

_EXIT SCRIPT:_ `F4` if you have default settings or `CTRL + SHIFT + B`(fallback hotkey)
## FAQ

#### Do I need AutoHotkey?

No, not anymore. The executable comes with all necessary components.

#### How do I know if it is on or off?

Firstly, the script starts on, so if you just launched it, it is on. If you selected noise to be on, you will hear two beeps if you toggled the script OFF, and one beep if you toggle the script ON. Otherwise, trying to interact with any object with E will not be possible because the script will be pressing and releasing it, an indicator that the script is currently toggled on.

#### Can I change the hotkeys?

Yes! You have a few options. You can change them on the first time setup, which you can re-trigger if you exit the script and rename "htcprefs.ini" located in the "lib" folder to something like "htcprefs.ini.backup". If you want to directly edit htcprefs.ini, keep in mind that you will have to use the [AutoHotkey hotkey scheme](https://www.autohotkey.com/docs/v2/Hotkeys.htm#Symbols) which is very simple. If you wanted to change the pause key to `Alt+Ctrl+Shift+CapsLock`, you would open the ini, find the top of the file `[controls]` edit the keybind to `!^+capslock`, meaning the full line should now read `pause=!^+capslock`, then save. The new keybind will now work!

#### I found a bug!

Please report it on the [issue tracker](https://github.com/Kubia-Beta/Hold_to_Craft/issues)! If you cannot, at least post it on the [mod page bug tracker](https://www.nexusmods.com/nomanssky/mods/2478?tab=bugs)!

## Credits

 - [Icons provided by Corey Ginnivan](https://www.systemuicons.com/)
 - The #Mod-help channel of the [No Man's Sky Discord](https://discord.gg/22ZAU9H)

