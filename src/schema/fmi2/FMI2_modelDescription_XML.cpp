

// This is a generated file, do not alter
// it is based on fmi2_md.toml

#include "xml_deserialize.hpp"
#include "FMI2_modelDescription_XML.hpp"


using namespace std;
using namespace pugi;
using namespace ssp4cpp::xml;

#include <boost/log/trivial.hpp>

namespace ssp4cpp::fmi2::md
{
    using namespace pugi;


    void from_xml(const xml_node &node, BaseUnit &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing BaseUnit" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.kg      , "kg");
        ssp4cpp::xml::parse_xml(node, obj.m       , "m");
        ssp4cpp::xml::parse_xml(node, obj.s       , "s");
        ssp4cpp::xml::parse_xml(node, obj.a       , "a");
        ssp4cpp::xml::parse_xml(node, obj.k       , "k");
        ssp4cpp::xml::parse_xml(node, obj.mol     , "mol");
        ssp4cpp::xml::parse_xml(node, obj.cd      , "cd");
        ssp4cpp::xml::parse_xml(node, obj.rad     , "rad");
        ssp4cpp::xml::parse_xml(node, obj.factor  , "factor");
        ssp4cpp::xml::parse_xml(node, obj.offset  , "offset");

        BOOST_LOG_TRIVIAL(trace) << "Completed BaseUnit" << std::endl;
    }


    void from_xml(const xml_node &node, DisplayUnit &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing DisplayUnit" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.name    , "name");
        ssp4cpp::xml::parse_xml(node, obj.factor  , "factor");
        ssp4cpp::xml::parse_xml(node, obj.offset  , "offset");

        BOOST_LOG_TRIVIAL(trace) << "Completed DisplayUnit" << std::endl;
    }


    void from_xml(const xml_node &node, fmi2Unit &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing fmi2Unit" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::xml::parse_xml(node, obj.BaseUnit     , "BaseUnit");
        ssp4cpp::xml::parse_xml(node, obj.DisplayUnit  , "DisplayUnit");

        BOOST_LOG_TRIVIAL(trace) << "Completed fmi2Unit" << std::endl;
    }


    void from_xml(const xml_node &node, UnitDefinitions &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing UnitDefinitions" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.Units  , "Unit");

        BOOST_LOG_TRIVIAL(trace) << "Completed UnitDefinitions" << std::endl;
    }


    void from_xml(const xml_node &node, Boolean &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Boolean" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.declaredType  , "declaredType");
        ssp4cpp::xml::parse_xml(node, obj.start         , "start");

        BOOST_LOG_TRIVIAL(trace) << "Completed Boolean" << std::endl;
    }


    void from_xml(const xml_node &node, Integer &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Integer" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.declaredType  , "declaredType");
        ssp4cpp::xml::parse_xml(node, obj.start         , "start");
        ssp4cpp::xml::parse_xml(node, obj.quantity      , "quantity");
        ssp4cpp::xml::parse_xml(node, obj.min           , "min");
        ssp4cpp::xml::parse_xml(node, obj.max           , "max");

        BOOST_LOG_TRIVIAL(trace) << "Completed Integer" << std::endl;
    }


    void from_xml(const xml_node &node, String &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing String" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.declaredType  , "declaredType");
        ssp4cpp::xml::parse_xml(node, obj.start         , "start");

        BOOST_LOG_TRIVIAL(trace) << "Completed String" << std::endl;
    }


    void from_xml(const xml_node &node, Real &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Real" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.declaredType      , "declaredType");
        ssp4cpp::xml::parse_xml(node, obj.quantity          , "quantity");
        ssp4cpp::xml::parse_xml(node, obj.unit              , "unit");
        ssp4cpp::xml::parse_xml(node, obj.displayUnit       , "displayUnit");
        ssp4cpp::xml::parse_xml(node, obj.relativeQuantity  , "relativeQuantity");
        ssp4cpp::xml::parse_xml(node, obj.min               , "min");
        ssp4cpp::xml::parse_xml(node, obj.max               , "max");
        ssp4cpp::xml::parse_xml(node, obj.nominal           , "nominal");
        ssp4cpp::xml::parse_xml(node, obj.unbounded         , "unbounded");
        ssp4cpp::xml::parse_xml(node, obj.start             , "start");
        ssp4cpp::xml::parse_xml(node, obj.derivative        , "derivative");
        ssp4cpp::xml::parse_xml(node, obj.reinit            , "reinit");

        BOOST_LOG_TRIVIAL(trace) << "Completed Real" << std::endl;
    }


