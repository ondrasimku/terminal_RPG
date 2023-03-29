PROGRAM=simkuond
CC=g++
CFLAGS= -std=c++17 -Wall -pedantic -g -lstdc++fs
BUILD_DIR=build
DOXYFILE=Doxyfile

all: $(PROGRAM)
	rm -f $(PROGRAM)
	mkdir -p examples/saves

compile: $(PROGRAM)

run:
	./$(PROGRAM)

clean:
	- rm $(PROGRAM)
	- rm -rf $(BUILD_DIR)
	- rm -rf doc

doc:
	mkdir -p doc
	doxygen $(DOXYFILE)

$(PROGRAM): $(BUILD_DIR)/Player.o $(BUILD_DIR)/Weapon.o $(BUILD_DIR)/Main.o $(BUILD_DIR)/Item.o $(BUILD_DIR)/Game.o $(BUILD_DIR)/Entitiy.o $(BUILD_DIR)/Arena.o $(BUILD_DIR)/Console.o $(BUILD_DIR)/classes/weapons/Sword.o $(BUILD_DIR)/classes/weapons/Knife.o\
 $(BUILD_DIR)/classes/weapons/Bow.o $(BUILD_DIR)/classes/weapons/Axe.o $(BUILD_DIR)/classes/potions/Health.o $(BUILD_DIR)/classes/potions/Strength.o $(BUILD_DIR)/classes/misc/Key.o $(BUILD_DIR)/classes/locations/GameStart.o\
 $(BUILD_DIR)/classes/locations/Location.o $(BUILD_DIR)/classes/locations/Eriador/Eriador.o $(BUILD_DIR)/classes/locations/Hrad/Hrad.o $(BUILD_DIR)/classes/locations/Komnata/Komnata.o\
 $(BUILD_DIR)/classes/locations/Les/Les.o $(BUILD_DIR)/classes/locations/Louka/Louka.o $(BUILD_DIR)/classes/entities/Human.o $(BUILD_DIR)/classes/entities/Wendigo.o $(BUILD_DIR)/classes/entities/Rhaaba.o\
 $(BUILD_DIR)/classes/entities/Ragnarok.o
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/Player.o: src/Player.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

 $(BUILD_DIR)/Weapon.o: src/Weapon.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/Main.o: src/Main.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/Item.o: src/Item.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/Game.o: src/Game.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/Entitiy.o: src/Entity.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@


$(BUILD_DIR)/Arena.o: src/Arena.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/Console.o: src/Console.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/classes/weapons/Sword.o: src/classes/weapons/Sword.cpp
	mkdir -p $(BUILD_DIR)/classes/weapons/
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/classes/weapons/Knife.o: src/classes/weapons/Knife.cpp
	mkdir -p $(BUILD_DIR)/classes/weapons/
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/classes/weapons/Axe.o: src/classes/weapons/Axe.cpp
	mkdir -p $(BUILD_DIR)/classes/weapons/
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/classes/weapons/Bow.o: src/classes/weapons/Bow.cpp
	mkdir -p $(BUILD_DIR)/classes/weapons/
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/classes/potions/Health.o: src/classes/potions/Health.cpp
	mkdir -p $(BUILD_DIR)/classes/potions/
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/classes/potions/Strength.o: src/classes/potions/Strength.cpp
	mkdir -p $(BUILD_DIR)/classes/potions/
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/classes/misc/Key.o: src/classes/misc/Key.cpp
	mkdir -p $(BUILD_DIR)/classes/misc/
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/classes/locations/GameStart.o: src/classes/locations/GameStart.cpp
	mkdir -p $(BUILD_DIR)/classes/locations/
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/classes/locations/Location.o: src/classes/locations/Location.cpp
	mkdir -p $(BUILD_DIR)/classes/locations/
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/classes/locations/Eriador/Eriador.o: src/classes/locations/Eriador/Eriador.cpp
	mkdir -p $(BUILD_DIR)/classes/locations/Eriador/
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/classes/locations/Hrad/Hrad.o: src/classes/locations/Hrad/Hrad.cpp
	mkdir -p $(BUILD_DIR)/classes/locations/Hrad/
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/classes/locations/Komnata/Komnata.o: src/classes/locations/Komnata/Komnata.cpp
	mkdir -p $(BUILD_DIR)/classes/locations/Komnata/
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/classes/locations/Les/Les.o: src/classes/locations/Les/Les.cpp
	mkdir -p $(BUILD_DIR)/classes/locations/Les/
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/classes/locations/Louka/Louka.o: src/classes/locations/Louka/Louka.cpp
	mkdir -p $(BUILD_DIR)/classes/locations/Louka/
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/classes/entities/Human.o: src/classes/entities/Human.cpp
	mkdir -p $(BUILD_DIR)/classes/entities/
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/classes/entities/Wendigo.o: src/classes/entities/Wendigo.cpp
	mkdir -p $(BUILD_DIR)/classes/entities/
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/classes/entities/Rhaaba.o: src/classes/entities/Rhaaba.cpp
	mkdir -p $(BUILD_DIR)/classes/entities/
	$(CC) $(CFLAGS) -c $^ -o $@

 $(BUILD_DIR)/classes/entities/Ragnarok.o: src/classes/entities/Ragnarok.cpp
	mkdir -p $(BUILD_DIR)/classes/entities/
	$(CC) $(CFLAGS) -c $^ -o $@
