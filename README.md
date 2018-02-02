# eGTHackathon

Updated 

Visual Studio Folder containing the UI used during the hackathon.

Steps for set up (Runs on Windows only):

1. Install Visual Studio 2015
https://msdn.microsoft.com/en-us/library/e2h7fzkw.aspx

2. Install QT 5.8
a. Toolkit for creating Graphical User Interface (GUIs).
b. Can be downloaded for free here:
http://download.qt.io/official_releases/online_installers/qt-unified-windows-x86-online.exe
c. Run the downloaded executable to install the software.
d. During installing process, you'll be asked ot create a QT login and password.
e. Use the defualt settings during installation.

3. Intstall VS QT Tools for Visual Studios 2015
a. Can be downloaded for free here:
http://download.qt.io/official_releases/vsaddin/qt-vs-tools-msvc2015-2.0.0.vsix
b. Run the downloaded file.
c. Run QT 5.8 64 bit for Desktop (MSVC  2015)
d. Add QT version 5.8 to Visual Studio
e. Open Visual Studio 2015
f. Clock on the QT VS Tools > QT Options > QT Versions Menu
g. Add a version named msvs2015_64 and give it a path C:\QT\5.8\msvc2015_64
h. In the Default QT/Win version: select the option you just added.
          
4. After successful isntallation, you should be able to compile and run the program from within Visual Studio 2015.
