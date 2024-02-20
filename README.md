# ICP-Project
Repository for FIT VUT ICP project.

*******************************************************************************

## Coding style rules:

    1. Indentation:                     4 spaces
    2. Variable and function names:     snake_case
        f.e. name_of_function (...)
    3. Type and structure names:        PascalCase
        f.e. StructName {...},
        class name
    4. Constant/maker names:            SCREAMING_SNAKE_CASE
        f.e. #define CONST_NAME 1
    5. Pointers names:                  with var's data type
        e.g. int* name;
    6. Compound parentheses:            on the same line
        f.e. method (...) {
            ...
        }
    7. Spaces around binary operators
        f.e. a + b;
    8. For, while, if:                 spaces before the bracket
        f.e. for (...)
    9. Spaces after a comma, semicolon, bracket

### Push strategy:                       requests

## Setup:
  #### 1) Install QT Creator ver. 5.6.0 (qt-opensource-windows-x86-mingw492-5.6.0.exe) [MINGW is required to be installed]:
  ```
  https://download.qt.io/new_archive/qt/5.6/5.6.0/
  ```
  #### 2) Follow manual to use Git alongside with QT Creator:
  ```
  https://cpb-us-w2.wpmucdn.com/u.osu.edu/dist/7/11881/files/2018/02/QtCreatorGitTutorial-2ahr2m0.pdf
  ```
  #### 3) Find suitable IDE to code, in my case: VsCode for code editing and Git operations + QT Creator for compiling

## Axis:
       Y
       ^
       |
       |
       |
    [0, 0] - - - > X

## Rotation:
#### -> COUNTER-Clockwise
    Internally all the angles are represented in radians.
-------------------------------------------------------------------------------
