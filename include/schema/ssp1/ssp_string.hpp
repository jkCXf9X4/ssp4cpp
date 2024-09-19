
#pragma once

#include <string>
#include <optional>

#include "SystemStructureDescription.hpp"

namespace ssp4cpp::ssp1::ssd
{
    using namespace std;

    string to_string(const SystemGeometry &obj);
    string to_string(const optional<SystemGeometry> &obj);

    string to_string(const ConnectorGeometry &obj);
    string to_string(const optional<ConnectorGeometry> &obj);

    string to_string(const ElementGeometry &obj);
    string to_string(const optional<ElementGeometry> &obj);

    string to_string(const ConnectionGeometry &obj);
    string to_string(const optional<ConnectionGeometry> &obj);

    string to_string(const TSignalDictionaries &obj);
    string to_string(const optional<TSignalDictionaries> &obj);

    string to_string(const TParameterBindings &obj);
    string to_string(const optional<TParameterBindings> &obj);

    string to_string(const GraphicalElements &obj);
    string to_string(const optional<GraphicalElements> &obj);

    string to_string(const TDefaultExperiment &obj);
    string to_string(const optional<TDefaultExperiment> &obj);

    string to_string(const Connection &obj);
    string to_string(const optional<Connection> &obj);

    string to_string(const Connections &obj);
    string to_string(const optional<Connections> &obj);

    string to_string(const Connector &obj);
    string to_string(const optional<Connector> &obj);

    string to_string(const TConnectors &obj);
    string to_string(const optional<TConnectors> &obj);

    string to_string(const TComponent &obj);
    string to_string(const optional<TComponent> &obj);

    string to_string(const TSignalDictionaryReference &obj);
    string to_string(const optional<TSignalDictionaryReference> &obj);

    string to_string(const Elements &obj);
    string to_string(const optional<Elements> &obj);

    string to_string(const TSystem &obj);
    string to_string(const optional<TSystem> &obj);

    string to_string(const SystemStructureDescription &obj);
    string to_string(const optional<SystemStructureDescription> &obj);

}