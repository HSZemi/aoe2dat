#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include "genie/dat/DatFile.h"
#include "tojson.h"
#include <boost/algorithm/string/join.hpp>

void datfile2json(std::ofstream& out, genie::DatFile* datFile) {
	out << "{" << std::endl;
	out << "\"FileVersion\":\"" << datFile->FileVersion << "\"," << std::endl;
	out << "\"PlayerColours\":[";
	long pcsize = datFile->PlayerColours.size();
	long pccount = 0;
	for (genie::PlayerColour pc : datFile->PlayerColours) {
		playercolour2json(out, pc);
		if (++pccount < pcsize) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]," << std::endl;
	out << "\"Effects\":[" << std::endl;
	long effectsize = datFile->Effects.size();
	long effectcount = 0;
	for (genie::Effect effect : datFile->Effects) {
		effect2json(out, effect);
		if (++effectcount < effectsize) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]," << std::endl;
	out << "\"Civs\":[" << std::endl;
	long civsize = datFile->Civs.size();
	long civcount = 0;
	for (genie::Civ civ : datFile->Civs) {
		civ2json(out, civ);
		if (++civcount < civsize) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]," << std::endl;
	out << "\"Techs\":[" << std::endl;
	long techsize = datFile->Techs.size();
	long techcount = 0;
	for (genie::Tech tech : datFile->Techs) {
		research2json(out, tech);
		if (++techcount < techsize) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]," << std::endl;
	out << "\"TechTree\":" << std::endl;
	techtree2json(out, datFile->TechTree);
	out << std::endl;
	out << "}" << std::endl;
}

void effect2json(std::ofstream& out, genie::Effect effect) {
	out << "{" << std::endl;
	out << "\"Name\":\"" << effect.Name << "\"," << std::endl;
	out << "\"EffectCommands\":[";
	long size = effect.EffectCommands.size();
	long count = 0;
	for (genie::EffectCommand effectCommand : effect.EffectCommands) {
		effectcommand2json(out, effectCommand);
		if (++count < size) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]" << std::endl;
	out << "}";
}

void effectcommand2json(std::ofstream& out,
		genie::EffectCommand effectCommand) {
	out << "{" << std::endl;
	out << "\"Type\":" << std::to_string(effectCommand.Type) << "," << std::endl;
	out << "\"A\":" << effectCommand.A << "," << std::endl;
	out << "\"B\":" << effectCommand.B << "," << std::endl;
	out << "\"C\":" << effectCommand.C << "," << std::endl;
	out << "\"D\":" << effectCommand.D << "" << std::endl;
	out << "}";
}

void techtree2json(std::ofstream& out, genie::TechTree techtree) {
	out << "{" << std::endl;
	out << "\"TotalUnitTechGroups\":" << techtree.TotalUnitTechGroups << ","
			<< std::endl;
	out << "\"TechTreeAges\":[";
	long size = techtree.TechTreeAges.size();
	long count = 0;
	for (genie::TechTreeAge techtreeage : techtree.TechTreeAges) {
		techtreeage2json(out, techtreeage);
		if (++count < size) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]," << std::endl;
	out << "\"BuildingConnections\":[";
	size = techtree.BuildingConnections.size();
	count = 0;
	for (genie::BuildingConnection buildingconnection : techtree.BuildingConnections) {
		buildingconnection2json(out, buildingconnection);
		if (++count < size) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]," << std::endl;
	out << "\"UnitConnections\":[";
	size = techtree.UnitConnections.size();
	count = 0;
	for (genie::UnitConnection unitconnection : techtree.UnitConnections) {
		unitconnection2json(out, unitconnection);
		if (++count < size) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]," << std::endl;
	out << "\"ResearchConnections\":[";
	size = techtree.ResearchConnections.size();
	count = 0;
	for (genie::ResearchConnection researchconnection : techtree.ResearchConnections) {
		researchconnection2json(out, researchconnection);
		if (++count < size) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]" << std::endl;
	out << "}";
}

void techtreeage2json(std::ofstream& out, genie::TechTreeAge techtreeage) {
	out << "{" << std::endl;
	out << "\"ID\":" << techtreeage.ID << "," << std::endl;
	out << "\"Status\":" << std::to_string(techtreeage.Status) << ","
			<< std::endl;
	out << "\"Buildings\":[" << join2string<int32_t>(techtreeage.Buildings)
			<< "]," << std::endl;
	out << "\"Units\":[" << join2string<int32_t>(techtreeage.Units) << "],"
			<< std::endl;
	out << "\"Techs\":[" << join2string<int32_t>(techtreeage.Techs) << "],"
			<< std::endl;
	out << "\"Common\":";
	common2json(out, techtreeage.Common);
	out << "," << std::endl;
	out << "\"NumBuildingLevels\":"
			<< std::to_string(techtreeage.NumBuildingLevels) << ","
			<< std::endl;
	out << "\"BuildingsPerZone\":["
			<< join2string<int8_t>(techtreeage.BuildingsPerZone) << "],"
			<< std::endl;
	out << "\"GroupLengthPerZone\":["
			<< join2string<int8_t>(techtreeage.GroupLengthPerZone) << "],"
			<< std::endl;
	out << "\"MaxAgeLength\":" << std::to_string(techtreeage.MaxAgeLength)
			<< "," << std::endl;
	out << "\"LineMode\":" << techtreeage.LineMode << std::endl;
	out << "}";
}

