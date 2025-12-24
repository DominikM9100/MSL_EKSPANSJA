# kompilator i flagi
CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra

# katalogi
SRC_DIR   := src
INC_DIR   := inc
OBJ_DIR   := obj
BIN_DIR   := bin
DANE_DIR  := dane

# sciezki do nagłowkow
INCLUDE_DIRS := $(INC_DIR) $(SRC_DIR)
CPPFLAGS  := $(addprefix -I,$(INCLUDE_DIRS))

# pliki
SOURCES   := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS   := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
DEPS      := $(OBJECTS:.o=.d)
TARGET    := $(BIN_DIR)/minimalizacja

# domyslny cel
all: $(TARGET)

# linkowanie
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# kompilacja + automatyczne zaleznozci
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

# katalogi posrednie
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# uruchomienie
run: $(TARGET)
	./$(TARGET)

# warianty
debug: CXXFLAGS += -g -O0
debug: $(TARGET)

release: CXXFLAGS += -O2 -DNDEBUG
release: $(TARGET)

# sprzatanie
clean:
	rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d
	rm -rf $(BIN_DIR)/*

distclean: clean
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# info / pomoc
info:
	@echo "Struktura projektu:"
	@echo "  Zrodla:          $(SRC_DIR)"
	@echo "  Naglowki:        $(INC_DIR)"
	@echo "  Obiekty:         $(OBJ_DIR)"
	@echo "  Pliki binarne:   $(BIN_DIR)"
	@echo "  Dane:            $(DANE_DIR)"
	@echo "  Pliki zrodlowe:  $(SOURCES)"
	@echo "  Pliki obiektowe: $(OBJECTS)"

help:
	@echo "Dostępne polecenia:"
	@echo "  make            - kompiluje projekt (domyslnie)"
	@echo "  make debug      - kompiluje z informacjami debugowania"
	@echo "  make release    - kompiluje z optymalizacjami"
	@echo "  make run        - uruchamia program"
	@echo "  make clean      - usuwa pliki obiektowe i wykonywalne"
	@echo "  make distclean  - czysci caly projekt"
	@echo "  make info       - wypisuje informacje o projekcie"

.PHONY: all clean distclean run debug release info help

# dolacz wygenerowane zaleznosci naglowkow
-include $(DEPS)
