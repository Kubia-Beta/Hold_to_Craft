/* This is an updated and more comprehensive AutoHotkey script that is not split into multiple files.
*  This script will allow you to hold down "e" or "d" for crafting in No Man's Sky.
*  The script compiler is included in the executable (.exe) automatically: https://www.autohotkey.com/docs/v2/Scripts.htm#ahk2exe
*  This means you do NOT have to download any version of AutoHotkey if you run the executable.
*  System icon provided by Corey Ginnivan https://www.systemuicons.com/images/icons/code.svg
*  
*  HOW TO USE:
*  This script starts active. 
*  Select the item you wish to craft or move your mouse over the item,
*  now press and hold "e" or "d" until you have the desired amount.
*  You can toggle this by pressing either F1 or by pressing CTRL+SHIFT+T. Two beeps will play to notify you it is off.
*  Turning it back on is just as simple. Using the same keys will re-activate the script. One beep will play to notify you it is on.
*  If you wish to exit the script, press F4 or CTRL+SHIFT+B.
*  
*  Script by KubiaBeta hosted on the Nexus under the name SkeithGaming https://www.nexusmods.com/nomanssky/mods/2478
*  26 Feb., 2023
*  
*  SCRIPT CONTROLS:
*  Toggle on/off: F1 or CTRL+SHIFT+T
*  Exit: F4 or CTRL+SHIFT+B
*  
*  If there are enough requests for it, I will work on a version that will do a one time setup for custom hotkeys.
*/

#Requires AutoHotkey >=v2.0- ;Run on 2.0, pre-release allowed. AHK v2 has quite a few improvements and is easier to read.

#SuspendExempt 1 ;Makes all the following function still work even if suspended until it sees #SuspendExpemt 0
^+t:: ;Toggle the script when CTRL+SHIFT+T is pressed,
F1:: ;OR when F1 is pressed.
{
   Suspend ;Toggles the program functionality that is not the two above keybinds or the exit function.
   currVolume := SoundGetVolume() ;Get the current MASTER volume
   moduloVolume := currVolume / 2 ;Divide it in half as SoundBeep is LOUD
   SoundSetVolume moduloVolume ;set the half volume to current MASTER volume temporarily
   if (A_IsSuspended = 1){ ;when turned off, beep TWICE
      SoundBeep ;523hz tone for 150ms
      SoundBeep
   } else { ;when turned on, beep ONCE
      SoundBeep
   }
   sleep 15 ;here so it doesn't fire faster than 15ms + time used by the code for safety
   SoundSetVolume currVolume ;restore the previous MASTER volume
}

;Exit function.
;Note that #SuspendExempt 1 applies as it has not been declared 0, so this will always run.
^+b:: ;Exit when CTRL+SHIFT+B is pressed
F4:: ;OR if F4 is pressed
{
SoundPlay "*64" ;play the system noise "Asterisk (info)" on exit
ExitApp ;Kill the script entirely
}

#SuspendExempt 0 ;All following functions DO NOT run when suspended (the point of suspending hotkeys)

; As long as the e key is held, send "e" repeatedly through this function:
$e:: ; Cash sign is used so the script does not trigger itself https://www.autohotkey.com/docs/v2/Hotkeys.htm
{
   While ( GetKeyState( "e","P" ) ) { ; As long as (while) the keystate of the key "e" is pressed
      Send "{e down}" ; Press the "e" key down
      Sleep 50 ; hold it down for 15ms
      Send "{e up}" ; release the key
      Sleep 50 ; delay so the loop will have the "e" key not being sent 100% of the time
   } 
Return
}

; As long as the d key is held, send "d" repeatedly, same as above:
$d:: 
{
   While ( GetKeyState( "d","P" ) ) { 
      Send "{d down}"
      Sleep 30
      Send "{d up}"
      Sleep 15
   } 
Return
}