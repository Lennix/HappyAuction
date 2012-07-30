#region COMMENTS
;log für profile statt für filter, queries per hour profile zum überschreibend er main, nextpagedelay in ms unter main, itemtimeleft min, legendarys and itemsets namen feld, minmax level
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
Global $mainList = ""
Global $mainGUI = ""
Global $inputGUI = ""
Global $mainDropDown = ""
Global $mainSlider = ""
Global $mainSliderCache = ""
Global $addButton = ""
Global $createButton = ""
Global $editButton = ""
Global $deleteButton = ""

Global $profileCounter = 0
Global $editingProfile = -1
Global $sliderStartValue = 800

Global $formData[10] = ["", "", "", "", "", "", "", "", "", ""]
Global $filterData[6][3] = [["", "", ""], ["", "", ""], ["", "", ""], ["", "", ""], ["", "", ""], ["", "", ""]]
#endregion
#region VARIABLES CONST
Const $Ini = "Profiles.ini"
Const $Txt = "Profiles.txt"

Const $error = "ERROR"

Const $colorRED = 0xF20041
Const $colorGREEN = 0x0D8B1A
Const $colorSTANDARD = 0xffffff

Const $queryZoneValue = 900
#endregion
#endregion
#region CORE
#region CORE START
checkIniFile()
builtMainGUI()
#endregion
#region CORE LOOP
While 1
	;manipulate mM for price, bid and buyout
	For $i = 5 To 7
		manipulateInputM($formData[$i], GUICtrlRead($formData[$i]))
	Next
	;manipulate mM for startgold
	manipulateInputM($formData[9], GUICtrlRead($formData[9]))
	;update slider value
	checkSliderInput()
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
	$mainGUI = GUICreate("ProfileAssembler - Z ©2012 Zero", 300, 90)
	builtMainLayers()
	GUISetState(@SW_SHOW, $mainGUI)
	GUISetOnEvent($GUI_EVENT_CLOSE, "quit", $mainGUI)
EndFunc

Func builtMainLayers()
	;main dropdown line
	GUICtrlCreateLabel("Profile", 10, 18)
	$mainDropDown = GUICtrlCreateCombo("", 76, 15, 166, 20)
	GUICtrlSetData($mainDropDown, $mainList)
	GUICtrlSetOnEvent($mainDropDown, "loadProfile")
	;add button line
	$addButton = GUICtrlCreateButton("+", 256, 12, 30, 26)
	GUICtrlSetOnEvent($addButton, "createProfileGUI")
	;queries per hour line
	GUICtrlCreateLabel("Queries / h", 10, 55)
	$mainSlider = GUICtrlCreateSlider(70, 53, 180, 50, BitOR($TBS_TOOLTIPS, $TBS_BOTTOM, $TBS_ENABLESELRANGE))
	GUICtrlSetLimit($mainSlider, 1600, 0)
	GUICtrlSetData($mainSlider, $sliderStartValue)
	Local $tempTicks[5] = [0, 400, 800, 1200, 1600]
	_GUICtrlSlider_ClearTics($mainSlider)
	For $i = 0 To UBound($tempTicks) - 1
		_GUICtrlSlider_SetTic($mainSlider, $tempTicks[$i])
	Next
	$mainSliderCache = GUICtrlCreateLabel($sliderStartValue, 257, 55, 30)
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
	$inputGUI = GUICreate("ProfileAssembler - Z ©2012 Zero", 300, 380)
	builtInputLayers()
	GUISetState(@SW_SHOW, $inputGUI)
	GUISetOnEvent($GUI_EVENT_CLOSE, "quit", $inputGUI)
EndFunc

Func builtInputLayers()
	;filtername line
	GUICtrlCreateLabel("ProfileName", 10, 18)
	$formData[0] = GUICtrlCreateInput("", 80, 15, 200, 20)
	;class line
	$classList = "Barbarian|Demon Hunter|Monk|Witch Doctor|Wizard"
	GUICtrlCreateLabel("Class", 10, 48)
	$formData[1] = GUICtrlCreateCombo("", 80, 45, 200, 20)
	GUICtrlSetData($formData[1], $classList)
	;itemtype line
	$itemtypeList = "1-Hand|2-Hand|Off-Hand|Armor|Follower Special"
	GUICtrlCreateLabel("ItemType", 10, 78)
	$formData[2] = GUICtrlCreateCombo("", 80, 75, 200, 20)
	GUICtrlSetData($formData[2], $itemtypeList)
	GUICtrlSetOnEvent($formData[2], "checkItemtype")
	;subtype line
	GUICtrlCreateLabel("SubType", 10, 108)
	$formData[3] = GUICtrlCreateCombo("", 80, 105, 200, 20)
	;rarity line
	$rarityList = "All|Inferior|Normal|Superior|Magic|Rare|Legendary"
	GUICtrlCreateLabel("Rarity", 10, 138)
	$formData[4] = GUICtrlCreateCombo("", 80, 135, 200, 20)
	GUICtrlSetData($formData[4], $rarityList)
	;filter
	GUICtrlCreateLabel("Filter", 10, 168)
	GUICtrlCreateTab(80, 165, 200, 50)
	$startTab = ""
	For $i = 1 To 6
		If $i == 1 Then
			$startTab = GUICtrlCreateTabItem($i)
		Else
			GUICtrlCreateTabItem($i)
		EndIf
		$filterData[$i - 1][0] = GUICtrlCreateInput("stat", 87, 190, 110, 20)
		$filterData[$i - 1][1] = GUICtrlCreateInput("0", 205, 190, 25, 20)
		$filterData[$i - 1][2] = GUICtrlCreateCheckbox("Log", 237, 190, 35, 20)
	Next
	GUICtrlCreateTabItem("")
	GUICtrlSetState($startTab, $GUI_SHOW)
	;price line
	GUICtrlCreateLabel("Price", 10, 228)
	$formData[5] = GUICtrlCreateInput("", 80, 225, 150, 20)
	;bid line
	GUICtrlCreateLabel("Bid", 10, 258)
	$formData[6] = GUICtrlCreateInput("", 80, 255, 200, 20)
	;buyout line
	GUICtrlCreateLabel("Buyout", 10, 288)
	$formData[7] = GUICtrlCreateInput("", 80, 285, 200, 20)
	;random checkbox line
	$formData[8] = GUICtrlCreateCheckbox("Random", 237, 225, 55, 20)
	;start gold line
	GUICtrlCreateLabel("StartGold", 10, 318)
	$formData[9] = GUICtrlCreateInput("0", 80, 315, 200, 20)
