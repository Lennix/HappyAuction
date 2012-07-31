#region COMMENTS
;socket infos abfragen (optional), dps/armor in lua via found abfragen
;cancel um edit wieder zu verlassen
#endregion
#region INCLUDES
#include <GUIConstantsEx.au3>
#include <GuiComboBox.au3>
#include <SliderConstants.au3>
#Include <GuiSlider.au3>
#include <WinAPI.au3>
#endregion
#region OPT
Opt("GUIOnEventMode", 1)
#endregion
#region VARIABLES
#region VARIABLES GLOBAL
;controls
Global $mainList = ""
Global $mainGUI = ""
Global $inputGUI = ""
Global $mainDropDown = ""
Global $mainSlider = ""
Global $mainSliderCache = ""
Global $mainInput = ""
Global $addButton = ""
Global $createButton = ""
Global $editButton = ""
Global $deleteButton = ""

;control holder
Global $profileCounter = "0"
Global $editingProfile = "-1"
Global $sliderStartValue = "800"
Global $startPageDelay = "0"

;arrays
Global $formData[19] = ["", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""]
Global $filterData[6][2] = [["", ""], ["", ""], ["", ""], ["", ""], ["", ""], ["", ""]]

;other
Global $lua_tab_count = 0
#endregion
#region VARIABLES CONST
;files
Const $Ini = "Profiles.ini"
Const $Txt = "Profiles.txt"

;color
Const $colorRED = 0xF20041
Const $colorGREEN = 0x0D8B1A
Const $colorSTANDARD = 0xffffff

;other
Const $queryZoneValue = 900
Const $error = "ERROR"
Const $guiInputX = 100
#endregion
#endregion
#region CORE
#region CORE START
checkIniFile()
builtMainGUI()
#endregion
#region CORE LOOP
While 1
	;manipulate
	manipulateInput()
	;update main values
	checkMainInput()
	;delay
    Sleep(100)
WEnd
#endregion
#region CORE FUNCTIONS
Func quit()
	Exit
EndFunc
#endregion
#endregion
#region GUI
Func paintGUI($control, $bool = True)
	If $bool Then
		GUICtrlSetBkColor($control, $colorSTANDARD)
	Else
		GUICtrlSetBkColor($control, $colorRED)
	EndIf
EndFunc
#region GUI MAIN
;main gui
Func builtMainGUI()
	$mainGUI = GUICreate("ProfileAssembler - Z ©2012 Zero", 300, 130)
	builtMainLayers()
	GUISetState(@SW_SHOW, $mainGUI)
	GUISetOnEvent($GUI_EVENT_CLOSE, "quit", $mainGUI)
EndFunc

Func builtMainLayers()
	;profile dropdown line
	GUICtrlCreateLabel("Profile", 10, 18)
	$mainDropDown = GUICtrlCreateCombo("", 76, 15, 166, 20)
	GUICtrlSetData($mainDropDown, $mainList)
	GUICtrlSetOnEvent($mainDropDown, "loadProfile")
	;add button line
	$addButton = GUICtrlCreateButton("+", 256, 12, 30, 26)
	GUICtrlSetOnEvent($addButton, "createProfileGUI")
	;pagedelay line
	GUICtrlCreateLabel("PageDelay", 10, 58)
	$mainInput = GUICtrlCreateInput($startPageDelay, 76, 55, 166, 20)
	GUICtrlCreateLabel("ms", 255, 58)
	;queries/h line
	GUICtrlCreateLabel("Queries / h", 10, 95)
	$mainSlider = GUICtrlCreateSlider(70, 92, 180, 50, BitOR($TBS_TOOLTIPS, $TBS_BOTTOM, $TBS_ENABLESELRANGE))
	GUICtrlSetLimit($mainSlider, 1600, 0)
	GUICtrlSetData($mainSlider, $sliderStartValue)
	Local $tempTicks[5] = [0, 400, 800, 1200, 1600]
	_GUICtrlSlider_ClearTics($mainSlider)
	For $i = 0 To UBound($tempTicks) - 1
		_GUICtrlSlider_SetTic($mainSlider, $tempTicks[$i])
	Next
	$mainSliderCache = GUICtrlCreateLabel($sliderStartValue, 257, 95, 30)
	If  $sliderStartValue == 0 Or $sliderStartValue > $queryZoneValue Then
		GUICtrlSetColor($mainSliderCache, $colorRED)
	Else
		GUICtrlSetColor($mainSliderCache, $colorGREEN)
	EndIf
EndFunc

Func switchToMainGUI()
	GUIDelete($inputGUI)
	GUISetState(@SW_SHOW, $mainGUI)
