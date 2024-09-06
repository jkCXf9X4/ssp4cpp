#include "common_xml_element.cpp"

namespace ssp4cpp::ssp1::ssd
{


    std::ostream &operator<<(std::ostream &os, const TSignalDictionaryReference &ref)
    {
        os << "TSignalDictionaryReference(dictionary: " << ref.dictionary << ")";
        return os;
    }

    void from_xml(const pugi::xml_node &node, TSignalDictionaryReference &ref)
    {
        BOOST_LOG_TRIVIAL(debug) << "Parsing TSignalDictionaryReference" << std::endl;

        ref.dictionary = get_attribute<string>(node, "dictionary");
    }
}