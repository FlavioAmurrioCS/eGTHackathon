# eGTHackathon

Updated 

Visual Studio Folder containing the UI used during the hackathon.

Steps for set up (Runs on Windows only):

1. Install Visual Studio 2015


2. Install QT 5.8
-Toolkit for creating Graphical User Interface (GUIs).
-Can be downloaded for free here:
http://download.qt.io/official_releases/online_installers/qt-unified-windows-x86-online.exe
-Run the downloaded executable to install the software.
    -During installing process, you'll be asked ot create a QT login and password.
    -Use the defualt settings during installation.

3. Intstall VS QT Tools for Visual Studios 2015
-Can be downloaded for free here:
http://download.qt.io/official_releases/vsaddin/qt-vs-tools-msvc2015-2.0.0.vsix
    -Run the downloaded file.
    -Run QT 5.8 64 bit for Desktop (MSVC  2015)
    -Add QT version 5.8 to Visual Studio
          -Open Visual Studio 2015
          -Clock on the QT VS Tools > QT Options > QT Versions Menu
          -Add a version named msvs2015_64 and give it a path C:\QT\5.8\msvc2015_64
          -In the Default QT/Win version: select the option you just added.
          
4. After successful isntallation, you should be able to compile and run the program from within Visual Studio 2015.
