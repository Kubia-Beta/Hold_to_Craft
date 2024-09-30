;HkGui := Gui()
;HkGui.Add("Text", "xm", "Prefix key:")
;HkGui.Add("Edit", "yp x100 w100 vPrefix", "Space")
;HkGui.Add("Text", "xm", "Suffix hotkey:")
;HkGui.Add("Edit", "yp x100 w100 vSuffix", "f & j")
;HkGui.Add("Button", "Default", "Register").OnEvent("Click", RegisterHotkey)
;HkGui.OnEvent("Close", (*) => ExitApp())
;HkGui.OnEvent("Escape", (*) => ExitApp())
;HkGui.Show()
;
;RegisterHotkey(*)
;{
;    Saved := HkGui.Submit(false)
;    HotIf (*) => GetKeyState(Saved.Prefix)
;    Hotkey Saved.Suffix, (ThisHotkey) => MsgBox(ThisHotkey)
;}
;#Requires AutoHotkey >=v2.0-
;#NoTrayIcon
;SetTimer Killswitch8h, 28800000 ; Kills the program if it has been running for 8 hours

;MsgBox "Ran"
;sleep 30000
;MsgBox "also ran" ;will never run!
;sleep 1000
;ExitApp()

;someHotkey := "!\" ; you can assign it any arbitrary shit as long as it is in ahk language basically
; ex. "space", "^+t", "+space", "capslock", "pgdn", "+[", "!\"

;hotkey someHotkey, Killswitch8h



;Killswitch8h(*){ ; 28800000 is 8 hours, 21600000 is 6 hours
;msgbox "exiting"
;ExitApp
;}


F1::
InputBox, name, Input name dialogue, Please enter your name, ,750, 378, , , locale, 10
msgbox, your name is %name%
return