void common2json(std::ofstream& out, genie::techtree::Common common) {
	out << "{" << std::endl;
	out << "\"SlotsUsed\":" << common.SlotsUsed << "," << std::endl;
	out << "\"UnitResearch\":[" << join2string<int32_t>(common.UnitResearch)
			<< "]," << std::endl;
	out << "\"Mode\":[" << join2string<int32_t>(common.Mode) << "]"
			<< std::endl;
	out << "}";
}

void buildingconnection2json(std::ofstream& out,
		genie::BuildingConnection buildingconnection) {
	out << "{" << std::endl;
	out << "\"ID\":" << buildingconnection.ID << "," << std::endl;
	out << "\"Status\":" << std::to_string(buildingconnection.Status) << ","
			<< std::endl;
	out << "\"Buildings\":["
			<< join2string<int32_t>(buildingconnection.Buildings) << "],"
			<< std::endl;
	out << "\"Units\":[" << join2string<int32_t>(buildingconnection.Units)
			<< "]," << std::endl;
	out << "\"Techs\":[" << join2string<int32_t>(buildingconnection.Techs)
			<< "]," << std::endl;
	out << "\"Common\":";
	common2json(out, buildingconnection.Common);
	out << "," << std::endl;
	out << "\"LocationInAge\":"
			<< std::to_string(buildingconnection.LocationInAge) << ","
			<< std::endl;
	out << "\"UnitsTechsTotal\":["
			<< join2string<int8_t>(buildingconnection.UnitsTechsTotal) << "],"
			<< std::endl;
	out << "\"UnitsTechsFirst\":["
			<< join2string<int8_t>(buildingconnection.UnitsTechsFirst) << "],"
			<< std::endl;
	out << "\"LineMode\":" << buildingconnection.LineMode << "," << std::endl;
	out << "\"EnablingResearch\":" << buildingconnection.EnablingResearch
			<< std::endl;
	out << "}";
}

void unitconnection2json(std::ofstream& out,
		genie::UnitConnection unitconnection) {
	out << "{" << std::endl;
	out << "\"ID\":" << unitconnection.ID << "," << std::endl;
	out << "\"Status\":" << std::to_string(unitconnection.Status) << ","
			<< std::endl;
	out << "\"UpperBuilding\":" << unitconnection.UpperBuilding << ","
			<< std::endl;
	out << "\"Common\":";
	common2json(out, unitconnection.Common);
	out << "," << std::endl;
	out << "\"VerticalLine\":" << unitconnection.VerticalLine << ","
			<< std::endl;
	out << "\"Units\":[" << join2string<int32_t>(unitconnection.Units) << "],"
			<< std::endl;
	out << "\"LocationInAge\":" << unitconnection.LocationInAge << ","
			<< std::endl;
	out << "\"RequiredResearch\":" << unitconnection.RequiredResearch << ","
			<< std::endl;
	out << "\"LineMode\":" << unitconnection.LineMode << "," << std::endl;
	out << "\"EnablingResearch\":" << unitconnection.EnablingResearch
			<< std::endl;
	out << "}";
}

void researchconnection2json(std::ofstream& out,
		genie::ResearchConnection researchconnection) {
	out << "{" << std::endl;
	out << "\"ID\":" << researchconnection.ID << "," << std::endl;
	out << "\"Status\":" << std::to_string(researchconnection.Status) << ","
			<< std::endl;
	out << "\"UpperBuilding\":" << researchconnection.UpperBuilding << ","
			<< std::endl;
	out << "\"Buildings\":["
			<< join2string<int32_t>(researchconnection.Buildings) << "],"
			<< std::endl;
	out << "\"Units\":[" << join2string<int32_t>(researchconnection.Units)
			<< "]," << std::endl;
	out << "\"Techs\":[" << join2string<int32_t>(researchconnection.Techs)
			<< "]," << std::endl;
	out << "\"Common\":";
	common2json(out, researchconnection.Common);
	out << "," << std::endl;
	out << "\"VerticalLine\":" << researchconnection.VerticalLine << ","
			<< std::endl;
	out << "\"LocationInAge\":" << researchconnection.LocationInAge << ","
			<< std::endl;
	out << "\"LineMode\":" << researchconnection.LineMode << std::endl;
	out << "}";
}

