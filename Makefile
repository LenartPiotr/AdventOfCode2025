# Ustawienia kompilatora
CXX      := g++
CXXFLAGS := -std=c++2a -Wall -Wextra -O3 -Iinclude
LDFLAGS  := 

# Katalogi
SRC_DIR := src
OUT_DIR := out

# Pliki wspólnej biblioteki (wszystko w src/)
LIB_SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
LIB_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(OUT_DIR)/%.o, $(LIB_SOURCES))

# Dni (zadania)
DAYS    := 2 3 4 5 6 7
TARGETS := $(patsubst %, $(OUT_DIR)/day%.exe, $(DAYS))

# Domyślna akcja - kompiluje wszystko
all: $(TARGETS)

# Kompilacja wspólnych plików .cpp na obiekty .o
$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Kompilacja konkretnego dnia i linkowanie z bibliotekami
$(OUT_DIR)/day%.exe: day%.cpp $(LIB_OBJECTS)
	$(CXX) $(CXXFLAGS) $< $(LIB_OBJECTS) -o $@ $(LDFLAGS)

# Uruchamianie konkretnego dnia (np. make run DAY=1)
run:
	@./$(OUT_DIR)/day$(DAY).exe

# Czyszczenie plików binarnych
clean:
	rm -rf $(OUT_DIR)

.PHONY: all prepare clean run