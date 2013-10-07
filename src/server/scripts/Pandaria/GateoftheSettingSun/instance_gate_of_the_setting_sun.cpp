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
SD%Complete: 50
SDComment: first script
SDCategory: gate_of_the_setting_sun
EndScriptData */


#include "ScriptPCH.h"
#include "gate_of_the_setting_sun.h"

#define ENCOUNTERS 4

class instance_gate_of_the_setting_sun : public InstanceMapScript
{
public:
    instance_gate_of_the_setting_sun() : InstanceMapScript("instance_gate_of_the_setting_sun", 471) { } //Good map normal

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_gate_of_the_setting_sun_InstanceMapScript(map);
    }

    struct instance_gate_of_the_setting_sun_InstanceMapScript: public InstanceScript
    {
        instance_gate_of_the_setting_sun_InstanceMapScript(InstanceMap* map) : InstanceScript(map) {}

        uint32 Encounter[ENCOUNTERS];

        uint64 SaboteurKiptilak;
        uint64 StrikerGadok;
        uint64 CommanderRimok;
        uint64 Raigonn;
        uint64 TeamInInstance;

        void Initialize()
        {
            SaboteurKiptilak        = 0;
            StrikerGadok            = 0;
            CommanderRimok          = 0;
            Raigonn                 = 0;

            for (uint8 i = 0 ; i<ENCOUNTERS; ++i)
                Encounter[i] = NOT_STARTED;
        }

        bool IsEncounterInProgress() const
        {
            for (uint8 i = 0; i < ENCOUNTERS; ++i)
            {
                if (Encounter[i] == IN_PROGRESS)
                    return true;
            }
            return false;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                 case BOSS_SABOTEUR_KIPTILAK:
                     SaboteurKiptilak = creature->GetGUID();
                     break;
                 case BOSS_STRIKER_GADOK:
                     StrikerGadok = creature->GetGUID();
                     break;
                 case BOSS_COMMANDER_RIMOK:
                     CommanderRimok = creature->GetGUID();
                     break;
                 case BOSS_RAIGONN:
                     Raigonn = creature->GetGUID();
                     break;
            }
        }

        uint64 getData64(uint32 identifier)
        {
            switch (identifier)
            {
                case DATA_SABOTEUR_KIPTILAK:
                    return SaboteurKiptilak;
                case DATA_STRIKER_GADOK:
                    return StrikerGadok;
                case DATA_COMMANDER_RIMOK:
                    return CommanderRimok;
                case DATA_RAIGONN:
                    return Raigonn;
            }
            return 0;
        }

        void SetData(uint32 type, uint32 data)
        {
            switch (type)
            {
                case DATA_SABOTEUR_KIPTILAK_EVENT:
                    Encounter[0] = data;
                    break;
                case DATA_STRIKER_GADOK_EVENT:
                    Encounter[1] = data;
                    break;
                case DATA_COMMANDER_RIMOK_EVENT:
                    Encounter[2] = data;
                    break;
                case DATA_RAIGONN_EVENT:
                    Encounter[3] = data;
                    break;
            }

           if (data == DONE)
               SaveToDB();
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::string str_data;
            std::ostringstream saveStream;
            saveStream << "G B" << Encounter[0] << " " << Encounter[1]  << " " << Encounter[2]  << " " << Encounter[3];
            str_data = saveStream.str();

            OUT_SAVE_INST_DATA_COMPLETE;
            return str_data;
        }

        void Load(const char* in)
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);

            char dataHead1, dataHead2;
            uint16 data0, data1, data2, data3;

            std::istringstream loadStream(in);
            loadStream >> dataHead1 >> dataHead2 >> data0 >> data1 >> data2 >> data3;

            if (dataHead1 == 'G' && dataHead2 == 'B')
            {
                Encounter[0] = data0;
                Encounter[1] = data1;
                Encounter[2] = data2;
                Encounter[3] = data3;

                for (uint8 i=0; i < ENCOUNTERS; ++i)
                    if (Encounter[i] == IN_PROGRESS)
                        Encounter[i] = NOT_STARTED;
            }
            else OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };
};

void AddSC_instance_gate_of_the_setting_sun()
{
    new instance_gate_of_the_setting_sun();
}
