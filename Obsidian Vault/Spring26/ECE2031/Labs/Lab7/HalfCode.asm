ORG 0
	LOADI 20
	SUB   Value
    STORE Temp

Loop:
	LOADI -1
    JNZ	  Loop

ORG 31
	Value: DW 30
  	Temp:  DW 0
