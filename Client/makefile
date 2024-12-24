# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wno-deprecated-declarations

# Каталоги и файлы
SRCDIR = .
SRC_CLIENT = main.cpp ConnHandler.cpp DataHandler.cpp Error.cpp sha256.cpp CommandLineDecoder.cpp
SRC_TEST = test.cpp ConnHandler.cpp DataHandler.cpp Error.cpp sha256.cpp CommandLineDecoder.cpp
OBJ_CLIENT = $(SRC_CLIENT:.cpp=.o)
OBJ_TEST = $(SRC_TEST:.cpp=.o)
TARGET_CLIENT = client
TARGET_TEST = test

# Флаги и библиотеки
LDFLAGS_CLIENT = -lcryptopp
LDFLAGS_TEST = -lcryptopp -lUnitTest++

# Правила
all: $(TARGET_CLIENT) $(TARGET_TEST) clean

$(TARGET_CLIENT): $(OBJ_CLIENT)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS_CLIENT)

$(TARGET_TEST): $(OBJ_TEST)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS_TEST)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o

.PHONY: all clean
