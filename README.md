#Wursty - a wurst dependency manager

Wursty is a very simple dependency manager for [Wurst](https://github.com/peq/WurstScript) projects/packages.

##How to use it?
First compile wursty so you get wursty.exe. Place this .exe in your wurst project.
Then, create a 'dependencies' file (without quotes) and place it in your wurst project too (this file will contain all the dependencies and its versions).

##How to write a dependencies file?
Its simple, the format is:

```
<dependency repository url>,<version/commit>
<dependency repository url>,<version/commit>
```

**Note:** Version are not supported yet, so avoid them (just write the dependency url), example:
```
<dependency repository url>
<dependency repository url>
```

Example
```
http://github.com/Ruk33/somepackage.git,HEAD
http://github.com/Ruk33/other_somepackage.git,a4537c55af4cdc563efbcaade51650030a1ca20e
```

If no version is pointed, HEAD will be.

##I have the .exe in the root folder and the dependencies file created, what now?
Simple run this command

```
cd wurst/project && wursty run
```

##What happens if a dependency is requested in multiple versions?
It will (when implemented) only display an error message (I know, high tech).

##How to compile?
```
cd path/to/wursty && make wursty
```

##How to run tests?
```
cd path/to/wursty/tests && make <test to run> && <test to run>
```

Example running dependency tests
```
cd path/to/wursty/tests && make dependency && dependency
```