
# Compilador
CXX = g++
CXXFLAGS = -std=c++17 -Wall -lcurl

# Archivos fuente del proyecto
SRC = main.cpp BloodDatabase.cpp Donor.cpp

# Archivos para pruebas unitarias
TEST_SRC = tests/test_blood_database.cpp Donor.cpp BloodDatabase.cpp
TEST_EXE = test_program
GTEST_FLAGS = -lgtest -lgtest_main -pthread

# Ejecutable principal
TARGET = programa

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

test: $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(GTEST_FLAGS) $(TEST_SRC) -o $(TEST_EXE) -lcurl

clean:
	rm -f $(TARGET) $(TEST_EXE)
