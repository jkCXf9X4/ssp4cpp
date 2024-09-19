#include <boost/log/trivial.hpp>

#include "modelDescription_XML.hpp"

#include "xml_deserialize.hpp"

using namespace std;
using namespace pugi;
using namespace ssp4cpp::xml;


namespace ssp4cpp::fmi2
{

    void from_xml(const xml_node &node, BaseUnit &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing BaseUnit" << std::endl;

        obj.kg = get_optional_attribute<int>(node, "kg");
        obj.m = get_optional_attribute<int>(node, "m");
        obj.s = get_optional_attribute<int>(node, "s");
        obj.a = get_optional_attribute<int>(node, "a");
        obj.k = get_optional_attribute<int>(node, "k");
        obj.mol = get_optional_attribute<int>(node, "mol");
        obj.cd = get_optional_attribute<int>(node, "cd");
        obj.rad = get_optional_attribute<int>(node, "rad");
        obj.factor = get_optional_attribute<double>(node, "factor");
        obj.offset = get_optional_attribute<double>(node, "offset");

        BOOST_LOG_TRIVIAL(trace) << "Completed BaseUnit" << std::endl;
    }

    void from_xml(const xml_node &node, DisplayUnit &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing DisplayUnit" << std::endl;

        obj.name = get_attribute<string>(node, "name");
        obj.factor = get_optional_attribute<double>(node, "factor");
        obj.offset = get_optional_attribute<double>(node, "offset");

        BOOST_LOG_TRIVIAL(trace) << "Completed DisplayUnit" << std::endl;
    }

    void from_xml(const xml_node &node, fmi2Unit &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing fmi2Unit" << std::endl;

        obj.name = get_attribute<string>(node, "name");
        get_optional_class(node, "BaseUnit", obj.BaseUnit);
        get_vector(node, "DisplayUnit", obj.DisplayUnit);

        BOOST_LOG_TRIVIAL(trace) << "Completed fmi2Unit" << std::endl;
    }

    void from_xml(const xml_node &node, UnitDefinitions &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing UnitDefinitions" << std::endl;

        get_vector(node, "Units", obj.Units);

        BOOST_LOG_TRIVIAL(trace) << "Completed UnitDefinitions" << std::endl;
    }

    void from_xml(const xml_node &node, Boolean &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Boolean" << std::endl;

        obj.declaredType = get_optional_attribute<string>(node, "declaredType");
        obj.start = get_optional_attribute<string>(node, "start");

        BOOST_LOG_TRIVIAL(trace) << "Completed Boolean" << std::endl;
    }

    void from_xml(const xml_node &node, Integer &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Integer" << std::endl;

        obj.declaredType = get_optional_attribute<string>(node, "declaredType");
        obj.start = get_optional_attribute<string>(node, "start");
        obj.quantity = get_optional_attribute<string>(node, "quantity");
        obj.min = get_optional_attribute<int>(node, "min");
        obj.max = get_optional_attribute<int>(node, "max");

        BOOST_LOG_TRIVIAL(trace) << "Completed Integer" << std::endl;
    }

    void from_xml(const xml_node &node, String &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing String" << std::endl;

        obj.declaredType = get_optional_attribute<string>(node, "declaredType");
        obj.start = get_optional_attribute<string>(node, "start");

        BOOST_LOG_TRIVIAL(trace) << "Completed String" << std::endl;
    }

    void from_xml(const xml_node &node, Real &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Real" << std::endl;

        obj.declaredType = get_optional_attribute<string>(node, "declaredType");
        obj.quantity = get_optional_attribute<string>(node, "quantity");
        obj.unit = get_optional_attribute<string>(node, "unit");
        obj.displayUnit = get_optional_attribute<string>(node, "displayUnit");
        obj.relativeQuantity = get_optional_attribute<bool>(node, "relativeQuantity");
        obj.min = get_optional_attribute<double>(node, "min");
        obj.max = get_optional_attribute<double>(node, "max");
        obj.nominal = get_optional_attribute<double>(node, "nominal");
        obj.unbounded = get_optional_attribute<bool>(node, "unbounded");
        obj.start = get_optional_attribute<double>(node, "start");
        obj.derivative = get_optional_attribute<unsigned int>(node, "derivative");
        obj.reinit = get_optional_attribute<bool>(node, "reinit");

        BOOST_LOG_TRIVIAL(trace) << "Completed Real" << std::endl;
    }

    void from_xml(const xml_node &node, Enumeration &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Enumeration" << std::endl;

        obj.declaredType = get_attribute<string>(node, "declaredType");
        obj.quantity = get_optional_attribute<string>(node, "quantity");
        obj.min = get_optional_attribute<int>(node, "min");
        obj.max = get_optional_attribute<int>(node, "max");
        obj.start = get_optional_attribute<int>(node, "start");

        BOOST_LOG_TRIVIAL(trace) << "Completed Enumeration" << std::endl;
    }