EndFunc
#endregion
#region GUI INPUT
Func builtInputGUI()
	GUISetState(@SW_HIDE, $mainGUI)
	$inputGUI = GUICreate("ProfileAssembler - Z ©2012 Zero", 350, 580)
	builtInputLayers()
	GUISetState(@SW_SHOW, $inputGUI)
	GUISetOnEvent($GUI_EVENT_CLOSE, "switchToMainGUI", $inputGUI)
EndFunc

Func builtInputLayers()
	;filtername line
	GUICtrlCreateLabel("ProfileName", 10, 18)
	$formData[0] = GUICtrlCreateInput("", $guiInputX, 15, 200, 20)
	;class line
	$classList = "Barbarian|Demon Hunter|Monk|Witch Doctor|Wizard"
	GUICtrlCreateLabel("Class", 10, 48)
	$formData[1] = GUICtrlCreateCombo("", $guiInputX, 45, 200, 20)
	GUICtrlSetData($formData[1], $classList)
	;itemtype line
	$itemtypeList = "1-Hand|2-Hand|Off-Hand|Armor|Follower Special"
	GUICtrlCreateLabel("ItemType", 10, 78)
	$formData[2] = GUICtrlCreateCombo("", $guiInputX, 75, 200, 20)
	GUICtrlSetData($formData[2], $itemtypeList)
	GUICtrlSetOnEvent($formData[2], "checkItemtype")
	;subtype line
	GUICtrlCreateLabel("SubType", 10, 108)
	$formData[3] = GUICtrlCreateCombo("", $guiInputX, 105, 200, 20)
	;rarity line
	$rarityList = "All|Inferior|Normal|Superior|Magic|Rare|Legendary"
	GUICtrlCreateLabel("Rarity", 10, 138)
	$formData[4] = GUICtrlCreateCombo("", $guiInputX, 135, 200, 20)
	GUICtrlSetData($formData[4], $rarityList)
	;filter
	GUICtrlCreateLabel("Filter", 10, 168)
	GUICtrlCreateTab($guiInputX, 165, 200, 50)
	$startTab = ""
	For $i = 1 To 6
		If $i == 1 Then
			$startTab = GUICtrlCreateTabItem($i)
		Else
			GUICtrlCreateTabItem($i)
		EndIf
		$filterData[$i - 1][0] = GUICtrlCreateInput("stat", $guiInputX + 7, 190, 140, 20)
		$filterData[$i - 1][1] = GUICtrlCreateInput("0", $guiInputX + 155, 190, 35, 20)
	Next
	GUICtrlCreateTabItem("")
	GUICtrlSetState($startTab, $GUI_SHOW)
	;price line
	GUICtrlCreateLabel("Price", 10, 228)
	$formData[5] = GUICtrlCreateInput("0", $guiInputX, 225, 150, 20)
	;bid line
	GUICtrlCreateLabel("Bid", 10, 258)
	$formData[6] = GUICtrlCreateInput("0", $guiInputX, 255, 200, 20)
	;buyout line
	GUICtrlCreateLabel("Buyout", 10, 288)
	$formData[7] = GUICtrlCreateInput("0", $guiInputX, 285, 200, 20)
	;random checkbox line
	$formData[8] = GUICtrlCreateCheckbox("Random", $guiInputX + 165, 225, 55, 20)
	;start gold line
	GUICtrlCreateLabel("StartGold", 10, 318)
	$formData[9] = GUICtrlCreateInput("0", $guiInputX, 315, 200, 20)
	;timeleft line
	GUICtrlCreateLabel("Timeleft", 10, 348)
	$formData[10] = GUICtrlCreateInput("d:hh:mm", $guiInputX, 345, 200, 20)
	;min lvl, max lvl line
	GUICtrlCreateLabel("min Lvl", 10, 378)
	$formData[11] = GUICtrlCreateInput("1", $guiInputX, 375, 60, 20)
	GUICtrlCreateLabel("max Lvl", $guiInputX + 80, 378)
	$formData[12] = GUICtrlCreateInput("60", 240, 375, 60, 20)
	;dps/armor line
	GUICtrlCreateLabel("DPS / Armor", 10, 408)
	$formData[13] = GUICtrlCreateInput("0", $guiInputX, 405, 200, 20)
	;Legendary/Set line
	GUICtrlCreateLabel("Legendary / Set", 10, 438)
	$formData[14] = GUICtrlCreateInput("", $guiInputX, 435, 200, 20)
	;query/h line
	GUICtrlCreateLabel("Queries / h", 10, 498)
	$formData[15] = GUICtrlCreateSlider($guiInputX, 495, 200, 50, BitOR($TBS_TOOLTIPS, $TBS_BOTTOM, $TBS_ENABLESELRANGE))
	GUICtrlSetLimit($formData[15], 1600, 0)
	GUICtrlSetData($formData[15], GUICtrlRead($mainSlider))
	Local $tempTicks[5] = [0, 400, 800, 1200, 1600]
	_GUICtrlSlider_ClearTics($formData[15])
	For $i = 0 To UBound($tempTicks) - 1
		_GUICtrlSlider_SetTic($formData[15], $tempTicks[$i])
	Next
	$formData[16] = GUICtrlCreateLabel(GUICtrlRead($mainSlider), $guiInputX + 207, 498, 30)
	If  GUICtrlRead($mainSlider) == 0 Or GUICtrlRead($mainSlider) > $queryZoneValue Then
		GUICtrlSetColor($formData[16], $colorRED)
	Else
		GUICtrlSetColor($formData[16], $colorGREEN)
	EndIf
	;itemlevel line
	GUICtrlCreateLabel("ItemLevel", 10, 468)
	$formData[17] = GUICtrlCreateInput("0", $guiInputX, 465, 200, 20)
	;log line
	$formData[18] = GUICtrlCreateCheckbox("Log", 300, 540, 55, 20)
