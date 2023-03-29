#include "Key.h"

void Key::print(std::ostream &os) { os << m_name << ", umožňuje přístup do " << m_opens << std::endl; }

std::string Key::getOpens() const { return m_opens; }

Key::~Key() {

}

Key::Key(const std::string &name, const std::string &opens) : Item(Type::MISC, name), m_opens(opens) {}

void Key::save(std::fstream &output) {
    output << "KEY" << " " << m_name << " " << m_opens << std::endl;
}
