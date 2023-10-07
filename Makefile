CXX=g++
CXXFLAGS=-std=c++17 -Wall -Werror -Wextra -pedantic -UQT_MACRO
GCOV=--coverage
OUTNAME=tests
TFN = model/tests/unit_tests.cc


.PHONY: all
all: tests cmake install

.PHONY: cmake
cmake:
	mkdir -p build && cd build && cmake ..

.PHONY: build
build: cmake
	cd build && make

.PHONY: tests
tests: model/tests/unit_tests.cc
	gcc $< -lstdc++ -lgtest -std=c++17 -Wall -Werror -Wextra -o unit_tests
	cd model/tests
	./unit_tests

.PHONY: leaks
leaks: model/tests/unit_tests.cc
	gcc $< -lstdc++ -lgtest -std=c++17 -Wall -Werror -Wextra -o unit_tests
	cd model/tests
	leaks --atExit -- ./unit_tests

gcov_report: clean
	gcc  --coverage $(TFN) -o gcov_report -lgtest -lstdc++
	./gcov_report
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html

.PHONY: dist
dist:
	zip -r my_arch.zip *
	# @tar -cf SmartCalc.tar *.cc *.h Makefile build

.PHONY: dvi
dvi:
	open dvi.html

install: build
	@mkdir $(HOME)/Desktop/SmartCalc_v2.0/
	mv build/output/amd64/view/qcp/SmartReckoner.app $(HOME)/Desktop/SmartCalc_v2.0/

.PHONY: uninstall
uninstall:
	@rm -rf build*
	@rm -rf $(HOME)/Desktop/SmartCalc_v2.0/

.PHONY: clean
clean:
	rm -rf build ./*.o ./*.a ./a.out ./*.gcno ./*.gcda ./gcov_report *.info ./*.info unit_tests