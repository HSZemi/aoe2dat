# aoe2dat
Extract Unit and Tech data from the Age of Empires II dat file

## Cloning this repository

This repository uses git submodules, so clone it like this:

```
git clone --recurse-submodules <url>
```

## Compiling

You will need cmake >3.0.0 and (some development dependencies).

```
cd code
mkdir build
cd build
cmake ..
cmake --build .
```

You should get a `aoe2dat` executable in the `build` folder.

## Using

Call the `aoe2dat` executable with your `dat` file as an argument, for example:

```
./aoe2dat ~/aoe/Aoe2DE\ proton/resources/_common/dat/empires2_x2_p1.dat
```

You will get some console output and two files will be created in your current directory: 

- `full.json` which contains all extracted data, and 
- `units_buildings_techs.json`, a subset of the data which is used for [Halfon](https://github.com/SiegeEngineers/halfon).

## Useful Paths

### Units

```
data->Civs[civ]->Units[i]->HitPoints
data->Civs[civ]->Units[i]->Type50->DisplayedAttack
data->Civs[civ]->Units[i]->Type50->DisplayedMeleeArmour
data->Civs[civ]->Units[i]->Creatable->DisplayedPierceArmour
data->Civs[civ]->Units[i]->Creatable->ResourceCosts[Type=0]->Amount //Food
data->Civs[civ]->Units[i]->Creatable->ResourceCosts[Type=1]->Amount //Wood
data->Civs[civ]->Units[i]->Creatable->ResourceCosts[Type=2]->Amount //Stone
data->Civs[civ]->Units[i]->Creatable->ResourceCosts[Type=3]->Amount //Gold
```