    void from_xml(const xml_node &node, Enumeration &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Enumeration" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.declaredType  , "declaredType");
        ssp4cpp::xml::parse_xml(node, obj.quantity      , "quantity");
        ssp4cpp::xml::parse_xml(node, obj.min           , "min");
        ssp4cpp::xml::parse_xml(node, obj.max           , "max");
        ssp4cpp::xml::parse_xml(node, obj.start         , "start");

        BOOST_LOG_TRIVIAL(trace) << "Completed Enumeration" << std::endl;
    }


    void from_xml(const xml_node &node, SimpleTypeEnumerationItem &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing SimpleTypeEnumerationItem" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::xml::parse_xml(node, obj.value        , "value");
        ssp4cpp::xml::parse_xml(node, obj.description  , "description");

        BOOST_LOG_TRIVIAL(trace) << "Completed SimpleTypeEnumerationItem" << std::endl;
    }


    void from_xml(const xml_node &node, SimpleTypeEnumeration &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing SimpleTypeEnumeration" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.quantity  , "quantity");
        ssp4cpp::xml::parse_xml(node, obj.Items     , "Item");

        BOOST_LOG_TRIVIAL(trace) << "Completed SimpleTypeEnumeration" << std::endl;
    }


    void from_xml(const xml_node &node, fmi2SimpleType &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing fmi2SimpleType" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::xml::parse_xml(node, obj.description  , "description");
        ssp4cpp::xml::parse_xml(node, obj.Real         , "Real");
        ssp4cpp::xml::parse_xml(node, obj.Integer      , "Integer");
        ssp4cpp::xml::parse_xml(node, obj.Boolean      , "Boolean");
        ssp4cpp::xml::parse_xml(node, obj.String       , "String");
        ssp4cpp::xml::parse_xml(node, obj.Enumeration  , "Enumeration");

        BOOST_LOG_TRIVIAL(trace) << "Completed fmi2SimpleType" << std::endl;
    }


    void from_xml(const xml_node &node, TypeDefinitions &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TypeDefinitions" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.SimpleTypes  , "SimpleType");

        BOOST_LOG_TRIVIAL(trace) << "Completed TypeDefinitions" << std::endl;
    }


    void from_xml(const xml_node &node, Category &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Category" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::xml::parse_xml(node, obj.description  , "description");

        BOOST_LOG_TRIVIAL(trace) << "Completed Category" << std::endl;
    }


    void from_xml(const xml_node &node, LogCategories &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing LogCategories" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.Categories  , "Category");

        BOOST_LOG_TRIVIAL(trace) << "Completed LogCategories" << std::endl;
    }


    void from_xml(const xml_node &node, fmi2Annotation &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing fmi2Annotation" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.annotation  , "annotation");

        BOOST_LOG_TRIVIAL(trace) << "Completed fmi2Annotation" << std::endl;
    }


    void from_xml(const xml_node &node, VendorAnnotations &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing VendorAnnotations" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.Annotations  , "Annotation");

        BOOST_LOG_TRIVIAL(trace) << "Completed VendorAnnotations" << std::endl;
    }


    void from_xml(const xml_node &node, DefaultExperiment &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing DefaultExperiment" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.startTime  , "startTime");
        ssp4cpp::xml::parse_xml(node, obj.stopTime   , "stopTime");
        ssp4cpp::xml::parse_xml(node, obj.tolerance  , "tolerance");
        ssp4cpp::xml::parse_xml(node, obj.stepSize   , "stepSize");

        BOOST_LOG_TRIVIAL(trace) << "Completed DefaultExperiment" << std::endl;
    }