EndFunc

Func builtCreateButton()
	$createButton = GUICtrlCreateButton("Create", 125, 535, 100, 30)
	GUICtrlSetOnEvent($createButton, "proceedCreatingProfile")
EndFunc

Func builtEditButton()
	$editButton = GUICtrlCreateButton("Edit", 65, 535, 100, 30)
	GUICtrlSetOnEvent($editButton, "proceedEditingProfile")
EndFunc

Func builtDeleteButton()
	$deleteButton = GUICtrlCreateButton("Delete", 185, 535, 100, 30)
	GUICtrlSetOnEvent($deleteButton, "proceedDeletingProfile")
EndFunc

Func checkItemtype()
	$subtypeList = ""
	$subtypeList1hand = "All|Axe|Ceremonial Knife|Hand Crossbow|Dagger|Fist Weapon|Mace|Mighty Weapon|Spear|Sword|Wand"
	$subtypeList2hand = "All|Two-Handed Axe|Bow|Daibo|Crossbow|Two-Handed Mace|Two-Handed Mighty Weapon|Polearm|Staff|Two-Handed Sword"
	$subtypeListOffhand = "All|Mojo|Source|Quiver|Shield"
	$subtypeListFollower = "All|Enchantress Focus|Scoundrel Token|Templar Relic"
	$subtypeListArmor = "All|Amulet|Belt|Boots|Bracers|Chest|Cloak|Gloves|Helm|Pants|Mighty Belt|Ring|Shoulders|Spirit Stone|Voodoo Mask|Wizard Hat"
	Switch GUICtrlRead($formData[2])
		Case "1-Hand"
			$subtypeList = $subtypeList1hand
		Case "2-Hand"
			$subtypeList = $subtypeList2hand
		Case "Off-Hand"
			$subtypeList = $subtypeListOffhand
		Case "Armor"
			$subtypeList = $subtypeListArmor
		Case "Follower Special"
			$subtypeList = $subtypeListFollower
	EndSwitch
	_GUICtrlComboBox_ResetContent($formData[3])
	GUICtrlSetData($formData[3], $subtypeList)
EndFunc

Func createProfileGUI()
	builtInputGUI()
	builtCreateButton()
	$editingProfile = -1
EndFunc

Func editProfileGUI()
	builtInputGUI()
	builtEditButton()
	builtDeleteButton()
