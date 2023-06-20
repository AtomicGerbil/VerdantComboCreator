# VerdantComboCreator
Really simplistic tool that is used to provide some architectural design to making weapons w/ the Verdant Library.
The purpose of this tool is to provide some level of architectural design.

This doesn't really create "combos" per-se, but essentially stitches multiple JSON files into a singular output.

The motivation was to allow modders to be able to split dense portions of JSON and work on them separately, providing some level of organisation.
Creating combos can feel bulky and leads to erroneous creations at times, since it is cumbersome to scroll through.

This uses `getopt`; this DLL is necessary, so if you ever move the executable, move that file with it.

## Assumptions

This application makes the following assumptions:

You know how to work a CLI.

If you don't provide any arguments to VCC.exe, it will use default initialised vars.
These are:
1. Weapon Config: `weaponFile.config`
2. Combo Filepath: `./combos/`


Your file names for the combos follows the style of `comboN.json`, where `N` is a number. 
The program reads from 1 and increments until it has filled out all combo keys.

Along with the above assumption, you understand that `formNames` is used to determine where combos are placed.

    I.E: Let's say the first value in key `formNames` is `default`;
    `combo1.json`'s contents are written into:
    
    "default" : { "combo" : [//VCC.exe dumps combo1.json contents into here//] } 
    
     It then moves onto the next form.

# How to Use

This will cover how to utilise the executable.

## Prerequisites
Download the latest release build of the project.
This should contain the executable and `getopt.dll`.

## Format

The arguments for the executable are:
- `-w` : Provide a path & file to the main weapon config.
- `-c` : Provide the path to where you keep your combo files.

An example: `> .\VCC.exe -w kikiBlade.config -c .\combos\`.

# TODO:
- Add option `-o` with a require value when using the option, allowing the user to name the output.
  (Output extension will ALWAYS be `.config`).
  
- Update this README.md whenever I make such a change, cuz I know I will forget.