void playercolour2json(std::ofstream& out, genie::PlayerColour pc) {
	out << "{" << std::endl;
	out << "\"ID\":\"" << pc.ID << "\"," << std::endl;
	out << "\"MinimapColour\":\"" << pc.MinimapColour << "\"," << std::endl;
	out << "\"PlayerColorBase\":\"" << pc.PlayerColorBase << "\"," << std::endl;
	out << "\"UnitOutlineColor\":\"" << pc.UnitOutlineColor << "\","
			<< std::endl;
	out << "\"UnitSelectionColor1\":\"" << pc.UnitSelectionColor1 << "\","
			<< std::endl;
	out << "\"UnitSelectionColor2\":\"" << pc.UnitSelectionColor2 << "\","
			<< std::endl;
	out << "\"MinimapColor2\":\"" << pc.MinimapColor2 << "\"," << std::endl;
	out << "\"MinimapColor3\":\"" << pc.MinimapColor3 << "\"," << std::endl;
	out << "\"StatisticsText\":\"" << pc.StatisticsText << "\"," << std::endl;
	out << "\"Name\":\"" << pc.Name << "\"," << std::endl;
	out << "\"ResourceID\":\"" << pc.ResourceID << "\"," << std::endl;
	out << "\"Type\":\"" << std::to_string(pc.Type) << "\"" << std::endl;
	out << "}";
}

void civ2json(std::ofstream& out, genie::Civ civ) {
	out << "{" << std::endl;
	out << "\"PlayerType\":" << std::to_string(civ.PlayerType) << ","
			<< std::endl;
	out << "\"Name\":\"" << civ.Name << "\"," << std::endl;
	out << "\"Name2\":\"" << civ.Name2 << "\"," << std::endl;
	out << "\"TechTreeID\":" << civ.TechTreeID << "," << std::endl;
	out << "\"TeamBonusID\":" << civ.TeamBonusID << "," << std::endl;
	out << "\"Resources\":[" << join2string<float>(civ.Resources) << "],"
			<< std::endl;
	out << "\"IconSet\":" << std::to_string(civ.IconSet) << "," << std::endl;
	out << "\"UnitPointers\":[" << join2string<int32_t>(civ.UnitPointers)
			<< "]," << std::endl;
	out << "\"Units\":[" << std::endl;
	long unitssize = civ.Units.size();
	long unitscount = 0;
	for (genie::Unit unit : civ.Units) {
		unit2json(out, unit);
		if (++unitscount < unitssize) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]," << std::endl;
	out << "\"UniqueUnitsTechs\":["
			<< join2string<int16_t>(civ.UniqueUnitsTechs) << "]" << std::endl;
	out << "}";
}