EndFunc
#endregion
#endregion
#region INI
Func loadIni()
	$profileCounter = IniRead($Ini, "main", "profilecounter", $error)
	Local $arrayProfiles[$profileCounter]
	For $i = 0 To UBound($arrayProfiles)-1
		Local $arrayData[17]
		Local $arrayFilter[2]
		Local $arrayStat[7]
		Local $arrayValue[7]
		$fcount = 0
		For $t = 1 To 6
			$arrayStat[$t] = IniRead($Ini, "profile" & $i, "filter" & $t, $error)
			If $arrayStat[$t] <> $error And $arrayStat[$t] <> "stat" Then $fcount += 1
			$arrayValue[$t] = IniRead($Ini, "profile" & $i, "value" & $t, $error)
		Next
		$arrayStat[0] = $fcount
		$arrayFilter[0] = $arrayStat
		$arrayFilter[1] = $arrayValue
		$arrayData[0] = $arrayFilter
		$arrayData[1] = IniRead($Ini, "profile" & $i, "name", $error)
		$arrayData[2] = IniRead($Ini, "profile" & $i, "class", $error)
		$arrayData[3] = IniRead($Ini, "profile" & $i, "itemtype", $error)
		$arrayData[4] = IniRead($Ini, "profile" & $i, "subtype", $error)
		$arrayData[5] = IniRead($Ini, "profile" & $i, "rarity", $error)
		$arrayData[6] = IniRead($Ini, "profile" & $i, "price", $error)
		$arrayData[7] = IniRead($Ini, "profile" & $i, "bid", $error)
		$arrayData[8] = IniRead($Ini, "profile" & $i, "buyout", $error)
		$arrayData[9] = IniRead($Ini, "profile" & $i, "priceflag", $error)
		$arrayData[10] = IniRead($Ini, "profile" & $i, "startgold", $error)
		$arrayData[11] = IniRead($Ini, "profile" & $i, "logflag", $error)
		$arrayData[12] = IniRead($Ini, "profile" & $i, "dpsarmor", $error)
		$arrayData[13] = IniRead($Ini, "profile" & $i, "itemlevel", 1) ; NOT AVAILABLE YET SET 1
		$arrayData[14] = IniRead($Ini, "profile" & $i, "legendaryset", $error)
		$arrayData[15] = IniRead($Ini, "profile" & $i, "minlvl", $error)
		$arrayData[16] = IniRead($Ini, "profile" & $i, "maxlvl", $error)
		$arrayProfiles[$i] = $arrayData
	Next
	Return $arrayProfiles
EndFunc

Func checkIniFile()
	If FileExists($Ini) Then
		;load main profilecounter
		$profileCounter = IniRead($Ini, "main", "profilecounter", $error)
		;load main slider value
		$sliderStartValue = IniRead($Ini, "main", "queries", $error)
		;load main page delay
		$startPageDelay = IniRead($Ini, "main", "pagedelay", $error)
		;load main dropdown data
		For $i = 0 To $profileCounter - 1
			$tempProfile = IniRead($Ini, "profile" & $i, "name", $error)
			$mainList &= "|" & $tempProfile
		Next
	Else
		;create main profilecounter
		IniWrite($Ini, "main", "profilecounter", $profileCounter)
		;create main slider value
		IniWrite($Ini, "main", "queries", $sliderStartValue)
		;create main page delay
		IniWrite($Ini, "main", "pagedelay", $startPageDelay)
	EndIf
EndFunc

Func proceedCreatingProfile()
	$catchedERROR = checkInput()
	If Not $catchedERROR Then
		writeProfile($profileCounter)
		convertProfilesToLua()
	EndIf
EndFunc

Func proceedEditingProfile()
	$catchedERROR = checkInput()
	If Not $catchedERROR Then
		writeProfile($editingProfile, True)
		convertProfilesToLua()
	EndIf
EndFunc

Func proceedDeletingProfile()
	deleteProfile($editingProfile)
	convertProfilesToLua()
EndFunc

Func writeProfile($position, $edit = False)
	IniWrite($Ini, "profile" & $position, "name", GUICtrlRead($formData[0]))
	IniWrite($Ini, "profile" & $position, "class", GUICtrlRead($formData[1]))
	IniWrite($Ini, "profile" & $position, "itemtype", GUICtrlRead($formData[2]))
	IniWrite($Ini, "profile" & $position, "subtype", GUICtrlRead($formData[3]))
	IniWrite($Ini, "profile" & $position, "rarity", GUICtrlRead($formData[4]))
	For $i = 1 To 6
		IniWrite($Ini, "profile" & $position, "filter" & $i, GUICtrlRead($filterData[$i - 1][0]))
		IniWrite($Ini, "profile" & $position, "value"  & $i, GUICtrlRead($filterData[$i - 1][1]))
	Next
	IniWrite($Ini, "profile" & $position, "price", GUICtrlRead($formData[5]))
	IniWrite($Ini, "profile" & $position, "bid", GUICtrlRead($formData[6]))
	IniWrite($Ini, "profile" & $position, "buyout", GUICtrlRead($formData[7]))
	IniWrite($Ini, "profile" & $position, "priceflag", GUICtrlRead($formData[8]))
	IniWrite($Ini, "profile" & $position, "startgold", GUICtrlRead($formData[9]))
	IniWrite($Ini, "profile" & $position, "timeleft", GUICtrlRead($formData[10]))
	IniWrite($Ini, "profile" & $position, "minlvl", GUICtrlRead($formData[11]))
	IniWrite($Ini, "profile" & $position, "maxlvl", GUICtrlRead($formData[12]))
	IniWrite($Ini, "profile" & $position, "dpsarmor", GUICtrlRead($formData[13]))
	IniWrite($Ini, "profile" & $position, "legendaryset", GUICtrlRead($formData[14]))
	Local $tempSliderData = "0"
	If GUICtrlRead($mainSlider) <> GUICtrlRead($formData[15]) Then
		$tempSliderData = GUICtrlRead($formData[15])
	EndIf
	IniWrite($Ini, "profile" & $position, "queries", $tempSliderData)
	IniWrite($Ini, "profile" & $position, "itemlevel", GUICtrlRead($formData[17]))
	IniWrite($Ini, "profile" & $position, "logflag", GUICtrlRead($formData[18]))
	If Not $edit Then
		;update main dropdown
		$mainList &= "|" & GUICtrlRead($formData[0])
		_GUICtrlComboBox_ResetContent($mainDropDown)
		GUICtrlSetData($mainDropDown, $mainList)
		;update profile counter
		$profileCounter += 1
		IniWrite($Ini, "main", "profilecounter", $profileCounter)
	EndIf
	;switch gui
	switchToMainGUI()
