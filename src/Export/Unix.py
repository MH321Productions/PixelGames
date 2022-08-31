#!/usr/bin/python3

import sys
from pathlib import Path
import shutil

# A list of all paths to the game executables
# (Relative to the build directory)
games = [
    "src/Pong-Single/Pong-Single"
]

# A list of all paths to the linked dynamic libraries
# (Relative to the build directory)
libs = [
    "lib/SFML/lib/libsfml-audio.so.3.0.0",
    "lib/SFML/lib/libsfml-graphics.so.3.0.0",
    "lib/SFML/lib/libsfml-network.so.3.0.0",
    "lib/SFML/lib/libsfml-system.so.3.0.0",
    "lib/SFML/lib/libsfml-window.so.3.0.0"
]

# A list of all paths to the resource files
# (Relative to the main directory)
res = [
    
]

def checkMainDir(mainDir):
    base = Path(mainDir)
    
    if base.exists() == False:
        return False
    
    r = base.joinpath("res")
    return r.exists() and r.is_dir()

#Main Program
if len(sys.argv) < 3:
    print("Not enough arguments!")
    print("Usage: Unix.py <Main dir> <Build dir>")
    exit(1)

mainDir = sys.argv[1]
buildDir = sys.argv[2]

#Check directories
if checkMainDir(mainDir) == False:
    print("Invalid main directory")
    exit(1)

if Path(buildDir).exists() == False:
    print("Invalid build path")
    exit(1)

#Create paths
mainPath = Path(mainDir)
buildPath = Path(buildDir)
exportPath = buildPath.joinpath("PixelGames")
binPath = exportPath.joinpath("bin")
resPath = exportPath.joinpath("res")

if exportPath.exists():
    print("Deleting export dir")
    shutil.rmtree(exportPath)

exportPath.mkdir()
binPath.mkdir()
resPath.mkdir()

#Copy files
print(f"Copying {len(games)} programs")
for item in games:
    shutil.copy(buildPath.joinpath(item), binPath)

print(f"Copying {len(libs)} libraries")
for item in libs:
    shutil.copy(buildPath.joinpath(item), binPath)

print(f"Copying {len(res)} resources")
for item in res:
    shutil.copy(mainPath.joinpath(item), resPath)