    void from_xml(const xml_node &node, SimpleTypeEnumerationItem &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing SimpleTypeEnumerationItem" << std::endl;

        obj.name = get_attribute<string>(node, "name");
        obj.value = get_attribute<int>(node, "value");
        obj.description = get_optional_attribute<string>(node, "description");

        BOOST_LOG_TRIVIAL(trace) << "Completed SimpleTypeEnumerationItem" << std::endl;
    }

    void from_xml(const xml_node &node, SimpleTypeEnumeration &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing SimpleTypeEnumeration" << std::endl;

        obj.quantity = get_optional_attribute<string>(node, "quantity");
        get_vector(node, "item", obj.item);

        BOOST_LOG_TRIVIAL(trace) << "Completed SimpleTypeEnumeration" << std::endl;
    }

    void from_xml(const xml_node &node, fmi2SimpleType &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing fmi2SimpleType" << std::endl;

        obj.name = get_attribute<string>(node, "name");
        obj.description = get_optional_attribute<string>(node, "description");
        get_optional_class(node, "Real", obj.Real);
        get_optional_class(node, "Integer", obj.Integer);
        get_optional_class(node, "Boolean", obj.Boolean);
        get_optional_class(node, "String", obj.String);
        get_optional_class(node, "Enumeration", obj.Enumeration);

        BOOST_LOG_TRIVIAL(trace) << "Completed fmi2SimpleType" << std::endl;
    }

    void from_xml(const xml_node &node, TypeDefinitions &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TypeDefinitions" << std::endl;

        get_vector(node, "SimpleTypes", obj.SimpleTypes);

        BOOST_LOG_TRIVIAL(trace) << "Completed TypeDefinitions" << std::endl;
    }

    void from_xml(const xml_node &node, Category &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Category" << std::endl;

        obj.name = get_attribute<string>(node, "name");
        obj.description = get_optional_attribute<string>(node, "description");

        BOOST_LOG_TRIVIAL(trace) << "Completed Category" << std::endl;
    }

    void from_xml(const xml_node &node, LogCategories &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing LogCategories" << std::endl;

        get_vector(node, "categories", obj.categories);

        BOOST_LOG_TRIVIAL(trace) << "Completed LogCategories" << std::endl;
    }

    void from_xml(const xml_node &node, fmi2Annotation &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing fmi2Annotation" << std::endl;

        obj.annotation = get_attribute<string>(node, "annotation");

        BOOST_LOG_TRIVIAL(trace) << "Completed fmi2Annotation" << std::endl;
    }

    void from_xml(const xml_node &node, VendorAnnotations &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing VendorAnnotations" << std::endl;

        get_vector(node, "Annotations", obj.Annotations);

        BOOST_LOG_TRIVIAL(trace) << "Completed VendorAnnotations" << std::endl;
    }

    void from_xml(const xml_node &node, DefaultExperiment &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing DefaultExperiment" << std::endl;

        obj.startTime = get_optional_attribute<double>(node, "startTime");
        obj.stopTime = get_optional_attribute<double>(node, "stopTime");
        obj.tolerance = get_optional_attribute<double>(node, "tolerance");
        obj.stepSize = get_optional_attribute<double>(node, "stepSize");

        BOOST_LOG_TRIVIAL(trace) << "Completed DefaultExperiment" << std::endl;
    }

    void from_xml(const xml_node &node, fmi2ScalarVariable &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing fmi2ScalarVariable" << std::endl;

        obj.name = get_attribute<string>(node, "name");
        obj.valueReference = get_optional_attribute<unsigned int>(node, "valueReference");
        obj.description = get_optional_attribute<string>(node, "description");
        obj.causality = get_optional_attribute<string>(node, "causality");
        obj.variability = get_optional_attribute<string>(node, "variability");
        obj.initial = get_optional_attribute<string>(node, "initial");
        obj.canHandleMultipleSetPerTimeInstant = get_optional_attribute<bool>(node, "canHandleMultipleSetPerTimeInstant");
        get_optional_class(node, "Real", obj.Real);
        get_optional_class(node, "Integer", obj.Integer);
        get_optional_class(node, "Boolean", obj.Boolean);
        get_optional_class(node, "String", obj.String);
        get_optional_class(node, "Enumeration", obj.Enumeration);
        get_vector(node, "Annotations", obj.Annotations);

        BOOST_LOG_TRIVIAL(trace) << "Completed fmi2ScalarVariable" << std::endl;
    }

    void from_xml(const xml_node &node, unknown &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing unknown" << std::endl;

        obj.index = get_attribute<int>(node, "index");
        obj.dependencies = get_attribute<string>(node, "dependencies");
        obj.dependenciesKind = get_attribute<string>(node, "dependenciesKind");

        BOOST_LOG_TRIVIAL(trace) << "Completed unknown" << std::endl;
    }

    void from_xml(const xml_node &node, ModelStructure &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing ModelStructure" << std::endl;

        get_vector(node, "outputs", obj.outputs);
        get_vector(node, "derivatives", obj.derivatives);
        get_vector(node, "initialUnknowns", obj.initialUnknowns);

        BOOST_LOG_TRIVIAL(trace) << "Completed ModelStructure" << std::endl;
    }