EndFunc

Func loadProfile()
	editProfileGUI()
	For $i = 0 To $profileCounter - 1
		$tempProfile = IniRead($Ini, "profile" & $i, "name", $error)
		If GUICtrlRead($mainDropDown) == $tempProfile Then
			$editingProfile = $i
			GUICtrlSetData($formData[0], $tempProfile)
			_GUICtrlComboBox_SetCurSel($formData[1], _GUICtrlComboBox_FindString($formData[1], IniRead($Ini, "profile" & $i, "class", $error)))
			_GUICtrlComboBox_SetCurSel($formData[2], _GUICtrlComboBox_FindString($formData[2], IniRead($Ini, "profile" & $i, "itemtype", $error)))
			checkItemtype()
			_GUICtrlComboBox_SetCurSel($formData[3], _GUICtrlComboBox_FindString($formData[3], IniRead($Ini, "profile" & $i, "subtype", $error)))
			_GUICtrlComboBox_SetCurSel($formData[4], _GUICtrlComboBox_FindString($formData[4], IniRead($Ini, "profile" & $i, "rarity", $error)))
			GUICtrlSetData($formData[5], IniRead($Ini, "profile" & $i, "price", $error))
			GUICtrlSetData($formData[6], IniRead($Ini, "profile" & $i, "bid", $error))
			GUICtrlSetData($formData[7], IniRead($Ini, "profile" & $i, "buyout", $error))
			If	IniRead($Ini, "profile" & $i, "priceflag", "4") == "1" Then
				GUICtrlSetState ($formData[8], $GUI_CHECKED)
			EndIf
			GUICtrlSetData($formData[9], IniRead($Ini, "profile" & $i, "startgold", $error))
			GUICtrlSetData($formData[10], IniRead($Ini, "profile" & $i, "timeleft", $error))
			GUICtrlSetData($formData[11], IniRead($Ini, "profile" & $i, "minlvl", $error))
			GUICtrlSetData($formData[12], IniRead($Ini, "profile" & $i, "maxlvl", $error))
			GUICtrlSetData($formData[13], IniRead($Ini, "profile" & $i, "dpsarmor", $error))
			GUICtrlSetData($formData[14], IniRead($Ini, "profile" & $i, "legendaryset", $error))
			Local $tempSliderData = GUICtrlRead($mainSlider)
			If IniRead($Ini, "profile" & $i, "queries", $error) <> "0" Then
				$tempSliderData = IniRead($Ini, "profile" & $i, "queries", $error)
			EndIf
			GUICtrlSetData($formData[15], $tempSliderData)
			GUICtrlSetData($formData[16], $tempSliderData)
			If  $tempSliderData == 0 Or $tempSliderData > $queryZoneValue Then
				GUICtrlSetColor($formData[16], $colorRED)
			Else
				GUICtrlSetColor($formData[16], $colorGREEN)
			EndIf
			GUICtrlSetData($formData[17], IniRead($Ini, "profile" & $i, "itemlevel", $error))
			If	IniRead($Ini, "profile" & $i, "logflag", "4") == "1" Then
				GUICtrlSetState ($formData[18], $GUI_CHECKED)
			EndIf
			For $t = 1 To 6
				GUICtrlSetData($filterData[$t - 1][0], IniRead($Ini, "profile" & $i, "filter" & $t, $error))
				GUICtrlSetData($filterData[$t - 1][1], IniRead($Ini, "profile" & $i, "value" & $t, $error))
			Next
		EndIf
	Next
EndFunc

Func deleteProfile($position)
	$tempProfile = IniRead($Ini, "profile" & $position, "name", "")
	IniDelete($Ini, "profile" & $position)
	;update main dropdown
	$mainList = StringReplace($mainList, "|" & $tempProfile, "")
	_GUICtrlComboBox_ResetContent($mainDropDown)
	GUICtrlSetData($mainDropDown, $mainList)
	;update ini profiles
	If $position + 1 < $profileCounter Then
		For $i = $position To $profileCounter - 2
			IniRenameSection($Ini, "profile" & ($i + 1), "profile" & $i)
		Next
	EndIf
	;update profile counter
	$profileCounter -= 1
	IniWrite($Ini, "main", "profilecounter", $profileCounter)
	;switch gui
	switchToMainGUI()
