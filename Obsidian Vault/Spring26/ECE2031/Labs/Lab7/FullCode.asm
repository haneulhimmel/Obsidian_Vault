ORG 0

Loop:
	LOADI 20
	SUB   Value
    STORE Temp
    
    JNZ	  Loop

ORG 31
	Value: DW 30
  	Temp:  DW 0
