CC = g++

RM = rm -f

OBJS = src/ScoringMatrix.h src/ScoringMatrix.cpp src/Align.h src/Align.cpp src/Import.h src/Import.cpp src/main.cpp

MAIN = bioinfo-tp1

$(MAIN): $(OBJS)
	@$(CC) $(OBJS) -o $(MAIN)

clean:
	$(RM) $(MAIN) *.o
	clear

run: $(MAIN)
	./$(MAIN)
