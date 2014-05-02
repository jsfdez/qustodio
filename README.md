# Qustodio test by Jesus Fernandez

## Requirements:
- boost
- qmake binary (in the Qt distribution)

## Building:
```
qmake
make
```

_Using BOOST_PATH environment variable may be necessary to find boost libraries before calling qmake._

## Creating projects for Visual Studio:
```
qmake -tp vc -recursive
```

## Third party libraries used: ##
* **Boost**: 
 * **Boost::asio**: Cross-platorform network library.
 * **Boost::test**: Cross-platform testing framework.
* **Rapidjson**: Message parsing/formating. I used json format for extensibility.