void unit2json(std::ofstream& out, genie::Unit unit) {
	out << "{" << std::endl;
	out << "\"Type\":" << std::to_string(unit.Type) << "," << std::endl;
	out << "\"ID\":" << unit.ID << "," << std::endl;
	out << "\"LanguageDLLName\":" << unit.LanguageDLLName << "," << std::endl;
	out << "\"LanguageDLLCreation\":" << unit.LanguageDLLCreation << ","
			<< std::endl;
	out << "\"Class\":" << unit.Class << "," << std::endl;
	out << "\"StandingGraphic\":[" << unit.StandingGraphic.first << ","
			<< unit.StandingGraphic.second << "]," << std::endl;
	out << "\"DyingGraphic\":" << unit.DyingGraphic << "," << std::endl;
	out << "\"UndeadGraphic\":" << unit.UndeadGraphic << "," << std::endl;
	out << "\"UndeadMode\":" << std::to_string(unit.UndeadMode) << ","
			<< std::endl;
	out << "\"HitPoints\":" << unit.HitPoints << "," << std::endl;
	out << "\"LineOfSight\":" << unit.LineOfSight << "," << std::endl;
	out << "\"GarrisonCapacity\":" << std::to_string(unit.GarrisonCapacity)
			<< "," << std::endl;
	out << "\"CollisionSize\":" << "{\"x\":" << unit.CollisionSize.x
			<< ",\"y\":" << unit.CollisionSize.y << ",\"z\":"
			<< unit.CollisionSize.z << "}," << std::endl;
	out << "\"TrainSound\":" << unit.TrainSound << "," << std::endl;
	out << "\"DamageSound\":" << unit.DamageSound << "," << std::endl;
	out << "\"DeadUnitID\":" << unit.DeadUnitID << "," << std::endl;
	out << "\"BloodUnitID\":" << unit.BloodUnitID << "," << std::endl;
	out << "\"SortNumber\":" << std::to_string(unit.SortNumber) << ","
			<< std::endl;
	out << "\"CanBeBuiltOn\":" << std::to_string(unit.CanBeBuiltOn) << ","
			<< std::endl;
	out << "\"IconID\":" << unit.IconID << "," << std::endl;
	out << "\"HideInEditor\":" << std::to_string(unit.HideInEditor) << ","
			<< std::endl;
	out << "\"OldPortraitPict\":" << unit.OldPortraitPict << "," << std::endl;
	out << "\"Enabled\":" << std::to_string(unit.Enabled) << "," << std::endl;
	out << "\"Disabled\":" << std::to_string(unit.Disabled) << "," << std::endl;
	out << "\"PlacementSideTerrain\":[" << unit.PlacementSideTerrain.first
			<< "," << unit.PlacementSideTerrain.second << "]," << std::endl;
	out << "\"PlacementTerrain\":[" << unit.PlacementTerrain.first << ","
			<< unit.PlacementTerrain.second << "]," << std::endl;
	out << "\"ClearanceSize\":[" << unit.ClearanceSize.first << ","
			<< unit.ClearanceSize.second << "]," << std::endl;
	out << "\"HillMode\":" << std::to_string(unit.HillMode) << "," << std::endl;
	out << "\"FogVisibility\":" << std::to_string(unit.FogVisibility) << ","
			<< std::endl;
	out << "\"TerrainRestriction\":" << unit.TerrainRestriction << ","
			<< std::endl;
	out << "\"FlyMode\":" << std::to_string(unit.FlyMode) << "," << std::endl;
	out << "\"ResourceCapacity\":" << unit.ResourceCapacity << "," << std::endl;
	out << "\"ResourceDecay\":" << unit.ResourceDecay << "," << std::endl;
	out << "\"BlastDefenseLevel\":" << std::to_string(unit.BlastDefenseLevel)
			<< "," << std::endl;
	out << "\"CombatLevel\":" << std::to_string(unit.CombatLevel) << ","
			<< std::endl;
	out << "\"InteractionMode\":" << std::to_string(unit.InteractionMode) << ","
			<< std::endl;
	out << "\"MinimapMode\":" << std::to_string(unit.MinimapMode) << ","
			<< std::endl;
	out << "\"InterfaceKind\":" << std::to_string(unit.InterfaceKind) << ","
			<< std::endl;
	out << "\"MultipleAttributeMode\":" << unit.MultipleAttributeMode << ","
			<< std::endl;
	out << "\"MinimapColor\":" << std::to_string(unit.MinimapColor) << ","
			<< std::endl;
	out << "\"LanguageDLLHelp\":" << unit.LanguageDLLHelp << "," << std::endl;
	out << "\"LanguageDLLHotKeyText\":" << unit.LanguageDLLHotKeyText << ","
			<< std::endl;
	out << "\"HotKey\":" << unit.HotKey << "," << std::endl;
	out << "\"Recyclable\":" << std::to_string(unit.Recyclable) << ","
			<< std::endl;
	out << "\"EnableAutoGather\":" << std::to_string(unit.EnableAutoGather)
			<< "," << std::endl;
	out << "\"CreateDoppelgangerOnDeath\":"
			<< std::to_string(unit.CreateDoppelgangerOnDeath) << ","
			<< std::endl;
	out << "\"ResourceGatherGroup\":"
			<< std::to_string(unit.ResourceGatherGroup) << "," << std::endl;
	out << "\"OcclusionMode\":" << std::to_string(unit.OcclusionMode) << ","
			<< std::endl;
	out << "\"ObstructionType\":" << std::to_string(unit.ObstructionType) << ","
			<< std::endl;
	out << "\"ObstructionClass\":" << std::to_string(unit.ObstructionClass)
			<< "," << std::endl;
	out << "\"Trait\":" << std::to_string(unit.Trait) << "," << std::endl;
	out << "\"Civilization\":" << std::to_string(unit.Civilization) << ","
			<< std::endl;
	out << "\"Nothing\":" << unit.Nothing << "," << std::endl;
	out << "\"SelectionEffect\":" << std::to_string(unit.SelectionEffect) << ","
			<< std::endl;
	out << "\"EditorSelectionColour\":"
			<< std::to_string(unit.EditorSelectionColour) << "," << std::endl;
	out << "\"OutlineSize\":" << "{\"x\":" << unit.OutlineSize.x << ",\"y\":"
			<< unit.OutlineSize.y << ",\"z\":" << unit.OutlineSize.z << "},"
			<< std::endl;
	out << "\"ResourceStorages\":[" << std::endl;
	long rssize = unit.ResourceStorages.size();
	long rscount = 0;
	for (ResourceStorage rs : unit.ResourceStorages) {
		out << "{\"Type\":" << rs.Type << ",\"Amount\":" << rs.Amount
				<< ",\"Flag\":" << std::to_string(rs.Flag) << "}";
		if (++rscount < rssize) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]," << std::endl;
	out << "\"DamageGraphics\":[" << std::endl;
	long dgsize = unit.DamageGraphics.size();
	long dgcount = 0;
	for (genie::unit::DamageGraphic dg : unit.DamageGraphics) {
		out << "{" << std::endl;
		out << "\"GraphicID\":" << dg.GraphicID << "," << std::endl;
		out << "\"DamagePercent\":" << std::to_string(dg.DamagePercent) << ","
				<< std::endl;
		out << "\"OldApplyMode\":" << std::to_string(dg.OldApplyMode) << ","
				<< std::endl;
		out << "\"ApplyMode\":" << std::to_string(dg.ApplyMode) << std::endl;
		out << "}";
		if (++dgcount < dgsize) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]," << std::endl;
	out << "\"SelectionSound\":" << unit.SelectionSound << "," << std::endl;
	out << "\"DyingSound\":" << unit.DyingSound << "," << std::endl;
	out << "\"OldAttackReaction\":" << std::to_string(unit.OldAttackReaction)
			<< "," << std::endl;
	out << "\"ConvertTerrain\":" << std::to_string(unit.ConvertTerrain) << ","
			<< std::endl;
	out << "\"Name\":\"" << unit.Name << "\"," << std::endl;
	out << "\"Name2\":\"" << unit.Name2 << "\"," << std::endl;
	out << "\"Unitline\":" << unit.Unitline << "," << std::endl;
	out << "\"MinTechLevel\":" << std::to_string(unit.MinTechLevel) << ","
			<< std::endl;
	out << "\"CopyID\":" << unit.CopyID << "," << std::endl;
	out << "\"BaseID\":" << unit.BaseID << "," << std::endl;
	out << "\"TelemetryID\":" << unit.TelemetryID << "," << std::endl;
	out << "\"Speed\":" << unit.Speed << "," << std::endl;
	out << "\"DeadFish\":";
	deadfish2json(out, unit.DeadFish);
	out << "," << std::endl;
	out << "\"Bird\":";
	bird2json(out, unit.Bird);
	out << "," << std::endl;
	out << "\"Type50\":";
	type502json(out, unit.Type50);
	out << "," << std::endl;
	out << "\"Projectile\":";
	projectile2json(out, unit.Projectile);
	out << "," << std::endl;
	out << "\"Creatable\":";
	creatable2json(out, unit.Creatable);
	out << "," << std::endl;
	out << "\"Building\":";
	building2json(out, unit.Building);
	out << std::endl;
	out << "}";
}