EndFunc

Func builtCreateButton()
	$createButton = GUICtrlCreateButton("Create", 100, 343, 100, 30)
	GUICtrlSetOnEvent($createButton, "proceedCreatingProfile")
EndFunc

Func builtEditButton()
	$editButton = GUICtrlCreateButton("Edit", 33, 343, 100, 30)
	GUICtrlSetOnEvent($editButton, "proceedEditingProfile")
EndFunc

Func builtDeleteButton()
	$deleteButton = GUICtrlCreateButton("Delete", 166, 343, 100, 30)
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
	Local $arrayProfiles[$profileCounter]
	For $i = 0 To UBound($arrayProfiles) - 1
		Local $arrayData[11]
		Local $arrayFilter[2]
		Local $arrayStat[6]
		Local $arrayValue[6]
		For $t = 0 To 5
			$arrayStat[$t] = IniRead($Ini, "profile" & $i, "filter" & $t, $error)
			$arrayValue[$t] = IniRead($Ini, "profile" & $i, "value" & $t, $error)
		Next
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
		IniWrite($Ini, "profile" & $position, "filterflag"  & $i, GUICtrlRead($filterData[$i - 1][2]))
	Next
	IniWrite($Ini, "profile" & $position, "price", GUICtrlRead($formData[5]))
	IniWrite($Ini, "profile" & $position, "bid", GUICtrlRead($formData[6]))
	IniWrite($Ini, "profile" & $position, "buyout", GUICtrlRead($formData[7]))
	IniWrite($Ini, "profile" & $position, "priceflag", GUICtrlRead($formData[8]))
	IniWrite($Ini, "profile" & $position, "startgold", GUICtrlRead($formData[9]))
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
			For $t = 1 To 6
				GUICtrlSetData($filterData[$t - 1][0], IniRead($Ini, "profile" & $i, "filter" & $t, $error))
				GUICtrlSetData($filterData[$t - 1][1], IniRead($Ini, "profile" & $i, "value" & $t, $error))
				If	IniRead($Ini, "profile" & $i, "filterflag" & $t, "4") == "1" Then
					GUICtrlSetState ($filterData[$t - 1][2], $GUI_CHECKED)
				EndIf
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

Func manipulateInputM($controlData, $input)
	$manipulatedInput = StringRegExpReplace($input, "[mM]", "000000")
	If $manipulatedInput <> $input Then
		GUICtrlSetData($controlData, $manipulatedInput)
	EndIf
EndFunc

Func checkSliderInput()
	$tempSliderValue = GUICtrlRead($mainSlider)
	If GUICtrlRead($mainSliderCache) <> $tempSliderValue Then
		GUICtrlSetData($mainSliderCache, $tempSliderValue)
		If $tempSliderValue == 0 Or $tempSliderValue > $queryZoneValue Then
			GUICtrlSetColor($mainSliderCache, $colorRED)
		Else
			GUICtrlSetColor($mainSliderCache, $colorGREEN)
		EndIf
		;update slider value in ini
		IniWrite($Ini, "main", "queries", $tempSliderValue)
	EndIf
EndFunc
#endregion
#region LUA CONVERTER
Func convertProfilesToLua()
	FileDelete($Txt)
	FileWrite($Txt, "")
	Local $profiles = loadIni()
	For $i = 0 To UBound($profiles) - 1
		Local $tempData = $profiles[$i]
		FileWriteLine($Txt, "-- Profile " & $tempData[1])
		FileWriteLine($Txt, "haFilterType('" & $tempData[4] & "')")
		FileWriteLine($Txt, "haFilterRarity('" & $tempData[5] & "')")
		FileWriteLine($Txt, "")
	Next
EndFunc
#endregion