EndFunc
#endregion
#region INPUT CONTROLLER
Func checkInput()
	$catchedERROR = False
	;check if all controls are filled
	For $i = 0 To UBound($formData) - 1
		If GUICtrlRead($formData[$i]) == "" Then
			paintGUI($formData[$i], False)
			$catchedERROR = True
		Else
			paintGUI($formData[$i])
		EndIf
	Next
	;check if the profilename is unique
	$doubleProfile = False
	For $i = 0 To $profileCounter - 1
		If GUICtrlRead($formData[0]) == IniRead($Ini, "profile" & $i, "name", "") Then
			If $editingProfile <> $i Then
				$doubleProfile = True
			EndIf
		EndIf
	Next
	If $doubleProfile Then
		paintGUI($formData[0], False)
		$catchedERROR = True
	ElseIf GUICtrlRead($formData[0]) <> "" Then
		paintGUI($formData[0])
	EndIf
	;check price, bid and buyout if they are numbers
	For $i = 5 To 7
		If  Number(GUICtrlRead($formData[$i])) < 1 And GUICtrlRead($formData[$i]) <> "0" Then
			paintGUI($formData[$i], False)
			$catchedERROR = True
		Else
			paintGUI($formData[$i])
			;check if price(5) >= buyout(7) >= bid(6) (at 7 to check only one time)
			If $i == 7 Then
				If Number(GUICtrlRead($formData[5])) < Number(GUICtrlRead($formData[7])) Then
					paintGUI($formData[7], False)
					$catchedERROR = True
				Else
					paintGUI($formData[7])
				EndIf
				If Number(GUICtrlRead($formData[7])) < Number(GUICtrlRead($formData[6])) Or Number(GUICtrlRead($formData[5])) < Number(GUICtrlRead($formData[6])) Then
					paintGUI($formData[6], False)
					$catchedERROR = True
				Else
					paintGUI($formData[6])
				EndIf
			EndIf
		EndIf
	Next
	;check when we have a stat if the value is a number and > 0
	For $i = 0 To 5
		If Number(GUICtrlRead($filterData[$i][1])) < 1 And GUICtrlRead($filterData[$i][1]) <> "0" Then
			paintGUI($filterData[$i][1], False)
			$catchedERROR = True
		Else
			paintGUI($filterData[$i][1])
			;new error check
			If GUICtrlRead($filterData[$i][0]) == "stat" And GUICtrlRead($filterData[$i][1]) > 0 Then
				paintGUI($filterData[$i][0], False)
				$catchedERROR = True
			Else
				paintGUI($filterData[$i][0])
			Endif
			If GUICtrlRead($filterData[$i][0]) <> "stat" And GUICtrlRead($filterData[$i][1]) < 1 Then
				paintGUI($filterData[$i][1], False)
				$catchedERROR = True
			Else
				paintGUI($filterData[$i][1])
			EndIf
		EndIf
	Next
	;check startgold for number
	If  Number(GUICtrlRead($formData[9])) < 1 And GUICtrlRead($formData[9]) <> "0" Then
		paintGUI($formData[9], False)
		$catchedERROR = True
	Else
		paintGUI($formData[9])
	EndIf
	;redraw window to avoid gui errors
	_WinAPI_RedrawWindow($inputGUI)
	Return $catchedERROR
EndFunc

Func manipulateInputMK($controlData, $input)
	Local $manipulatedInput = $input
	$manipulatedInput = StringRegExpReplace($manipulatedInput, "[,]", ".")
	If checkStringForManipulator($manipulatedInput, "[mM]") Then
		$manipulatedInput = StringRegExpReplace($manipulatedInput, "[mM]", "")
		$manipulatedInput = Number($manipulatedInput)
		$manipulatedInput *= 1000000
	EndIf
	If checkStringForManipulator($manipulatedInput, "[kK]") Then
		$manipulatedInput = StringRegExpReplace($manipulatedInput, "[kK]", "")
		$manipulatedInput = Number($manipulatedInput)
		$manipulatedInput *= 1000
	EndIf
	If $manipulatedInput <> $input Then
		GUICtrlSetData($controlData, $manipulatedInput)
	EndIf
EndFunc

Func checkStringForManipulator($string, $manipulator)
    If StringRegExp($string, $manipulator) Then Return True
    Return False
EndFunc