void deadfish2json(std::ofstream& out, genie::unit::DeadFish deadFish) {
	out << "{" << std::endl;
	out << "\"WalkingGraphic\":" << deadFish.WalkingGraphic << "," << std::endl;
	out << "\"RunningGraphic\":" << deadFish.RunningGraphic << "," << std::endl;
	out << "\"RotationSpeed\":" << deadFish.RotationSpeed << "," << std::endl;
	out << "\"OldSizeClass\":" << std::to_string(deadFish.OldSizeClass) << ","
			<< std::endl;
	out << "\"TrackingUnit\":" << deadFish.TrackingUnit << "," << std::endl;
	out << "\"TrackingUnitMode\":" << std::to_string(deadFish.TrackingUnitMode)
			<< "," << std::endl;
	out << "\"TrackingUnitDensity\":" << deadFish.TrackingUnitDensity << ","
			<< std::endl;
	out << "\"OldMoveAlgorithm\":" << std::to_string(deadFish.OldMoveAlgorithm)
			<< "," << std::endl;
	out << "\"TurnRadius\":" << deadFish.TurnRadius << "," << std::endl;
	out << "\"TurnRadiusSpeed\":" << deadFish.TurnRadiusSpeed << ","
			<< std::endl;
	out << "\"MaxYawPerSecondMoving\":" << deadFish.MaxYawPerSecondMoving << ","
			<< std::endl;
	out << "\"StationaryYawRevolutionTime\":"
			<< deadFish.StationaryYawRevolutionTime << "," << std::endl;
	out << "\"MaxYawPerSecondStationary\":"
			<< deadFish.MaxYawPerSecondStationary << std::endl;
	out << "}";
}