    void from_xml(const xml_node &node, fmi2ScalarVariable &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing fmi2ScalarVariable" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.name                                , "name");
        ssp4cpp::xml::parse_xml(node, obj.valueReference                      , "valueReference");
        ssp4cpp::xml::parse_xml(node, obj.description                         , "description");
        ssp4cpp::xml::parse_xml(node, obj.causality                           , "causality");
        ssp4cpp::xml::parse_xml(node, obj.variability                         , "variability");
        ssp4cpp::xml::parse_xml(node, obj.initial                             , "initial");
        ssp4cpp::xml::parse_xml(node, obj.canHandleMultipleSetPerTimeInstant  , "canHandleMultipleSetPerTimeInstant");
        ssp4cpp::xml::parse_xml(node, obj.Real                                , "Real");
        ssp4cpp::xml::parse_xml(node, obj.Integer                             , "Integer");
        ssp4cpp::xml::parse_xml(node, obj.Boolean                             , "Boolean");
        ssp4cpp::xml::parse_xml(node, obj.String                              , "String");
        ssp4cpp::xml::parse_xml(node, obj.Enumeration                         , "Enumeration");
        ssp4cpp::xml::parse_xml(node, obj.Annotations                         , "Annotation");

        BOOST_LOG_TRIVIAL(trace) << "Completed fmi2ScalarVariable" << std::endl;
    }


    void from_xml(const xml_node &node, Unknown &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Unknown" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.index             , "index");
        ssp4cpp::xml::parse_xml(node, obj.dependencies      , "dependencies");
        ssp4cpp::xml::parse_xml(node, obj.dependenciesKind  , "dependenciesKind");

        BOOST_LOG_TRIVIAL(trace) << "Completed Unknown" << std::endl;
    }


    void from_xml(const xml_node &node, Outputs &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Outputs" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.Unknowns  , "Unknown");

        BOOST_LOG_TRIVIAL(trace) << "Completed Outputs" << std::endl;
    }


    void from_xml(const xml_node &node, Derivatives &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Derivatives" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.Unknowns  , "Unknown");

        BOOST_LOG_TRIVIAL(trace) << "Completed Derivatives" << std::endl;
    }


    void from_xml(const xml_node &node, InitialUnknowns &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing InitialUnknowns" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.Unknowns  , "Unknown");

        BOOST_LOG_TRIVIAL(trace) << "Completed InitialUnknowns" << std::endl;
    }


    void from_xml(const xml_node &node, ModelStructure &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing ModelStructure" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.Outputs          , "Outputs");
        ssp4cpp::xml::parse_xml(node, obj.Derivatives      , "Derivatives");
        ssp4cpp::xml::parse_xml(node, obj.InitialUnknowns  , "InitialUnknowns");

        BOOST_LOG_TRIVIAL(trace) << "Completed ModelStructure" << std::endl;
    }


    void from_xml(const xml_node &node, ModelVariables &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing ModelVariables" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.ScalarVariable  , "ScalarVariable");

        BOOST_LOG_TRIVIAL(trace) << "Completed ModelVariables" << std::endl;
    }


    void from_xml(const xml_node &node, File &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing File" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.name  , "name");

        BOOST_LOG_TRIVIAL(trace) << "Completed File" << std::endl;
    }


    void from_xml(const xml_node &node, SourceFiles &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing SourceFiles" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.Files  , "File");

        BOOST_LOG_TRIVIAL(trace) << "Completed SourceFiles" << std::endl;
    }


    void from_xml(const xml_node &node, ModelExchange &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing ModelExchange" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.modelIdentifier                      , "modelIdentifier");
        ssp4cpp::xml::parse_xml(node, obj.needsExecutionTool                   , "needsExecutionTool");
        ssp4cpp::xml::parse_xml(node, obj.completedIntegratorStepNotNeeded     , "completedIntegratorStepNotNeeded");
        ssp4cpp::xml::parse_xml(node, obj.canBeInstantiatedOnlyOncePerProcess  , "canBeInstantiatedOnlyOncePerProcess");
        ssp4cpp::xml::parse_xml(node, obj.canNotUseMemoryManagementFunctions   , "canNotUseMemoryManagementFunctions");
        ssp4cpp::xml::parse_xml(node, obj.canGetAndSetFMUstate                 , "canGetAndSetFMUstate");
        ssp4cpp::xml::parse_xml(node, obj.canSerializeFMUstate                 , "canSerializeFMUstate");
        ssp4cpp::xml::parse_xml(node, obj.providesDirectionalDerivatives       , "providesDirectionalDerivatives");
        ssp4cpp::xml::parse_xml(node, obj.SourceFiles                          , "SourceFiles");

        BOOST_LOG_TRIVIAL(trace) << "Completed ModelExchange" << std::endl;
    }


