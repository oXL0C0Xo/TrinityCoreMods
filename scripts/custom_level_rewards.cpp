#include "ScriptMgr.h"
#include "Chat.h"
#include "DatabaseEnv.h"
#include "Player.h"


#define SATCHEL_25 51999
#define SATCHEL_35 52000
#define SATCHEL_45 52001
#define SATCHEL_55 52002
#define SATCHEL_60 52003
#define SATCHEL_65 52004
#define SATCHEL_70 52005
#define TRAVELERS_BACKPACK 4500

class custom_level_rewards : public PlayerScript
{
    public:
        custom_level_rewards() : PlayerScript("custom_level_rewards") { }

    void OnLevelChanged(Player* player, uint8 oldLevel)
    {
        uint8 newLevel = player->getLevel();

        if (newLevel < 15)
        {
            player->AddItem(SATCHEL_25, 1);
            switch (newLevel){
                case 5:
                    player->AddItem(TRAVELERS_BACKPACK, 1);
                    break;
                case 10:
                    player->AddItem(TRAVELERS_BACKPACK, 1);
                    break;
                default:
                    break;
            } 
        } 
        else if (newLevel < 25)
        {
            player->AddItem(SATCHEL_35, 1);
            switch (newLevel){
                case 15:
                    player->AddItem(TRAVELERS_BACKPACK, 1);
                    break;
                case 20:
                    player->AddItem(TRAVELERS_BACKPACK, 1);
                    break;
                default:
                    break;
            }
        }
        else if (newLevel < 35)
            player->AddItem(SATCHEL_45, 1);
        else if (newLevel < 45)
            player->AddItem(SATCHEL_55, 1);
        else if (newLevel < 50)
            player->AddItem(SATCHEL_60, 1);
        else if (newLevel < 55)
            player->AddItem(SATCHEL_65, 1);
        else if (newLevel < 61)
            player->AddItem(SATCHEL_70, 1);
        else
            return;
    }
};

void AddSC_custom_level_rewards()
{
  new custom_level_rewards();
}
