LibreCAM
========

A CAM plugin for LibreCAD


Installation
========
Within your LibreCAM directory go to your plugins directory and execute:

git clone https://github.com/LibreCAM/LibreCAM.git

Your plugins directory should look like this:
.
|-- LibreCAM
|-- Makefile
|-- README.plugins
|-- asciifile
|-- plugins.pro
..
..
`-- sample

Edit the file plugins.pro and add LibreCAM to the SUBDIRS section.

Now you can compile LibreCAD and LibreCAM and it will be deployed as such into the resources directory during compilation.
