CC = g++
CPPFLAGS = -lgtest -lstdc++ -std=c++17
CHECKFLAGS = -Wall -Werror -Wextra
SRCS = src/Model/affine_strategy.cpp \
src/Model/file_reader.cpp \
src/Model/s21_matrix_oop.cpp

MODULES_CPP=src/Model/*.cpp src/*.cpp src/Controller/*.cpp
MODULES_H=src/Model/*.h src/*.h src/Controller/*.h

OS:=$(shell uname -s)

SUP = --suppress=

all: install run

tests: src/s21_test.cpp
	${CC} ${CHECKFLAGS} ${CPPFLAGS} src/s21_test.cpp ${SRCS} -o src/test
	@./src/test

clean:
	@/bin/rm -rf src/*.o src/*.a src/test src/*.out src/moc_*

style:
	cp -r materials/linters/CPPLINT.cfg src/
	python3 materials/linters/cpplint.py --extensions=cpp $(MODULES_CPP) $(MODULES_H)
	rm -rf src/CPPLINT.cfg

cppcheck:
	cppcheck --enable=all $(SUP)useStlAlgorithm $(SUP)unusedFunction $(SUP)missingInclude $(SUP)unmatchedSuppression $(MODULES_CPP)

leaks: tests
ifeq ($(OS), Darwin)
	leaks --atExit -- ./src/test
else
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./src/test
endif

install: uninstall
	mkdir build
	cp -r src/* build
	cd build; qmake -makefile Viewer_v2.pro
	make -C build
	make clean -C build

uninstall:
	@rm -rf build
	
dist: install
	@tar -zcf Viewer_v2.tar build/Viewer_v2.app

dvi:
	open src/dvi.html

run:
ifeq ($(OS), Darwin)
	./build/Viewer_v2.app/Contents/MacOS/Viewer_v2
else
	./build/Viewer_v2
endif
