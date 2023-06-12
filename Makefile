GCSTUFF = g++ -std=c++11
BELLS = -g -Wextra
.PHONY: clean

allIt:	project3.out clean

project3.out: big3.cpp Board.o BottomStuff.o PIC.o Randinator.o Tile.o
	$(GCSTUFF) $(BELLS) big3.cpp Board.cpp BottomStuff.cpp PIC.cpp Randinator.cpp Tile.cpp -o $@
	project3.out
	
Board.o: Board.cpp
	$(GCSTUFF) $(BELLS) -c $< -o $@
	
BottomStuff.o: BottomStuff.cpp
	$(GCSTUFF) $(BELLS) -c $< -o $@
	
PIC.o: PIC.cpp
	$(GCSTUFF) $(BELLS) -c $< -o $@
	
Randinator.o: Randinator.cpp
	$(GCSTUFF) $(BELLS) -c $< -o $@
	
Tile.o: Tile.cpp
	$(GCSTUFF) $(BELLS) -c $< -o $@
	
clean:
#	del project3.out
#	del /s output\*.tga
	del /s *.o