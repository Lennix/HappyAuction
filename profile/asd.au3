Local $batchContent = "@echo off" & @CRLF & _
;wait until creator exe is closed
":loop" & @CRLF & _
"del /Q ProfileCreator.exe" & @CRLF & _
"if exist ProfileCreator.exe goto loop" & @CRLF & _
;write new creator file
"if exist ProfileCreator.exe.new" & @CRLF & _
"(REN ProfileCreator.exe.new ProfileCreator.exe)" & @CRLF & _
;write new bot file
"if exist HappyAuctionAdvanced.exe.new" & @CRLF & _
"(del /Q HappyAuctionAdvanced.exe" & @CRLF & _
"REN HappyAuctionAdvanced.exe.new HappyAuctionAdvanced.exe)" & @CRLF & _
;start creator
"start ProfileCreator.exe" & @CRLF & _
"exit"