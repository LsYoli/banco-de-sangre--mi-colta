
CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lcurl

SRC = main.cpp BloodDatabase.cpp Donor.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = programa

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
