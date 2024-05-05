# ICP Project 2023/2024
# @file Makefile
# @author Tomáš Daniel (xdanie14)
# @author Jakub Janšta (xjanst02)
# @brief Makefile producing QT Makefile using qmake and containing all other required targets.

NAME = src/ICP-Project
PROJECT_FILE = src/ICP-Project.pro
QMAKE_MAKEFILE = src/Makefile
ZIP_NAME = xdanie14-xjanst02.zip
ZIP_FILES = doc/ examples/ src/ Makefile LICENSE README.txt


default: build

build:
	@qmake $(PROJECT_FILE) -o $(QMAKE_MAKEFILE)
	@$(MAKE) -C src/ -o $(NAME)

run: build
	@$(NAME)

clean: build
	@$(MAKE) -C src/ clean
	@rm -rf $(QMAKE_MAKEFILE) $(NAME) src/.qmake.stash doc/html doc/latex

doxygen:
	doxygen doc/Doxyfile

pack: clean
	@if [ -f $(ZIP_NAME) ]; then \
		rm $(ZIP_NAME); \
	fi
	@zip -r $(ZIP_NAME) $(ZIP_FILES)
