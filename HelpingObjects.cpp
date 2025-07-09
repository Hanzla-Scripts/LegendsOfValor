
#include "24F-0505_24F-0580_Classes.h"
using namespace std;

HelpingObject::HelpingObject(const string& n, helpingObjects t, const string& desc, int qty, int effect, int p)
    : name(n), type(t), description(desc), quantity(qty), effectValue(effect), price(p) {
}

HelpingObject::HelpingObject(const HelpingObject& other)
    : name(other.getName()), type(other.getType()), description(other.getDescription()),
    quantity(other.getQuantity()), effectValue(other.getEffectValue()), price(other.getPrice()) {
}

HelpingObject::~HelpingObject() {}