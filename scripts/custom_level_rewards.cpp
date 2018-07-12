#include "ScriptMgr.h"
#include "DatabaseEnv.h"
#include "Player.h"
#include "Mail.h"
#include "Item.h"

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
        std::string subject = "Congratulations on Level " + std::to_string(player->getLevel());
        std::string text = "Here are your rewards!";
        uint32 receiverGUIDLow = player->GetGUID().GetCounter();
        uint32 senderGUIDLow = 0;
        uint32 stationary = MAIL_STATIONERY_DEFAULT;
        uint32 delay = 0;
        uint32 money = 0;
        uint32 cod = 0;
        std::map<uint32, uint32> items;

        uint8 newLevel = player->getLevel();

        if (newLevel < 15)
        {
            items.insert(std::pair<uint32, uint32>(SATCHEL_25, 1));
            switch (newLevel){
                case 5:
                    items.insert(std::pair<uint32, uint32>(TRAVELERS_BACKPACK, 1));
                    break;
                case 10:
                    items.insert(std::pair<uint32, uint32>(TRAVELERS_BACKPACK, 1));
                    break;
                default:
                    break;
            } 
        } 
        else if (newLevel < 25)
        {
            items.insert(std::pair<uint32, uint32>(SATCHEL_35, 1));
            switch (newLevel){
                case 15:
                    items.insert(std::pair<uint32, uint32>(TRAVELERS_BACKPACK, 1));
                    break;
                case 20:
                    items.insert(std::pair<uint32, uint32>(TRAVELERS_BACKPACK, 1));
                    break;
                default:
                    break;
            }
        }
        else if (newLevel < 35)
            items.insert(std::pair<uint32, uint32>(SATCHEL_45, 1));
        else if (newLevel < 45)
            items.insert(std::pair<uint32, uint32>(SATCHEL_55, 1));
        else if (newLevel < 50)
            items.insert(std::pair<uint32, uint32>(SATCHEL_60, 1));
        else if (newLevel < 55)
            items.insert(std::pair<uint32, uint32>(SATCHEL_65, 1));
        else if (newLevel < 61)
            items.insert(std::pair<uint32, uint32>(SATCHEL_70, 1));
        else if (newLevel < 81)
            money = 50000 * newLevel;
        else
            return;

        MailSender sender(MAIL_NORMAL, senderGUIDLow, (MailStationery)stationary);
        MailDraft draft(subject, text);

        if (cod)
            draft.AddCOD(cod);
        if (money)
            draft.AddMoney(money);

        SQLTransaction trans = CharacterDatabase.BeginTransaction();

        ASSERT(items.size() <= MAX_MAIL_ITEMS);

        for (auto& it : items)
        {
            uint32 entry = it.first;
            uint32 amount = it.second;

            //Need to figure out what this does
            //ItemTemplate const* item_proto = eObjectMgr->GetItemTemplate(entry);
            //ASSERT(item_proto);
            //ASSERT(amount < 1 || (item_proto->MaxCount > 0 && amount > uint32(item_proto->MaxCount)));
            if (Item* item = Item::CreateItem(entry, amount))
            {
                item->SaveToDB(trans);
                draft.AddItem(item);
            }
        }

        draft.SendMailTo(trans, MailReceiver(player), sender, MAIL_CHECK_MASK_NONE, delay);
        CharacterDatabase.CommitTransaction(trans);
        //Need to figure out how to update the player, so that it shows there is a new mail
    }
};

void AddSC_custom_level_rewards()
{
  new custom_level_rewards();
}
