Game:
	gcc Main.c utilities.c PrintBoard.c GenerateValues.c cJSON.c -o Main

clean:
	del *.obj
	del *.exe
	del *.lib