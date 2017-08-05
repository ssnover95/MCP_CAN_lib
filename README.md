This project is a fork of the excellent `MCP_CAN_lib` project by Cory J Fowler 
and Seeed Studio ([repository](https://github.com/coryjfowler/MCP_CAN_lib)).
#Purpose
In this project, I'll be developing a C++ CAN Controller module compatible 
with the Arduino CAN Shield based on the MCP2515 CAN Controller. In doing so, 
I'll be practicing my modern C++ development skills and learning to use CMake 
for build management.

#Goals
* Design, document, and implement a CAN Controller module which uses a MCP2515 
Driver module.
* Convert the `examples/` to build via the tool CMake.
* Set up CMake build target to produce object file for inclusion in AVR project.
* _Maybe_: Set up Google Test and Mock for unit testing.

#End Product
The primary customer for this project is embedded developers using the 8-bit 
Atmega AVR microcontroller family. The user should be able to build an object 
file from this source for use in their own AVR-based projects. This should 
support the use of the Arduino Uno R3 development board with a CAN Shield as 
well as custom hardware using an AVR and the MCP2515 CAN Controller.

I am not aiming to support integration into Arduino libraries at this point.