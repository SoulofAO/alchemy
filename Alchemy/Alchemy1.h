#pragma once

#include <iostream>
#include <array>
#include <memory>
#include <vector>
#include <string>


namespace alchemy1 {

class Character
{
public:
	int mana() const { return mana_; }
	void addMana(int delta) { mana_ += delta; }

	int health() const { return health_; }
	void addHealth(int delta) { health_ += delta; }

private:
	int mana_{ 0 };
	int health_{ 0 };
};


class Item {
public:
	enum class Kind {
		kUndef,
		kFlower,
		kEye,
		kFang,
		kManaPotion,
		kHealthPotion
	};

public:
	virtual std::string name() const = 0;
	virtual void use(Character *target) = 0;
};


class Ingredient : public Item {

};


class Flower : public Ingredient {
public:
	virtual std::string name() const override {
		return "Witch Flower";
	}

	virtual void use(Character* target) override;

};


class Fang : public Ingredient {
public:
	virtual std::string name() const override {
		return "Boar Fang";
	}

	virtual void use(Character* target) override;

};


class Eye : public Ingredient {
public:
	virtual std::string name() const override {
		return "Frog Eye";
	}

	virtual void use(Character* target) override;
};


class Potion : public Item {

};


class HealthPotion : public Potion {
public:
	HealthPotion()
		: hp_(10)
	{
	}

	virtual std::string name() const override {
		return "Potion of Health";
	}

	virtual void use(Character* target) override;

private:
	int hp_;
};


class ManaPotion : public Potion {
public:
	virtual std::string name() const override {
		return "Potion of Mana";
	}

	virtual void use(Character* target) override;

};


class Inventory final {
public:
	constexpr static int kNumSlots = 8;
	constexpr static int kStackMax = 4;

public:
	void add(int slot, Item* item);
	void removeOne(int slot);
	Item* get(int slot);
	int findSuitableSlot(Item* item);

public:
	void render(std::ostream& out) const;

private:
	// CLASS INVARIANT: all elements of the inner vector store items of the same kind
	std::array<std::vector<Item*>, kNumSlots> items_;
};


class Cauldron {
public:
	void mix(const std::vector<Ingredient*>& ingredients);
};


int main();

}
