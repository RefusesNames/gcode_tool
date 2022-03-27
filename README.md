# Configure

## Install libaries
```sh
mkdir build/conan
cd build/conan

conan install ../..

# to use a custom conan profile, use this command and build the libraries
# conan install ../.. -pr=[your profile name] --build=missing 

# don't forget to return to the project folder 
cd ../..
```

## Create solution files
```sh
premake5 vs2019
```

# Build

## Debug
```sh
msbuild gcode_tool.sln
```

## Release
```sh
msbuild .\gcode_tool.sln -p:Configuration=Release
```

# Run

## Debug
```sh
.\bin\Debug\gcode_tool.exe
```

## Release
```sh
.\bin\Release\gcode_tool.exe
```

# Generate compilation database

This step requires the [Clang Power Tools](https://clangpowertools.com/) extension for Visual Studio as well as [this script](https://raw.githubusercontent.com/Caphyon/clang-power-tools/master/ClangPowerTools/ClangPowerToolsShared/Tooling/v1/clang-build.ps1) for it, which is already included here.


```sh
./clang-build -export-jsondb

```