void task2json(std::ofstream& out, genie::Task task) {
	out << "{" << std::endl;
	out << "\"TaskType\":" << task.TaskType << "," << std::endl;
	out << "\"ID\":" << task.ID << "," << std::endl;
	out << "\"IsDefault\":" << std::to_string(task.IsDefault) << ","
			<< std::endl;
	out << "\"ActionType\":" << task.ActionType << "," << std::endl;
	out << "\"ClassID\":" << task.ClassID << "," << std::endl;
	out << "\"UnitID\":" << task.UnitID << "," << std::endl;
	out << "\"TerrainID\":" << task.TerrainID << "," << std::endl;
	out << "\"ResourceIn\":" << task.ResourceIn << "," << std::endl;
	out << "\"ResourceMultiplier\":" << task.ResourceMultiplier << ","
			<< std::endl;
	out << "\"ResourceOut\":" << task.ResourceOut << "," << std::endl;
	out << "\"UnusedResource\":" << task.UnusedResource << "," << std::endl;
	out << "\"WorkValue1\":" << task.WorkValue1 << "," << std::endl;
	out << "\"WorkValue2\":" << task.WorkValue2 << "," << std::endl;
	out << "\"WorkRange\":" << task.WorkRange << "," << std::endl;
	out << "\"AutoSearchTargets\":" << std::to_string(task.AutoSearchTargets)
			<< "," << std::endl;
	out << "\"SearchWaitTime\":" << task.SearchWaitTime << "," << std::endl;
	out << "\"EnableTargeting\":" << std::to_string(task.EnableTargeting) << ","
			<< std::endl;
	out << "\"CombatLevelFlag\":" << std::to_string(task.CombatLevelFlag) << ","
			<< std::endl;
	out << "\"GatherType\":" << task.GatherType << "," << std::endl;
	out << "\"WorkFlag2\":" << task.WorkFlag2 << "," << std::endl;
	out << "\"TargetDiplomacy\":" << std::to_string(task.TargetDiplomacy) << ","
			<< std::endl;
	out << "\"CarryCheck\":" << std::to_string(task.CarryCheck) << ","
			<< std::endl;
	out << "\"PickForConstruction\":"
			<< std::to_string(task.PickForConstruction) << "," << std::endl;
	out << "\"MovingGraphicID\":" << task.MovingGraphicID << "," << std::endl;
	out << "\"ProceedingGraphicID\":" << task.ProceedingGraphicID << ","
			<< std::endl;
	out << "\"WorkingGraphicID\":" << task.WorkingGraphicID << "," << std::endl;
	out << "\"CarryingGraphicID\":" << task.CarryingGraphicID << ","
			<< std::endl;
	out << "\"ResourceGatheringSoundID\":" << task.ResourceGatheringSoundID
			<< "," << std::endl;
	out << "\"ResourceDepositSoundID\":" << task.ResourceDepositSoundID
			<< std::endl;
	out << "}";
}

void bird2json(std::ofstream& out, genie::unit::Bird bird) {
	out << "{" << std::endl;
	out << "\"DefaultTaskID\":" << bird.DefaultTaskID << "," << std::endl;
	out << "\"SearchRadius\":" << bird.SearchRadius << "," << std::endl;
	out << "\"WorkRate\":" << bird.WorkRate << "," << std::endl;
	out << "\"DropSites\":[" << std::endl;
	long dsize = bird.DropSites.size();
	long dcount = 0;
	for(short dropSite : bird.DropSites){
	    out << dropSite;
		if (++dcount < dsize) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]," << std::endl;
	out << "\"TaskSwapGroup\":" << std::to_string(bird.TaskSwapGroup) << ","
			<< std::endl;
	out << "\"AttackSound\":" << bird.AttackSound << "," << std::endl;
	out << "\"MoveSound\":" << bird.MoveSound << "," << std::endl;
	out << "\"RunPattern\":" << std::to_string(bird.RunPattern) << ","
			<< std::endl;
	out << "\"TaskList\":[";
	long tsize = bird.TaskList.size();
	long tcount = 0;
	for (genie::Task task : bird.TaskList) {
		task2json(out, task);
		if (++tcount < tsize) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]" << std::endl;
	out << "}";

}

