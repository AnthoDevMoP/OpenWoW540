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
BossName: Saboteur Kiptilak
SD%Complete: 5
SDComment: first script
SDCategory: gate_of_the_setting_sun
EndScriptData */

#include "ScriptPCH.h"
#include "gate_of_the_setting_sun.h"


class boss_saboteur_kiptilak : public CreatureScript
{
public:
    boss_saboteur_kiptilak() : CreatureScript("boss_saboteur_kiptilak") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_saboteur_kiptilak (creature);
    }

    struct boss_saboteur_kiptilakAI : public ScriptedAI
    {
        boss_saboteur_kiptilakAI(Creature* creature) : ScriptedAI(creature)
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

void AddSC_boss_saboteur_kiptilak()
{
    new boss_saboteur_kiptilak();
}
