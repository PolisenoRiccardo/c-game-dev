# Nome del tuo programma finale
TARGET = game

# File sorgenti (per ora solo uno)
SOURCES = pong.c

# Librerie SDL2 necessarie
LIBS = -lSDL2 -lSDL2main -lm

# Flags del compilatore
CFLAGS = -Wall -Wextra -std=c99 -g

# Regola principale - cosa succede quando scrivi "make"
$(TARGET): $(SOURCES)
	gcc $(CFLAGS) -o $(TARGET) $(SOURCES) $(LIBS)

# Regola per pulire i file compilati
clean:
	rm -f $(TARGET)

# Regola per eseguire dopo aver compilato
run: $(TARGET)
	./$(TARGET)
