/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2013 Arcaniafr<http://arcaniafr.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
 
/* ScriptData
SDName: instance_gate_of_the_setting_sun
BossName: Raigonn
SD%Complete: 5
SDComment: first script
SDCategory: gate_of_the_setting_sun
EndScriptData */

#include "ScriptPCH.h"
#include "gate_of_the_setting_sun.h"

//Base spells
enum Spells
{
    SPELL_BATTERING_HEADBUTT    = 111668, // "Raigonn charges the door..."
    SPELL_BROKEN_CARAPACE       = 107146, // "The Mantid Carapace has been broken..."
    SPELL_FIXATE                = 111725, // "Raigonn is fixated on you!"
    SPELL_FRENZY                = 111730, // "Increases damage dealt by 25%. Stacks."
    SPELL_IMPERVIOUS_CARAPACE   = 107118, // "The armored carapace reduces damage taken by 99%."
    SPELL_STOMP                 = 111728  // "Raigonn stomps, inflicting 34125 to 35875 "
};

class boss_raigonn : public CreatureScript
{
public:
    boss_raigonn() : CreatureScript("boss_raigonn") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_raigonn (creature);
    }

    struct boss_raigonnAI : public ScriptedAI
    {
        boss_raigonnAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset() {}

        void EnterCombat(Unit* /*who*/) {}

        void UpdateAI(uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_raigonn()
{
    new boss_raigonn();
}
