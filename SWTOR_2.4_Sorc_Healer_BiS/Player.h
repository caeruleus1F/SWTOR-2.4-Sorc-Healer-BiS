#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class Player {

	//Defensive stats
	float Health, BaseHealth, BaseEndurance, EnduranceRating, HealthFromEndurance, HealthFromSkillsBuffs, EK_EHP, IE_EHP, COMP_HEALTH_MULT;
	float DamageReduction, BaseDamageReduction, SkillDamageReduction, ArmorRating, DamageReductionFromArmorRating, DamageReductionEK, DamageReductionIE;
	float DefenseChance, BaseDefensePercent, DefenseFromRating, DefenseRating, DefenseFromSkillsBuffs;
	float ShieldChance, ShieldGeneratorChance, ShieldFromRating, ShieldRating, ShieldFromSkillsBuffs;
	float ShieldAbsorption, ShieldGeneratorAbsorption, AbsorbFromRating, AbsorbRating;

	float MARK_OF_POWER_STAT, MARK_OF_POWER_REDUCTION, HUNTERS_BOON, COORDINATION, UNNATURAL_MIGHT;
	
	//Offensive stats
	float WillpowerRating, TotalWillpower, PowerRating, BonusDamageFromSkillsBuffs, ForcePower, BonusHeal, BonusHealFromWillpower, BonusHealFromPower, BonusHealFromForcePower;
	float AccuracyPercent, WeaponAccuracy, AccuracyFromRating, AccuracyRating, AccuracyFromSkillsBuffs, AccuracyFromCompanion;
	float MeleeCriticalChance, ForceCriticalChance, BaseCriticalChance, BonusCriticalChance, CritFromRating, CritFromWillpower, CritRating, CritFromSkillsBuffs, CritFromCompanion;
	float SurgePercent, BaseSurge, SurgeFromRating, SurgeRating, SurgeFromSkillsBuffs, SurgeFromCompanion;
	float AlacrityPercent, BaseAlacrity, AlacrityFromRating, AlacrityRating, AlacrityFromSkillsBuffs;

	float HealRotation() {

		float Revivification, Resurgence, FirstInnervate, DarkInfusion, SecondInnervate, StaticBarrier, UnnaturalPreservation, TotalHeal, TotalTime, HPS;

		Revivification = (1 + ForceCriticalChance * SurgePercent) * (.209 * 11180 + 4.136 * BonusHeal);
		Resurgence = (1 + ForceCriticalChance * SurgePercent) * ((.045 * 11180 + .91 * BonusHeal) + (.06 * 11180 + 1.18 * BonusHeal));
		FirstInnervate = (1 + (ForceCriticalChance + .25) * SurgePercent) * (.056 * 11180 + 1.12 * BonusHeal) * 4;
		SecondInnervate = (1 + ForceCriticalChance * SurgePercent) * (.056 * 11180 + 1.12 * BonusHeal) * 4;
		DarkInfusion = (1 + ForceCriticalChance * SurgePercent) * (.17 * 11180 + 3.41 * BonusHeal);
		StaticBarrier = 1.1 * (.164 * 11180 + 3.27 * BonusHeal);
		//UnnaturalPreservation = (1 + ForceCriticalChance * SurgePercent) * (1.82 * 11180 + 3.64 * BonusHeal);

		TotalHeal = Revivification * 3 + Resurgence * 12 + FirstInnervate * 4 + SecondInnervate * 4 + DarkInfusion * 6 + StaticBarrier * 60;// + UnnaturalPreservation * 4;
		//Resurgence + StaticBarrier + UnnaturalPreservation + (AlacrityModifiedCastTime) * (DarkInfusions + Innervates + Revivifications
		TotalTime = 114 + (1 - AlacrityPercent) * (2.5 * 6 + (8 * 3 * .82) + 6);
		HPS = TotalHeal / TotalTime;

		return HPS;
	}

public:

	short IN_GROUP, COMP_HEALTH_BUFF, COMP_CRIT_BUFF, COMP_SURGE_BUFF, COMP_ACCURACY_BUFF;

	Player ();

	float modOffStats (string, float, string, float, string, float, string, float, string, float, string, float);
	void showOffStats ();

	void OffHiltArmorings (float []);
	void OffMods (float []);
	void OffEnhancements (float []);
	void OffEarpieces (float []);
	void OffImplants (float []);
	void OffColorCrystals (float []);
	void OffAugments (float []);
	
	void showHPS () {
		cout << "HPS: " << HealRotation() << "\n";
	}
};

#endif