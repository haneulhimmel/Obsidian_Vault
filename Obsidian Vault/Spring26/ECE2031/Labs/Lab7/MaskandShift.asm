ORG 0
	LOAD Value
    SHIFT -8
    AND Lowmask
    STORE Highbyte
    
    LOAD Value
    AND Lowmask
    STORE Lowbyte
    
    LOAD Highbyte
    SUB	 Lowbyte
    JNEG LowtoHigh
    
    STORE Result
    JUMP Loop

LowtoHigh:
	LOAD Lowbyte
    SUB Highbyte
    STORE Result

Loop:
    JUMP Loop

ORG 100
	Result: DW 0
    
ORG 200
    Value:      DW 61440
    LowMask:    DW 255
    Highbyte: DW 0
    Lowbyte: DW 0
