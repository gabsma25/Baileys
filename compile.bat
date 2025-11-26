@ECHO OFF
TITLE Compilando FACE Game...
COLOR 0A

ECHO ========================================
ECHO      FACE - Compilacao Rapida
ECHO ========================================
ECHO.

:: Configurar PATH
SET PATH=%PATH%;%CD%;%CD%\include;%CD%\include\box2d;C:\SFML-3.0.0;C:\SFML-3.0.0\include;C:\SFML-3.0.0\include\SFML-3.0.0;C:\SFML-3.0.0\bin;C:\SFML-3.0.0\lib;C:\mingw64\bin;C:\mingw64\x86_64-w64-mingw32\bin;C:\Program Files\PostgreSQL\16\bin

:: Limpar compilacao anterior
IF EXIST face-game.exe (
    ECHO [INFO] Removendo executavel anterior...
    DEL face-game.exe
)

ECHO [INFO] Compilando...
ECHO.

:: Compilar
g++ -std=c++17 ^
    main.cpp ^
    src/Core/Game.cpp ^
    src/Core/SceneManager.cpp ^
    src/Scenes/MenuScene.cpp ^
    src/Scenes/QuizScene.cpp ^
    src/Scenes/FaceScene.cpp ^
    src/Utils/FontManager.cpp ^
    src/Database/DatabaseManager.cpp ^
    -o face-game.exe ^
    -I include ^
    -I C:/SFML-3.0.0/include ^
    -I C:/PROGRA~1/POSTGR~1/16/include ^
    -L C:/SFML-3.0.0/lib ^
    -L C:/PROGRA~1/POSTGR~1/16/lib ^
    -lsfml-graphics ^
    -lsfml-window ^
    -lsfml-system ^
    -lpq ^
    -O2 ^
    -Wall ^
    -Wextra

:: Verificar sucesso
IF %ERRORLEVEL% EQU 0 (
    ECHO.
    ECHO ========================================
    ECHO    COMPILACAO BEM-SUCEDIDA!
    ECHO ========================================
    ECHO.
    ECHO Executavel criado: face-game.exe
    ECHO.
    ECHO Pressione qualquer tecla para executar...
    PAUSE >NUL
    face-game.exe
) ELSE (
    ECHO.
    ECHO ========================================
    ECHO    ERRO NA COMPILACAO!
    ECHO ========================================
    ECHO.
    ECHO Verifique os erros acima.
    ECHO.
)

PAUSE
