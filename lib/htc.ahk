;;;;;;;;;;;;;;;;;;;;;;;;
;; By:              ;;;
;; Kubia           ;;;
;; 28 Feb. 2023   ;;;
;;;;;;;;;;;;;;;;;;;;

#Requires AutoHotkey >=v2.0-
#NoTrayIcon
#SuspendExempt 1 ; Makes all the following function still work even if suspended until it sees #SuspendExempt 0

pauseKey := iniread("htcprefs.ini","controls","pause")
exitKey :=iniread("htcprefs.ini","controls","exit")
noise :=	iniread("htcprefs.ini","sound","noise") ; 0 is off 1 is on

; then Hold to Craft

try
	Hotkey pauseKey, PauseFunc, "S" ; user hotkey for pause
catch TargetError
	MsgBox "The pause hotkey does not exist or it has no variant for the current If criteria."

try
	Hotkey exitKey, exitFunc, "S" ; user hotkey for exit
catch TargetError
	MsgBox "The exit hotkey does not exist or it has no variant for the current If criteria."


SetTimer Killswitch8h, 28800000 ; Kills the program if it has been running for 8 hours

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
ExitApp "0" ;Kill the script entirely
}

exitFunc(*){ ;for some reason if I don't define the func and the hotkey it has a fit unlike PauseFunc
ExitApp "1"
}


; this exists in case of an incorrect termination. After 8 hours, it will exit
Killswitch8h(*){ ; 28800000 is 8 hours, 21600000 is 6 hours
ExitApp "0"
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


