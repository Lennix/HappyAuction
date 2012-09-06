Func md5($sMessage)
    Local $Padding = Binary('0x8000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000')
    Local $bytes = Binary($sMessage) + BinaryMid($Padding,1,BinaryLen($Padding) - Mod(BinaryLen($sMessage),64)) + BinaryMid(Binary(BinaryLen($sMessage)*8)+Binary(0),1,8)
    Local $x[BinaryLen($bytes)/4]
    For $i = 1 To BinaryLen($bytes) Step 4
        $x[($i-1)/4] = Dec(StringTrimLeft(Binary(BinaryMid($bytes,$i+3,1) + BinaryMid($bytes,$i+2,1) + BinaryMid($bytes,$i+1,1) + BinaryMid($bytes,$i,1)),2))
    Next
    Local $a = 0x67452301, $b = 0xEFCDAB89, $c = 0x98BADCFE, $d = 0x10325476

    For $k = 0 To UBound($x) - 1 Step 16
        $AA = $a
        $BB = $b
        $CC = $c
        $DD = $d

        ; The hex number in the middle of each of the following lines
        ; an element from the 64 element table constructed with
        ; T(i) = Int(4294967296 * Abs(Sin(i))) where i is 1 to 64.
        ;
        ; However, for speed we don't want to calculate the value every time.


        $a = BitOR(BitRotate(BitOR($a + BitOR(BitOR(BitOR(BitAND($b, $c), BitAND((BitNOT($b)), $d)) + $x[$k + 0x0],0) + 0xD76AA478,0),0), 0x07,"D")+$b,0)
        $d = BitOR(BitRotate(BitOR($d + BitOR(BitOR(BitOR(BitAND($a, $b), BitAND((BitNOT($a)), $c)) + $x[$k + 0x1],0) + 0xE8C7B756,0),0), 0x0C,"D")+$a,0)
        $c = BitOR(BitRotate(BitOR($c + BitOR(BitOR(BitOR(BitAND($d, $a), BitAND((BitNOT($d)), $b)) + $x[$k + 0x2],0) + 0x242070DB,0),0), 0x11,"D")+$d,0)
        $b = BitOR(BitRotate(BitOR($b + BitOR(BitOR(BitOR(BitAND($c, $d), BitAND((BitNOT($c)), $a)) + $x[$k + 0x3],0) + 0xC1BDCEEE,0),0), 0x16,"D")+$c,0)
        $a = BitOR(BitRotate(BitOR($a + BitOR(BitOR(BitOR(BitAND($b, $c), BitAND((BitNOT($b)), $d)) + $x[$k + 0x4],0) + 0xF57C0FAF,0),0), 0x07,"D")+$b,0)
        $d = BitOR(BitRotate(BitOR($d + BitOR(BitOR(BitOR(BitAND($a, $b), BitAND((BitNOT($a)), $c)) + $x[$k + 0x5],0) + 0x4787C62A,0),0), 0x0C,"D")+$a,0)
        $c = BitOR(BitRotate(BitOR($c + BitOR(BitOR(BitOR(BitAND($d, $a), BitAND((BitNOT($d)), $b)) + $x[$k + 0x6],0) + 0xA8304613,0),0), 0x11,"D")+$d,0)
        $b = BitOR(BitRotate(BitOR($b + BitOR(BitOR(BitOR(BitAND($c, $d), BitAND((BitNOT($c)), $a)) + $x[$k + 0x7],0) + 0xFD469501,0),0), 0x16,"D")+$c,0)
        $a = BitOR(BitRotate(BitOR($a + BitOR(BitOR(BitOR(BitAND($b, $c), BitAND((BitNOT($b)), $d)) + $x[$k + 0x8],0) + 0x698098D8,0),0), 0x07,"D")+$b,0)
        $d = BitOR(BitRotate(BitOR($d + BitOR(BitOR(BitOR(BitAND($a, $b), BitAND((BitNOT($a)), $c)) + $x[$k + 0x9],0) + 0x8B44F7AF,0),0), 0x0C,"D")+$a,0)
        $c = BitOR(BitRotate(BitOR($c + BitOR(BitOR(BitOR(BitAND($d, $a), BitAND((BitNOT($d)), $b)) + $x[$k + 0xA],0) + 0xFFFF5BB1,0),0), 0x11,"D")+$d,0)
        $b = BitOR(BitRotate(BitOR($b + BitOR(BitOR(BitOR(BitAND($c, $d), BitAND((BitNOT($c)), $a)) + $x[$k + 0xB],0) + 0x895CD7BE,0),0), 0x16,"D")+$c,0)
        $a = BitOR(BitRotate(BitOR($a + BitOR(BitOR(BitOR(BitAND($b, $c), BitAND((BitNOT($b)), $d)) + $x[$k + 0xC],0) + 0x6B901122,0),0), 0x07,"D")+$b,0)
        $d = BitOR(BitRotate(BitOR($d + BitOR(BitOR(BitOR(BitAND($a, $b), BitAND((BitNOT($a)), $c)) + $x[$k + 0xD],0) + 0xFD987193,0),0), 0x0C,"D")+$a,0)
        $c = BitOR(BitRotate(BitOR($c + BitOR(BitOR(BitOR(BitAND($d, $a), BitAND((BitNOT($d)), $b)) + $x[$k + 0xE],0) + 0xA679438E,0),0), 0x11,"D")+$d,0)
        $b = BitOR(BitRotate(BitOR($b + BitOR(BitOR(BitOR(BitAND($c, $d), BitAND((BitNOT($c)), $a)) + $x[$k + 0xF],0) + 0x49B40821,0),0), 0x16,"D")+$c,0)

        $a = BitOR(BitRotate(BitOR($a + BitOR(BitOR(BitOR(BitAND($b, $d), BitAND($c, (BitNOT($d)))) + $x[$k + 0x1],0) + 0xF61E2562,0),0),0x05,"D")+$b,0)
        $d = BitOR(BitRotate(BitOR($d + BitOR(BitOR(BitOR(BitAND($a, $c), BitAND($b, (BitNOT($c)))) + $x[$k + 0x6],0) + 0xC040B340,0),0),0x09,"D")+$a,0)
        $c = BitOR(BitRotate(BitOR($c + BitOR(BitOR(BitOR(BitAND($d, $b), BitAND($a, (BitNOT($b)))) + $x[$k + 0xB],0) + 0x265E5A51,0),0),0x0E,"D")+$d,0)
        $b = BitOR(BitRotate(BitOR($b + BitOR(BitOR(BitOR(BitAND($c, $a), BitAND($d, (BitNOT($a)))) + $x[$k + 0x0],0) + 0xE9B6C7AA,0),0),0x14,"D")+$c,0)
        $a = BitOR(BitRotate(BitOR($a + BitOR(BitOR(BitOR(BitAND($b, $d), BitAND($c, (BitNOT($d)))) + $x[$k + 0x5],0) + 0xD62F105D,0),0),0x05,"D")+$b,0)
        $d = BitOR(BitRotate(BitOR($d + BitOR(BitOR(BitOR(BitAND($a, $c), BitAND($b, (BitNOT($c)))) + $x[$k + 0xA],0) + 0x02441453,0),0),0x09,"D")+$a,0)
        $c = BitOR(BitRotate(BitOR($c + BitOR(BitOR(BitOR(BitAND($d, $b), BitAND($a, (BitNOT($b)))) + $x[$k + 0xF],0) + 0xD8A1E681,0),0),0x0E,"D")+$d,0)
        $b = BitOR(BitRotate(BitOR($b + BitOR(BitOR(BitOR(BitAND($c, $a), BitAND($d, (BitNOT($a)))) + $x[$k + 0x4],0) + 0xE7D3FBC8,0),0),0x14,"D")+$c,0)
        $a = BitOR(BitRotate(BitOR($a + BitOR(BitOR(BitOR(BitAND($b, $d), BitAND($c, (BitNOT($d)))) + $x[$k + 0x9],0) + 0x21E1CDE6,0),0),0x05,"D")+$b,0)
        $d = BitOR(BitRotate(BitOR($d + BitOR(BitOR(BitOR(BitAND($a, $c), BitAND($b, (BitNOT($c)))) + $x[$k + 0xE],0) + 0xC33707D6,0),0),0x09,"D")+$a,0)
        $c = BitOR(BitRotate(BitOR($c + BitOR(BitOR(BitOR(BitAND($d, $b), BitAND($a, (BitNOT($b)))) + $x[$k + 0x3],0) + 0xF4D50D87,0),0),0x0E,"D")+$d,0)
        $b = BitOR(BitRotate(BitOR($b + BitOR(BitOR(BitOR(BitAND($c, $a), BitAND($d, (BitNOT($a)))) + $x[$k + 0x8],0) + 0x455A14ED,0),0),0x14,"D")+$c,0)
        $a = BitOR(BitRotate(BitOR($a + BitOR(BitOR(BitOR(BitAND($b, $d), BitAND($c, (BitNOT($d)))) + $x[$k + 0xD],0) + 0xA9E3E905,0),0),0x05,"D")+$b,0)
        $d = BitOR(BitRotate(BitOR($d + BitOR(BitOR(BitOR(BitAND($a, $c), BitAND($b, (BitNOT($c)))) + $x[$k + 0x2],0) + 0xFCEFA3F8,0),0),0x09,"D")+$a,0)
        $c = BitOR(BitRotate(BitOR($c + BitOR(BitOR(BitOR(BitAND($d, $b), BitAND($a, (BitNOT($b)))) + $x[$k + 0x7],0) + 0x676F02D9,0),0),0x0E,"D")+$d,0)
        $b = BitOR(BitRotate(BitOR($b + BitOR(BitOR(BitOR(BitAND($c, $a), BitAND($d, (BitNOT($a)))) + $x[$k + 0xC],0) + 0x8D2A4C8A,0),0),0x14,"D")+$c,0)

        $a = BitOR(BitRotate(BitOR($a + BitOR(BitOR(BitXOR($b, $c, $d) + $x[$k + 0x5],0) + 0xFFFA3942,0),0),0x04,"D")+$b,0)
        $d = BitOR(BitRotate(BitOR($d + BitOR(BitOR(BitXOR($a, $b, $c) + $x[$k + 0x8],0) + 0x8771F681,0),0),0x0B,"D")+$a,0)
        $c = BitOR(BitRotate(BitOR($c + BitOR(BitOR(BitXOR($d, $a, $b) + $x[$k + 0xB],0) + 0x6D9D6122,0),0),0x10,"D")+$d,0)
        $b = BitOR(BitRotate(BitOR($b + BitOR(BitOR(BitXOR($c, $d, $a) + $x[$k + 0xE],0) + 0xFDE5380C,0),0),0x17,"D")+$c,0)
        $a = BitOR(BitRotate(BitOR($a + BitOR(BitOR(BitXOR($b, $c, $d) + $x[$k + 0x1],0) + 0xA4BEEA44,0),0),0x04,"D")+$b,0)
        $d = BitOR(BitRotate(BitOR($d + BitOR(BitOR(BitXOR($a, $b, $c) + $x[$k + 0x4],0) + 0x4BDECFA9,0),0),0x0B,"D")+$a,0)
        $c = BitOR(BitRotate(BitOR($c + BitOR(BitOR(BitXOR($d, $a, $b) + $x[$k + 0x7],0) + 0xF6BB4B60,0),0),0x10,"D")+$d,0)
        $b = BitOR(BitRotate(BitOR($b + BitOR(BitOR(BitXOR($c, $d, $a) + $x[$k + 0xA],0) + 0xBEBFBC70,0),0),0x17,"D")+$c,0)
        $a = BitOR(BitRotate(BitOR($a + BitOR(BitOR(BitXOR($b, $c, $d) + $x[$k + 0xD],0) + 0x289B7EC6,0),0),0x04,"D")+$b,0)
        $d = BitOR(BitRotate(BitOR($d + BitOR(BitOR(BitXOR($a, $b, $c) + $x[$k + 0x0],0) + 0xEAA127FA,0),0),0x0B,"D")+$a,0)
        $c = BitOR(BitRotate(BitOR($c + BitOR(BitOR(BitXOR($d, $a, $b) + $x[$k + 0x3],0) + 0xD4EF3085,0),0),0x10,"D")+$d,0)
        $b = BitOR(BitRotate(BitOR($b + BitOR(BitOR(BitXOR($c, $d, $a) + $x[$k + 0x6],0) + 0x04881D05,0),0),0x17,"D")+$c,0)
        $a = BitOR(BitRotate(BitOR($a + BitOR(BitOR(BitXOR($b, $c, $d) + $x[$k + 0x9],0) + 0xD9D4D039,0),0),0x04,"D")+$b,0)
        $d = BitOR(BitRotate(BitOR($d + BitOR(BitOR(BitXOR($a, $b, $c) + $x[$k + 0xC],0) + 0xE6DB99E5,0),0),0x0B,"D")+$a,0)
        $c = BitOR(BitRotate(BitOR($c + BitOR(BitOR(BitXOR($d, $a, $b) + $x[$k + 0xF],0) + 0x1FA27CF8,0),0),0x10,"D")+$d,0)
        $b = BitOR(BitRotate(BitOR($b + BitOR(BitOR(BitXOR($c, $d, $a) + $x[$k + 0x2],0) + 0xC4AC5665,0),0),0x17,"D")+$c,0)

        $a = BitOR(BitRotate(BitOR($a + BitOR(BitOR(BitXOR($c, BitOR($b, (BitNOT($d)))) + $x[$k + 0x0],0) + 0xF4292244,0),0),0x06,"D")+$b,0)
        $d = BitOR(BitRotate(BitOR($d + BitOR(BitOR(BitXOR($b, BitOR($a, (BitNOT($c)))) + $x[$k + 0x7],0) + 0x432AFF97,0),0),0x0A,"D")+$a,0)
        $c = BitOR(BitRotate(BitOR($c + BitOR(BitOR(BitXOR($a, BitOR($d, (BitNOT($b)))) + $x[$k + 0xE],0) + 0xAB9423A7,0),0),0x0F,"D")+$d,0)
        $b = BitOR(BitRotate(BitOR($b + BitOR(BitOR(BitXOR($d, BitOR($c, (BitNOT($a)))) + $x[$k + 0x5],0) + 0xFC93A039,0),0),0x15,"D")+$c,0)
        $a = BitOR(BitRotate(BitOR($a + BitOR(BitOR(BitXOR($c, BitOR($b, (BitNOT($d)))) + $x[$k + 0xC],0) + 0x655B59C3,0),0),0x06,"D")+$b,0)
        $d = BitOR(BitRotate(BitOR($d + BitOR(BitOR(BitXOR($b, BitOR($a, (BitNOT($c)))) + $x[$k + 0x3],0) + 0x8F0CCC92,0),0),0x0A,"D")+$a,0)
        $c = BitOR(BitRotate(BitOR($c + BitOR(BitOR(BitXOR($a, BitOR($d, (BitNOT($b)))) + $x[$k + 0xA],0) + 0xFFEFF47D,0),0),0x0F,"D")+$d,0)
        $b = BitOR(BitRotate(BitOR($b + BitOR(BitOR(BitXOR($d, BitOR($c, (BitNOT($a)))) + $x[$k + 0x1],0) + 0x85845DD1,0),0),0x15,"D")+$c,0)
        $a = BitOR(BitRotate(BitOR($a + BitOR(BitOR(BitXOR($c, BitOR($b, (BitNOT($d)))) + $x[$k + 0x8],0) + 0x6FA87E4F,0),0),0x06,"D")+$b,0)
        $d = BitOR(BitRotate(BitOR($d + BitOR(BitOR(BitXOR($b, BitOR($a, (BitNOT($c)))) + $x[$k + 0xF],0) + 0xFE2CE6E0,0),0),0x0A,"D")+$a,0)
        $c = BitOR(BitRotate(BitOR($c + BitOR(BitOR(BitXOR($a, BitOR($d, (BitNOT($b)))) + $x[$k + 0x6],0) + 0xA3014314,0),0),0x0F,"D")+$d,0)
        $b = BitOR(BitRotate(BitOR($b + BitOR(BitOR(BitXOR($d, BitOR($c, (BitNOT($a)))) + $x[$k + 0xD],0) + 0x4E0811A1,0),0),0x15,"D")+$c,0)
        $a = BitOR(BitRotate(BitOR($a + BitOR(BitOR(BitXOR($c, BitOR($b, (BitNOT($d)))) + $x[$k + 0x4],0) + 0xF7537E82,0),0),0x06,"D")+$b,0)
        $d = BitOR(BitRotate(BitOR($d + BitOR(BitOR(BitXOR($b, BitOR($a, (BitNOT($c)))) + $x[$k + 0xB],0) + 0xBD3AF235,0),0),0x0A,"D")+$a,0)
        $c = BitOR(BitRotate(BitOR($c + BitOR(BitOR(BitXOR($a, BitOR($d, (BitNOT($b)))) + $x[$k + 0x2],0) + 0x2AD7D2BB,0),0),0x0F,"D")+$d,0)
        $b = BitOR(BitRotate(BitOR($b + BitOR(BitOR(BitXOR($d, BitOR($c, (BitNOT($a)))) + $x[$k + 0x9],0) + 0xEB86D391,0),0),0x15,"D")+$c,0)

        $a = BitOR($a + $AA,0)
        $b = BitOR($b + $BB,0)
        $c = BitOR($c + $CC,0)
        $d = BitOR($d + $DD,0)
    Next

    Return StringLower(StringMid(Hex($a),7,2) & StringMid(Hex($a),5,2) & StringMid(Hex($a),3,2) & StringMid(Hex($a),1,2) & _
           StringMid(Hex($b),7,2) & StringMid(Hex($b),5,2) & StringMid(Hex($b),3,2) & StringMid(Hex($b),1,2) & _
           StringMid(Hex($c),7,2) & StringMid(Hex($c),5,2) & StringMid(Hex($c),3,2) & StringMid(Hex($c),1,2) & _
           StringMid(Hex($d),7,2) & StringMid(Hex($d),5,2) & StringMid(Hex($d),3,2) & StringMid(Hex($d),1,2))
EndFunc   ;==>MD5