NAME = ICP-Project
PROJECT_FILE = ./src/ICP-Project.pro
QMAKE_MAKEFILE = ./QMakefile
ZIP_NAME = xdanie14-xjanst02.zip
ZIP_FILES = ./doc/ ./examples/ ./src/ Makefile LICENSE README.txt


default: build

build:
	qmake $(PROJECT_FILE) -o $(QMAKE_MAKEFILE)
	$(MAKE) -f $(QMAKE_MAKEFILE) -o $(NAME)

run:
	./$(NAME)

clean:
	$(MAKE) -f $(QMAKE_MAKEFILE) clean

doxygen:
	doxygen doc/Doxyfile
    
pack:
	zip -r $(ZIP_NAME) $(ZIP_FILES)
