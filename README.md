# aoe2dat
Unit and Tech data, extracted from the Age of Empires II dat file

## Structure

- `code` contains the C++ code that takes the Age of Empires II `.dat` file as an input and produces a `.json` file that contains data from the `.dat` file in basically the same structure.
- `bin` contains a compiled version of above code for linux - no idea if it will work or even execute on another machine
- `data` contains the `json` output, ready to be further processed by third-party applications. It also contains python scripts to extract interesting data.

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
