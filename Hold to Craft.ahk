;;;;;;;;;;;;;;;;;;;;;;;;
;; By:              ;;;
;; Kubia           ;;;
;; 28 Feb. 2023   ;;;
;;;;;;;;;;;;;;;;;;;;

; Development test build

#Requires AutoHotkey >=v2.0- ;Run on 2.0, pre-release allowed. AHK v2 has quite a few improvements and is easier to read.

if not (file exists) { ;file does not exist
	DllCall("Keybinding.dll\Keybinding", "Cdecl") ; make it https://www.autohotkey.com/docs/v2/lib/DllCall.htm
}

iniread htcprefs.ini
pauseKey :=
exitKey :=
noise :=	;0 is off 1 is on

;then Hold to Craft

try
	Hotkey pauseKey, PauseFunc ; user hotkey for pause
catch TargetError
	MsgBox "The pause hotkey does not exist or it has no variant for the current If criteria."

try
	Hotkey exitKey, ExitApp ; user hotkey for exit
catch TargetError
	MsgBox "The exit hotkey does not exist or it has no variant for the current If criteria."


#SuspendExempt 1 ; Makes all the following function still work even if suspended until it sees #SuspendExempt 0
^+t::PauseFunc ; BACKUP HOTKEY: Toggle the script when CTRL+SHIFT+T is pressed,
PauseFunc(*)
{
	Suspend ; Toggles the program functionality that is not the two above keybinds or the exit function.
	if (noise = 1){ ; if the user turned sound ON
		currVolume := SoundGetVolume() ; Get the current MASTER volume
		moduloVolume := currVolume / 2 ; Divide it in half as SoundBeep is LOUD
		SoundSetVolume moduloVolume ; set the half volume to current MASTER volume temporarily
		
		if (A_IsSuspended = 1){ ; when turned off, beep TWICE
			SoundBeep ;523hz tone for 150ms
			SoundBeep
		} else { ; when turned on, beep ONCE
			SoundBeep
		}
		sleep 15 ; here so it doesn't fire faster than 15ms + time used by the code for safety
		SoundSetVolume currVolume ; restore the previous MASTER volume
	} ; end noise block
}

^+b:: ;BACKUP HOTKEY: Exit when CTRL+SHIFT+B is pressed
{
ExitApp ;Kill the script entirely
}


#SuspendExempt 0 ; All following functions DO NOT run when suspended (the point of suspending hotkeys)
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