void creatable2json(std::ofstream& out, genie::unit::Creatable creatable) {
	out << "{" << std::endl;
	out << "\"ResourceCosts\":[" << std::endl;
	long rcsize = creatable.ResourceCosts.size();
	long rccount = 0;
	for (ResourceCost rc : creatable.ResourceCosts) {
		out << "{\"Type\":" << rc.Type << ",\"Amount\":" << rc.Amount
				<< ",\"Flag\":" << rc.Flag << "}";
		if (++rccount < rcsize) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]," << std::endl;
	out << "\"TrainTime\":" << creatable.TrainTime << "," << std::endl;
	out << "\"TrainLocationID\":" << creatable.TrainLocationID << ","
			<< std::endl;
	out << "\"ButtonID\":" << std::to_string(creatable.ButtonID) << ","
			<< std::endl;
	out << "\"RearAttackModifier\":" << creatable.RearAttackModifier << ","
			<< std::endl;
	out << "\"FlankAttackModifier\":" << creatable.FlankAttackModifier << ","
			<< std::endl;
	out << "\"CreatableType\":" << std::to_string(creatable.CreatableType)
			<< "," << std::endl;
	out << "\"HeroMode\":" << std::to_string(creatable.HeroMode) << ","
			<< std::endl;
	out << "\"GarrisonGraphic\":" << creatable.GarrisonGraphic << ","
			<< std::endl;
	out << "\"TotalProjectiles\":" << creatable.TotalProjectiles << ","
			<< std::endl;
	out << "\"MaxTotalProjectiles\":"
			<< std::to_string(creatable.MaxTotalProjectiles) << ","
			<< std::endl;
	out << "\"ProjectileSpawningArea\":["
			<< join2string<float>(creatable.ProjectileSpawningArea) << "],"
			<< std::endl;
	out << "\"SecondaryProjectileUnit\":" << creatable.SecondaryProjectileUnit
			<< "," << std::endl;
	out << "\"SpecialGraphic\":" << creatable.SpecialGraphic << ","
			<< std::endl;
	out << "\"SpecialAbility\":" << std::to_string(creatable.SpecialAbility)
			<< "," << std::endl;
	out << "\"DisplayedPierceArmour\":" << creatable.DisplayedPierceArmour
			<< std::endl;
	out << "}";
}

void building2json(std::ofstream& out, genie::unit::Building building) {
	out << "{" << std::endl;
	out << "\"ConstructionGraphicID\":" << building.ConstructionGraphicID << ","
			<< std::endl;
	out << "\"SnowGraphicID\":" << building.SnowGraphicID << "," << std::endl;
	out << "\"AdjacentMode\":" << std::to_string(building.AdjacentMode) << ","
			<< std::endl;
	out << "\"GraphicsAngle\":" << building.GraphicsAngle << "," << std::endl;
	out << "\"DisappearsWhenBuilt\":"
			<< std::to_string(building.DisappearsWhenBuilt) << "," << std::endl;
	out << "\"StackUnitID\":" << building.StackUnitID << "," << std::endl;
	out << "\"FoundationTerrainID\":" << building.FoundationTerrainID << ","
			<< std::endl;
	out << "\"OldOverlayID\":" << building.OldOverlayID << "," << std::endl;
	out << "\"TechID\":" << building.TechID << "," << std::endl;
	out << "\"CanBurn\":" << std::to_string(building.CanBurn) << ","
			<< std::endl;
	out << "\"Annexes\": [" << std::endl;
	long axsize = building.Annexes.size();
	long axcount = 0;
	for (genie::unit::BuildingAnnex ax : building.Annexes) {
		out << "{\"UnitID\":" << ax.UnitID << ",\"Misplacement\":["
				<< ax.Misplacement.first << "," << ax.Misplacement.second
				<< "]}";
		if (++axcount < axsize) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]," << std::endl;
	out << "\"HeadUnit\":" << building.HeadUnit << "," << std::endl;
	out << "\"TransformUnit\":" << building.TransformUnit << "," << std::endl;
	out << "\"TransformSound\":" << building.TransformSound << "," << std::endl;
	out << "\"ConstructionSound\":" << building.ConstructionSound << ","
			<< std::endl;
	out << "\"GarrisonType\":" << std::to_string(building.GarrisonType) << ","
			<< std::endl;
	out << "\"GarrisonHealRate\":" << building.GarrisonHealRate << ","
			<< std::endl;
	out << "\"GarrisonRepairRate\":" << building.GarrisonRepairRate << ","
			<< std::endl;
	out << "\"PileUnit\":" << building.PileUnit << std::endl;
	out << "}";
}

void projectile2json(std::ofstream& out, genie::unit::Projectile projectile) {
	out << "{" << std::endl;
	out << "\"ProjectileType\":" << std::to_string(projectile.ProjectileType)
			<< "," << std::endl;
	out << "\"SmartMode\":" << std::to_string(projectile.SmartMode) << ","
			<< std::endl;
	out << "\"HitMode\":" << std::to_string(projectile.HitMode) << ","
			<< std::endl;
	out << "\"VanishMode\":" << std::to_string(projectile.VanishMode) << ","
			<< std::endl;
	out << "\"AreaEffectSpecials\":"
			<< std::to_string(projectile.AreaEffectSpecials) << ","
			<< std::endl;
	out << "\"ProjectileArc\":" << std::to_string(projectile.ProjectileArc)
			<< std::endl;
	out << "}";
}