Func manipulateInput()
	;manipulate price, bid and buyout
	For $i = 5 To 7
		manipulateInputMK($formData[$i], GUICtrlRead($formData[$i]))
	Next
	;manipulate startgold
	manipulateInputMK($formData[9], GUICtrlRead($formData[9]))
	;manipulate pagedelay
	manipulateInputMK($mainInput, GUICtrlRead($mainInput))
EndFunc

Func checkSliderInput()
	Local $tempSlider[2] = [$mainSlider, $formData[15]]
	Local $tempSliderCache[2] = [$mainSliderCache, $formData[16]]
	For $i = 0 To 1
		$tempSliderValue = GUICtrlRead($tempSlider[$i])
		If GUICtrlRead($tempSliderCache[$i]) <> $tempSliderValue Then
			GUICtrlSetData($tempSliderCache[$i], $tempSliderValue)
			If $tempSliderValue == 0 Or $tempSliderValue > $queryZoneValue Then
				GUICtrlSetColor($tempSliderCache[$i], $colorRED)
			Else
				GUICtrlSetColor($tempSliderCache[$i], $colorGREEN)
			EndIf
			;update slider value in main
			If $i = 0 Then
				IniWrite($Ini, "main", "queries", $tempSliderValue)
			EndIf
		EndIf
	Next
EndFunc

Func checkPageDelayInput()
	If IniRead($Ini, "main", "pagedelay", $error) <> GUICtrlRead($mainInput) Then
		IniWrite($Ini, "main", "pagedelay", GUICtrlRead($mainInput))
	EndIf
EndFunc

Func checkMainInput()
	checkSliderInput()
	checkPageDelayInput()
