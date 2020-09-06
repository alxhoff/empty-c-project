# empty-c-project
Empty C project with VS Code integration

## How to use

### Command line

``` bash
cd build
cmake ..
make
```

### VS Code

Firstly from the command line:

1. Navigate to the `build` folder within the `empty-c-project` folder

2. Invoke CMake with VSCode support `cmake -DUSE_IDE=vscode ..`

Now not on the command line:

1. Open VSCode

2. Dismiss welcome screen

3. In menu `File->Open (Folder)`
  - Navigate to the folder containing this code, probably named `empty-c-project`

4. Install the reccomended extensions, will show up in a box in the bottom right corner

5. Open the source files you want to edit

#### Targets

There are configs for a number of VSCode tasks, this is done via `Terminal->Run Task`.

To build use the `Run` task, this will also compile the code if you have made changes and saved them.

To debug you can simply navigate to `Run->Start Debugging` or just press **F5**.