    void from_xml(const xml_node &node, ModelVariables &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing ModelVariables" << std::endl;

        get_vector(node, "ScalarVariable", obj.ScalarVariable);

        BOOST_LOG_TRIVIAL(trace) << "Completed ModelVariables" << std::endl;
    }

    void from_xml(const xml_node &node, File &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing File" << std::endl;

        obj.name = get_attribute<string>(node, "name");

        BOOST_LOG_TRIVIAL(trace) << "Completed File" << std::endl;
    }

    void from_xml(const xml_node &node, ModelExchange &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing ModelExchange" << std::endl;

        obj.modelIdentifier = get_attribute<string>(node, "modelIdentifier");
        obj.needsExecutionTool = get_optional_attribute<bool>(node, "needsExecutionTool");
        obj.completedIntegratorStepNotNeeded = get_optional_attribute<bool>(node, "completedIntegratorStepNotNeeded");
        obj.canBeInstantiatedOnlyOncePerProcess = get_optional_attribute<bool>(node, "canBeInstantiatedOnlyOncePerProcess");
        obj.canNotUseMemoryManagementFunctions = get_optional_attribute<bool>(node, "canNotUseMemoryManagementFunctions");
        obj.canGetAndSetFMUstate = get_optional_attribute<bool>(node, "canGetAndSetFMUstate");
        obj.canSerializeFMUstate = get_optional_attribute<bool>(node, "canSerializeFMUstate");
        obj.providesDirectionalDerivatives = get_optional_attribute<bool>(node, "providesDirectionalDerivatives");
        get_vector(node, "SourceFiles", obj.SourceFiles);

        BOOST_LOG_TRIVIAL(trace) << "Completed ModelExchange" << std::endl;
    }

    void from_xml(const xml_node &node, CoSimulation &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing CoSimulation" << std::endl;

        obj.modelIdentifier = get_attribute<string>(node, "modelIdentifier");
        obj.needsExecutionTool = get_optional_attribute<bool>(node, "needsExecutionTool");
        obj.canHandleVariableCommunicationStepSize = get_optional_attribute<bool>(node, "canHandleVariableCommunicationStepSize");
        obj.canInterpolateInputs = get_optional_attribute<bool>(node, "canInterpolateInputs");
        obj.maxOutputDerivativeOrder = get_optional_attribute<bool>(node, "maxOutputDerivativeOrder");
        obj.canRunAsynchronuously = get_optional_attribute<bool>(node, "canRunAsynchronuously");
        obj.canBeInstantiatedOnlyOncePerProcess = get_optional_attribute<bool>(node, "canBeInstantiatedOnlyOncePerProcess");
        obj.canNotUseMemoryManagementFunctions = get_optional_attribute<bool>(node, "canNotUseMemoryManagementFunctions");
        obj.canGetAndSetFMUstate = get_optional_attribute<bool>(node, "canGetAndSetFMUstate");
        obj.canSerializeFMUstate = get_optional_attribute<bool>(node, "canSerializeFMUstate");
        obj.providesDirectionalDerivatives = get_optional_attribute<bool>(node, "providesDirectionalDerivatives");
        get_vector(node, "SourceFiles", obj.SourceFiles);

        BOOST_LOG_TRIVIAL(trace) << "Completed CoSimulation" << std::endl;
    }

    void from_xml(const xml_node &node, fmi2ModelDescription &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing fmi2ModelDescription" << std::endl;

        obj.fmiVersion = get_attribute<string>(node, "fmiVersion");
        obj.modelName = get_attribute<string>(node, "modelName");
        obj.guid = get_attribute<string>(node, "guid");
        obj.description = get_optional_attribute<string>(node, "description");
        obj.author = get_optional_attribute<string>(node, "author");
        obj.version = get_optional_attribute<string>(node, "version");
        obj.copyright = get_optional_attribute<string>(node, "copyright");
        obj.license = get_optional_attribute<string>(node, "license");
        obj.generationTool = get_optional_attribute<string>(node, "generationTool");
        obj.generationDateAndTime = get_optional_attribute<string>(node, "generationDateAndTime");
        obj.variableNamingConvention = get_optional_attribute<string>(node, "variableNamingConvention");
        obj.numberOfEventIndicators = get_optional_attribute<string>(node, "numberOfEventIndicators");
        get_optional_class(node, "ModelExchange", obj.ModelExchange);
        get_optional_class(node, "CoSimulation", obj.CoSimulation);
        get_optional_class(node, "UnitDefinitions", obj.UnitDefinitions);
        get_optional_class(node, "TypeDefinitions", obj.TypeDefinitions);
        get_optional_class(node, "LogCategories", obj.LogCategories);
        get_optional_class(node, "DefaultExperiment", obj.DefaultExperiment);
        get_optional_class(node, "VendorAnnotations", obj.VendorAnnotations);
        from_xml(node.child("ModelVariables"), obj.ModelVariables);
        from_xml(node.child("ModelStructure"), obj.ModelStructure);

        BOOST_LOG_TRIVIAL(trace) << "Completed fmi2ModelDescription" << std::endl;
    }

}