EndFunc
#endregion
#region LUA CONVERTER
Func convertProfilesToLua()
	$statfilter = "ERROR,Has Sockets,stat"

	FileDelete($Txt)
	FileWrite($Txt, "")

	WriteLua("--[[", 1)
	WriteLua("DISCLAIMER:")
	WriteLua("This file was automatically created by HAA Profile Creator. It may not be compatible with HA.")
	WriteLua("Please do not change this file unless you know what you're doing.")
	WriteLua("]]--", -1)

	WriteLua("while 1 do", 1)

	$lua_tabs = ""
	Local $profiles = loadIni()
	For $i = 0 To UBound($profiles)-1
		Local $prof = $profiles[$i]

		luaResetFilters()

		; 0 filter, 1 name, 2 class, 3 itemtype, 4 subtype, 5 rarity, 6 price, 7 bid, 8 buyout, 9 priceflag (random), 10 startgold, 11 log flag
		; filter: 0 stats, 1 values
		; write profile name
		If $i > 0 Then WriteLua("")
		WriteLua("-- Profile " & $prof[1])

		; check gold (lets do that in the beginning)
		If $prof[10] > 0 Then WriteLua("if haGetGold() > " & $prof[10] & " then", 1)

		If StringLen($prof[2]) > 0 Then WriteLua("haFilterClass('" & $prof[2] & "')")

		; itemtype is automatically determined, just use subtype
		If StringLen($prof[4]) > 0 Then
			WriteLua("haFilterType('" & $prof[4] & "')")
		Else
			; if subtype isn't set use itemtype
			WriteLua("haFilterType('" & $prof[3] & "')")
		EndIf
		; rarity
		If StringLen($prof[5]) > 0 Then
			WriteLua("haFilterRarity('" & $prof[5] & "')")
		Else
			WriteLua("haFilterRarity('All')")
		EndIf
		; level requirement
		If $prof[15] > 0 And $prof[16] > 0 Then
			WriteLua("haFilterLevel(" & $prof[15] & "," & $prof[16] & ")")
		ElseIf $prof[15] > 0 Then
			WriteLua("haFilterLevel(" & $prof[15] & ",-1)")
		ElseIf $prof[16] > 0 Then
			WriteLua("haFilterLevel(-1," & $prof[16] & ")")
		Else
			WriteLua("haFilterLevel(-1,-1)")
		EndIf

		; price
		If $prof[6] > 0 Then
			If $prof[9] == 1 Then ; randomize
				WriteLua("haFilterBuyout(" & $prof[6] & ", true)")
			Else
				WriteLua("haFilterBuyout(" & $prof[6] & ", false)")
			EndIf
		Else
			WriteLua("haFilterBuyout(-1)")
		EndIf

		; set unique/legendary name
		If StringLen($prof[14]) > 0 Then
			WriteLua("haFilterUnique('" & $prof[14] & "')")
		Else
			WriteLua("haFilterUnique('')")
		EndIf

		$filter = $prof[0]
		$stats = $filter[0]
		$values = $filter[1]

		$fcount = 0

		If $stats[0] > 0 Then
			; set first 3 filter
			For $j = 1 To $stats[0]
				If $stats[$j] <> "ERROR" And $stats[$j] <> "stat" Then
					$fcount += 1
					WriteLua("haFilterStat(" & $fcount & ", '" & $stats[$j] & "', " & $values[$j] & ")")
					If $fcount == 3 Then ExitLoop
				EndIf
			Next
		EndIf

		; now lets search
		WriteLua("if haActionSearch() then", 1)
		WriteLua("while haListNext() do", 1)

		; get item information
		WriteLua("local dpsarmor, bid, buyout, nstats, nsockets, id, currBid, flags, ilvl, timeleft, name = haListItem()")

		; log it?
		If $prof[11] == 1 Then WriteLua("haLog('ID: ' .. id .. ' DPS/Armor: ' .. dpsarmor .. ' bid: ' .. bid .. ' buyout: ' .. buyout .. ' currBid: ' .. currBid .. ' flags: ' .. flags .. ' ilvl: ' .. ilvl .. ' timeleft: ' .. timeleft .. ' name: ' .. name)")

		WriteLua("local found = 0")
		$found = 0

		; only loop through stats when we want to check stats or log it
		If $stats[0] > 0 Or $prof[11] == 1 Then
			; check the stats
			WriteLua("for i = 1, nstats do", 1)

			WriteLua("local stat, value1 = haListItemStat(i)")
			If $prof[11] == 1 Then WriteLua("haLog('STAT:' .. stat .. ' VALUE:' .. value1)")

			For $j = 1 To $stats[0]
				If StringInStr($statfilter, $stats[$j]) == 0 Then
					$found += 1
					WriteLua('if stat == "' & $stats[$j] & '" and value1 >= ' & $values[$j] & " then found = found + 1 end")
				EndIf
			Next

			WriteLua("end", -1) ; end for stat-loop
		EndIf

		; check dps/armor
		If $prof[12] > 0 Then
			WriteLua("if dpsarmor > " & $prof[12] & " then found = found + 1 end")
			$found += 1
		EndIf

		; check itemlevel
		If $prof[13] > 0 Then
			WriteLua("if ilvl > " & $prof[13] & " then found = found + 1 end")
			$found += 1
		EndIf

		; buy/bid if we have buy/bid values
		If $prof[7] > 0 Or $Prof[8] > 0 Then
			; did we find all filter and did the values fit?
			WriteLua("if found == " & $found & " and flags == 102 then", 1)

			; check buyout
			If $prof[8] > 0 Then
				WriteLua("if buyout <= " & $prof[8] & " then", 1)
				If $prof[11] == 1 Then WriteLua("haLog('Buying item')")
				WriteLua("haActionBuyout()")
			EndIf
			; check bid
			If $prof[7] > 0 Then
				If $prof[8] > 0 Then
					WriteLua("elseif bid <= " & $prof[7] & " then", -1)
				Else
					WriteLua("if bid <= " & $prof[7] & " then", 1)
				EndIf
				If $prof[11] == 1 Then WriteLua("haLog('Bidding on item for " & $prof[7] & "')")
				WriteLua("haActionBid(" & $prof[7] & ")",1)
			EndIf

			WriteLua("end", -1) ; end for bid/buyout if
			WriteLua("end", -1) ; end for found
		ElseIf $prof[11] == 1 Then
			WriteLua("if found == " & $found & " and flags == 102 then haLog('Found match!') end")
		EndIf

		If $prof[11] == 1 Then
			WriteLua("for i = 1, nsockets do", 1)
			WriteLua("local stat, gtype, rank, value1 = haListItemSocket(i)")
			WriteLua("haLog('SOCKET:' .. stat .. ' VALUE:' .. value1 .. ' GEM:' .. gtype .. ' RANK:' .. rank)")
			WriteLua("end", -1)
		EndIf
		WriteLua("end", -1) ; end for while
		WriteLua("end", -1) ; end for search
		If $prof[10] > 0 Then WriteLua("end", -1) ; end for gold if
	Next

	WriteLua("end", -1) ; end for main while
EndFunc

Func WriteLua($text, $tab_count_change = 0)
	If $tab_count_change < 0 Then $lua_tab_count += $tab_count_change
	$lua_tabs = ""
	For $i = 1 To $lua_tab_count
		$lua_tabs &= @TAB
	Next
	FileWriteLine($Txt, $lua_tabs & $text)
	If $tab_count_change > 0 Then $lua_tab_count += $tab_count_change
EndFunc

Func luaResetFilters()
	WriteLua("haFilterStat(1, 'None', 0)")
	WriteLua("haFilterStat(2, 'None', 0)")
	WriteLua("haFilterStat(3, 'None', 0)")
EndFunc
#endregion