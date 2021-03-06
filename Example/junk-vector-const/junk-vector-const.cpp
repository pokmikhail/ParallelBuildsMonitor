// junk-vector-const.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <map>


struct Item
{
    int width = 3;
    int length = 4;
};


class Collection
{
public:
    void Fill()
    {
        vec.push_back(new Item);
        vec.push_back(new Item{ 7,9 });
        vec.push_back(new Item{ 12, 16 });
    }

    //THIS IS WRONG - We can modify item in this way!!
    const std::vector<Item*>& GetMembers()
    {
        return vec;
    }

    //THIS IS CORRECT - Can't modify Item
    std::vector<const Item*> GetMembersCCC() const
    {
        return std::vector<const Item*>(vec.begin(), vec.end());
    }

protected:
    std::vector<Item*> vec;
};





class MapCollection
{
public:
    void Fill()
    {
        map.insert({ "a", new Item });
        map.insert({ "b", new Item{ 7,9 } });
        map.insert({ "c", new Item{ 12, 16 } });
    }

    // HALF CORRECT
    // This is actually a little correct because oprator[] in map isn't const. This is suprising!
    // Value can be modifie by .at() method!!    and this is WRONG!!!
    const std::map<std::string, Item*>& GetMembers()
    {
        return map;
    }

    //THIS IS CORRECT - Can't modify Item
    std::map<std::string, const Item*> GetMembersCCC() const
    {
        return std::map<std::string, const Item*>(map.begin(), map.end());
    }

    //THIS IS CORRECT - Can't modify Item, however slow
    std::vector<const Item*> GetMembersAsVector() const
    {
        std::vector<const Item*> vec;
        vec.reserve(map.size());
        for (const auto &pair : map)
            vec.push_back(pair.second);

        return vec;
    }


protected:
    std::map<std::string, Item*> map;
};





int main()
{
    Collection col;
    col.Fill();
    const std::vector<Item*>& members = col.GetMembers();
    members;
    Item* pItem = members[0]; //THIS IS WRONG - We can modify item in this way!!
    pItem->width = 0; //THIS IS WRONG - We can modify item in this way!!

    std::vector<const Item*> membersCCC = col.GetMembersCCC();
    membersCCC;
    const Item* pItemCCC = membersCCC[0]; 
    //pItemCCC->width = 0; //THIS IS CORRECT - Can't modify Item
    pItemCCC;


    MapCollection mapcol;
    mapcol.Fill();
    const std::map<std::string, Item*>& mapmembers = mapcol.GetMembers();
    mapmembers;
    //const Item* pMapItem = mapmembers["a"]; //This is actually correct because oprator[] in map isn't const. This is suprising!
    //pMapItem->width = 0;
    Item* pMapItem = mapmembers.at("a"); //This is actually correct because oprator[] in map isn't const. This is suprising!
    pMapItem->width = 0; //THIS IS WRONG - We can modify item in this way!!


    std::map<std::string, const Item*> mapmembersCCC = mapcol.GetMembersCCC();
    mapmembersCCC;
    const Item* pMapItemCCC = mapmembersCCC["a"];
    //pMapItemCCC->width = 0; //THIS IS CORRECT - Can't modify Item
    pMapItemCCC;

    std::vector<const Item*> mapToVec = mapcol.GetMembersAsVector();
    const Item* pMapToVecItem = mapToVec[0];
    //pMapToVecItem->width = 0; //THIS IS CORRECT - Can't modify Item
    pMapToVecItem;



    return 0;
}

