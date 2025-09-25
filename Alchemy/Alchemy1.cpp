#include "Alchemy1.h"

#include <cassert>
#include <iomanip>
#include <typeinfo>

namespace alchemy1 {

void Flower::use(Character* target)
{
	// do nothing?
}


void Fang::use(Character* target)
{
	// do nothing?
}


void Eye::use(Character* target)
{
	// do nothing?
}


void HealthPotion::use(Character* target)
{
	target->addHealth(hp_);
}


void ManaPotion::use(Character* target)
{
	target->addMana(5); 
}


void Inventory::add(int slot, Item* item)
{
	assert(slot >= 0 && slot < kNumSlots);

	if (!items_[slot].empty() && typeid(items_[slot][0]) != typeid(item)) {
		return;
	}

	if (items_[slot].size() >= kStackMax) {
		return;
	}

	items_[slot].push_back(item);
}
 
void Inventory::removeOne(int slot)
{
	assert(slot >= 0 && slot < kNumSlots);

	if (!items_[slot].empty()) {
		items_[slot].pop_back();
	}
}

Item* Inventory::get(int slot)
{
	assert(slot >= 0 && slot < kNumSlots);

	if (items_[slot].empty()) 
		return nullptr;

	return items_[slot].back();
}

int Inventory::findSuitableSlot(Item* item)
{
	// slot is suitable, if
	// 1. there is a stack of same items with size < MAX
	for (int i = 0; i < kNumSlots; ++i) {
		if (items_[i].size() > 0 
				&& typeid(items_[i][0]) == typeid(item)
				&& items_[i].size() < kStackMax) {
			return i;
		}
	}

	// 2. there is an empty slot
	for (int i = 0; i < kNumSlots; ++i) {
		if (items_[i].size() == 0)
			return i;
	}

	return -1;
}

void Inventory::render(std::ostream& out) const
{
	std::ios_base::fmtflags sf = out.flags();

	for (auto s : items_) {
		if (s.empty()) {
			out << std::left << std::setw(0) << '[' << std::setw(16) << ' ' << std::setw(0) << ']' << std::endl;
		}
		else {
			out << std::left << std::setw(0) << '[' << std::setw(16) << s[0]->name() + "x" + std::to_string(s.size()) << std::setw(0) << ']' << std::endl;
		}
	}

	out.flags(sf);
}


void Cauldron::mix(const std::vector<Ingredient*>& ingredients)
{
	// implementation?
}


int main()
{
	Inventory inventory;
	Cauldron cauldron;

	Flower* flower1 = new Flower();
	Flower* flower2 = new Flower();
	Eye* eye = new Eye();

	inventory.add(0, flower1);
	inventory.add(0, flower2);
	inventory.add(1, eye);

	inventory.render(std::cout);


	std::vector<Ingredient*> ingredients;
	// dynamic_cast?
	//ingredients.push_back(inventory.get(0));
	//ingredients.push_back(inventory.get(1));

	cauldron.mix(ingredients);


	delete eye;
	delete flower1;
	delete flower2;

	return 0;
}

}