    void from_xml(const xml_node &node, CoSimulation &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing CoSimulation" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.modelIdentifier                         , "modelIdentifier");
        ssp4cpp::xml::parse_xml(node, obj.needsExecutionTool                      , "needsExecutionTool");
        ssp4cpp::xml::parse_xml(node, obj.canHandleVariableCommunicationStepSize  , "canHandleVariableCommunicationStepSize");
        ssp4cpp::xml::parse_xml(node, obj.canInterpolateInputs                    , "canInterpolateInputs");
        ssp4cpp::xml::parse_xml(node, obj.maxOutputDerivativeOrder                , "maxOutputDerivativeOrder");
        ssp4cpp::xml::parse_xml(node, obj.canRunAsynchronuously                   , "canRunAsynchronuously");
        ssp4cpp::xml::parse_xml(node, obj.canBeInstantiatedOnlyOncePerProcess     , "canBeInstantiatedOnlyOncePerProcess");
        ssp4cpp::xml::parse_xml(node, obj.canNotUseMemoryManagementFunctions      , "canNotUseMemoryManagementFunctions");
        ssp4cpp::xml::parse_xml(node, obj.canGetAndSetFMUstate                    , "canGetAndSetFMUstate");
        ssp4cpp::xml::parse_xml(node, obj.canSerializeFMUstate                    , "canSerializeFMUstate");
        ssp4cpp::xml::parse_xml(node, obj.providesDirectionalDerivatives          , "providesDirectionalDerivatives");
        ssp4cpp::xml::parse_xml(node, obj.SourceFiles                             , "SourceFiles");

        BOOST_LOG_TRIVIAL(trace) << "Completed CoSimulation" << std::endl;
    }


    void from_xml(const xml_node &node, fmi2ModelDescription &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing fmi2ModelDescription" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.fmiVersion                , "fmiVersion");
        ssp4cpp::xml::parse_xml(node, obj.modelName                 , "modelName");
        ssp4cpp::xml::parse_xml(node, obj.guid                      , "guid");
        ssp4cpp::xml::parse_xml(node, obj.description               , "description");
        ssp4cpp::xml::parse_xml(node, obj.author                    , "author");
        ssp4cpp::xml::parse_xml(node, obj.version                   , "version");
        ssp4cpp::xml::parse_xml(node, obj.copyright                 , "copyright");
        ssp4cpp::xml::parse_xml(node, obj.license                   , "license");
        ssp4cpp::xml::parse_xml(node, obj.generationTool            , "generationTool");
        ssp4cpp::xml::parse_xml(node, obj.generationDateAndTime     , "generationDateAndTime");
        ssp4cpp::xml::parse_xml(node, obj.variableNamingConvention  , "variableNamingConvention");
        ssp4cpp::xml::parse_xml(node, obj.numberOfEventIndicators   , "numberOfEventIndicators");
        ssp4cpp::xml::parse_xml(node, obj.ModelExchange             , "ModelExchange");
        ssp4cpp::xml::parse_xml(node, obj.CoSimulation              , "CoSimulation");
        ssp4cpp::xml::parse_xml(node, obj.UnitDefinitions           , "UnitDefinitions");
        ssp4cpp::xml::parse_xml(node, obj.TypeDefinitions           , "TypeDefinitions");
        ssp4cpp::xml::parse_xml(node, obj.LogCategories             , "LogCategories");
        ssp4cpp::xml::parse_xml(node, obj.DefaultExperiment         , "DefaultExperiment");
        ssp4cpp::xml::parse_xml(node, obj.VendorAnnotations         , "VendorAnnotations");
        ssp4cpp::xml::parse_xml(node, obj.ModelVariables            , "ModelVariables");
        ssp4cpp::xml::parse_xml(node, obj.ModelStructure            , "ModelStructure");

        BOOST_LOG_TRIVIAL(trace) << "Completed fmi2ModelDescription" << std::endl;
    }

}