void type502json(std::ofstream& out, genie::unit::Type50 type50) {
	out << "{" << std::endl;
	out << "\"BaseArmor\":" << type50.BaseArmor << "," << std::endl;
	out << "\"Attacks\":[" << std::endl;
	long atsize = type50.Attacks.size();
	long atcount = 0;
	for (genie::unit::AttackOrArmor aoa : type50.Attacks) {
		out << "{\"Class\":" << aoa.Class << ",\"Amount\":" << aoa.Amount
				<< "}";
		if (++atcount < atsize) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]," << std::endl;
	out << "\"Armours\":[" << std::endl;
	long armsize = type50.Armours.size();
	long armcount = 0;
	for (genie::unit::AttackOrArmor aoa : type50.Armours) {
		out << "{\"Class\":" << aoa.Class << ",\"Amount\":" << aoa.Amount
				<< "}";
		if (++armcount < armsize) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]," << std::endl;
	out << "\"DefenseTerrainBonus\":" << type50.DefenseTerrainBonus << ","
			<< std::endl;
	out << "\"MaxRange\":" << type50.MaxRange << "," << std::endl;
	out << "\"BlastWidth\":" << type50.BlastWidth << "," << std::endl;
	out << "\"ReloadTime\":" << type50.ReloadTime << "," << std::endl;
	out << "\"ProjectileUnitID\":" << type50.ProjectileUnitID << ","
			<< std::endl;
	out << "\"AccuracyPercent\":" << type50.AccuracyPercent << "," << std::endl;
	out << "\"BreakOffCombat\":" << std::to_string(type50.BreakOffCombat) << ","
			<< std::endl;
	out << "\"FrameDelay\":" << type50.FrameDelay << "," << std::endl;
	out << "\"GraphicDisplacement\":["
			<< join2string<float>(type50.GraphicDisplacement) << "],"
			<< std::endl;
	out << "\"BlastAttackLevel\":" << std::to_string(type50.BlastAttackLevel)
			<< "," << std::endl;
	out << "\"MinRange\":" << type50.MinRange << "," << std::endl;
	out << "\"AccuracyDispersion\":" << type50.AccuracyDispersion << ","
			<< std::endl;
	out << "\"AttackGraphic\":" << type50.AttackGraphic << "," << std::endl;
	out << "\"DisplayedMeleeArmour\":" << type50.DisplayedMeleeArmour << ","
			<< std::endl;
	out << "\"DisplayedAttack\":" << type50.DisplayedAttack << "," << std::endl;
	out << "\"DisplayedRange\":" << type50.DisplayedRange << "," << std::endl;
	out << "\"DisplayedReloadTime\":" << type50.DisplayedReloadTime
			<< std::endl;
	out << "}";

}

template<typename T>
std::string join2string(std::vector<T> numbers) {
	long nsize = numbers.size();
	long ncount = 0;
	std::string s = "";
	for (T i : numbers) {
		s += std::to_string(i);
		if (++ncount < nsize) {
			s += ",";
		}
	}
	return s;
}

void research2json(std::ofstream& out, genie::Tech tech) {
	out << "{" << std::endl;
	out << "\"RequiredTechs\":[";
	out << join2string<int16_t>(tech.RequiredTechs);
	out << "]," << std::endl;
	out << "\"ResourceCosts\":[" << std::endl;
	long rrcsize = tech.ResourceCosts.size();
	long rrccount = 0;
	for (ResearchResourceCost rrc : tech.ResourceCosts) {
		out << "{\"Type\":" << rrc.Type << ",\"Amount\":" << rrc.Amount
				<< ",\"Flag\":" << std::to_string(rrc.Flag) << "}";
		if (++rrccount < rrcsize) {
			out << ",";
		}
		out << std::endl;
	}
	out << "]," << std::endl;
	out << "\"RequiredTechCount\":" << tech.RequiredTechCount << ","
			<< std::endl;
	out << "\"Civ\":" << tech.Civ << "," << std::endl;
	out << "\"FullTechMode\":" << tech.FullTechMode << "," << std::endl;
	out << "\"ResearchLocation\":" << tech.ResearchLocation << "," << std::endl;
	out << "\"LanguageDLLName\":" << tech.LanguageDLLName << "," << std::endl;
	out << "\"LanguageDLLDescription\":" << tech.LanguageDLLDescription << ","
			<< std::endl;
	out << "\"ResearchTime\":" << tech.ResearchTime << "," << std::endl;
	out << "\"EffectID\":" << tech.EffectID << "," << std::endl;
	out << "\"Type\":" << tech.Type << "," << std::endl;
	out << "\"IconID\":" << tech.IconID << "," << std::endl;
	out << "\"ButtonID\":" << std::to_string(tech.ButtonID) << "," << std::endl;
	out << "\"LanguageDLLHelp\":" << tech.LanguageDLLHelp << "," << std::endl;
	out << "\"LanguageDLLTechTree\":" << tech.LanguageDLLTechTree << ","
			<< std::endl;
	out << "\"HotKey\":" << tech.HotKey << "," << std::endl;
	out << "\"Name\":\"" << tech.Name << "\"," << std::endl;
	out << "\"Name2\":\"" << tech.Name2 << "\"" << std::endl;
	out << "}";
}
