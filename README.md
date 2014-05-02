Qustodio test by Jesus Fernandez

Requirements:
- boost
- qmake binary (in the Qt distribution)

Building:
qmake
make

* Using BOOST_PATH environment variable may be necessary to find boost libraries.

Creating projects for Visual Studio:
qmake -tp vc -recursive