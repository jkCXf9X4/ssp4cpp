

// This is a generated file, do not alter
// it is based on fmi2_md.toml

#include "FMI2_modelDescription_XML.hpp"


#include "xml_deserialize.hpp"

#include "common_log.hpp"

namespace ssp4cpp::fmi2::md
{
    using namespace pugi;
    using namespace common;

    auto log = Logger("ssp4cpp.fmi2.md", LogLevel::info);


    void from_xml(const xml_node &node, BaseUnit &obj)
    {
        log.ext_trace("Parsing BaseUnit");

        ssp4cpp::common::xml::parse_xml(node, obj.kg      , "kg");
        ssp4cpp::common::xml::parse_xml(node, obj.m       , "m");
        ssp4cpp::common::xml::parse_xml(node, obj.s       , "s");
        ssp4cpp::common::xml::parse_xml(node, obj.a       , "a");
        ssp4cpp::common::xml::parse_xml(node, obj.k       , "k");
        ssp4cpp::common::xml::parse_xml(node, obj.mol     , "mol");
        ssp4cpp::common::xml::parse_xml(node, obj.cd      , "cd");
        ssp4cpp::common::xml::parse_xml(node, obj.rad     , "rad");
        ssp4cpp::common::xml::parse_xml(node, obj.factor  , "factor");
        ssp4cpp::common::xml::parse_xml(node, obj.offset  , "offset");

        log.ext_trace("Completed BaseUnit");
    }


    void from_xml(const xml_node &node, DisplayUnit &obj)
    {
        log.ext_trace("Parsing DisplayUnit");

        ssp4cpp::common::xml::parse_xml(node, obj.name    , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.factor  , "factor");
        ssp4cpp::common::xml::parse_xml(node, obj.offset  , "offset");

        log.ext_trace("Completed DisplayUnit");
    }


    void from_xml(const xml_node &node, fmi2Unit &obj)
    {
        log.ext_trace("Parsing fmi2Unit");

        ssp4cpp::common::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.BaseUnit     , "BaseUnit");
        ssp4cpp::common::xml::parse_xml(node, obj.DisplayUnit  , "DisplayUnit");

        log.ext_trace("Completed fmi2Unit");
    }


    void from_xml(const xml_node &node, UnitDefinitions &obj)
    {
        log.ext_trace("Parsing UnitDefinitions");

        ssp4cpp::common::xml::parse_xml(node, obj.Units  , "Unit");

        log.ext_trace("Completed UnitDefinitions");
    }


    void from_xml(const xml_node &node, Boolean &obj)
    {
        log.ext_trace("Parsing Boolean");

        ssp4cpp::common::xml::parse_xml(node, obj.declaredType  , "declaredType");
        ssp4cpp::common::xml::parse_xml(node, obj.start         , "start");

        log.ext_trace("Completed Boolean");
    }


    void from_xml(const xml_node &node, Integer &obj)
    {
        log.ext_trace("Parsing Integer");

        ssp4cpp::common::xml::parse_xml(node, obj.declaredType  , "declaredType");
        ssp4cpp::common::xml::parse_xml(node, obj.start         , "start");
        ssp4cpp::common::xml::parse_xml(node, obj.quantity      , "quantity");
        ssp4cpp::common::xml::parse_xml(node, obj.min           , "min");
        ssp4cpp::common::xml::parse_xml(node, obj.max           , "max");

        log.ext_trace("Completed Integer");
    }


    void from_xml(const xml_node &node, String &obj)
    {
        log.ext_trace("Parsing String");

        ssp4cpp::common::xml::parse_xml(node, obj.declaredType  , "declaredType");
        ssp4cpp::common::xml::parse_xml(node, obj.start         , "start");

        log.ext_trace("Completed String");
    }


    void from_xml(const xml_node &node, Real &obj)
    {
        log.ext_trace("Parsing Real");

        ssp4cpp::common::xml::parse_xml(node, obj.declaredType      , "declaredType");
        ssp4cpp::common::xml::parse_xml(node, obj.quantity          , "quantity");
        ssp4cpp::common::xml::parse_xml(node, obj.unit              , "unit");
        ssp4cpp::common::xml::parse_xml(node, obj.displayUnit       , "displayUnit");
        ssp4cpp::common::xml::parse_xml(node, obj.relativeQuantity  , "relativeQuantity");
        ssp4cpp::common::xml::parse_xml(node, obj.min               , "min");
        ssp4cpp::common::xml::parse_xml(node, obj.max               , "max");
        ssp4cpp::common::xml::parse_xml(node, obj.nominal           , "nominal");
        ssp4cpp::common::xml::parse_xml(node, obj.unbounded         , "unbounded");
        ssp4cpp::common::xml::parse_xml(node, obj.start             , "start");
        ssp4cpp::common::xml::parse_xml(node, obj.derivative        , "derivative");
        ssp4cpp::common::xml::parse_xml(node, obj.reinit            , "reinit");

        log.ext_trace("Completed Real");
    }


    void from_xml(const xml_node &node, Enumeration &obj)
    {
        log.ext_trace("Parsing Enumeration");

        ssp4cpp::common::xml::parse_xml(node, obj.declaredType  , "declaredType");
        ssp4cpp::common::xml::parse_xml(node, obj.quantity      , "quantity");
        ssp4cpp::common::xml::parse_xml(node, obj.min           , "min");
        ssp4cpp::common::xml::parse_xml(node, obj.max           , "max");
        ssp4cpp::common::xml::parse_xml(node, obj.start         , "start");

        log.ext_trace("Completed Enumeration");
    }


    void from_xml(const xml_node &node, SimpleTypeEnumerationItem &obj)
    {
        log.ext_trace("Parsing SimpleTypeEnumerationItem");

        ssp4cpp::common::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.value        , "value");
        ssp4cpp::common::xml::parse_xml(node, obj.description  , "description");

        log.ext_trace("Completed SimpleTypeEnumerationItem");
    }


    void from_xml(const xml_node &node, SimpleTypeEnumeration &obj)
    {
        log.ext_trace("Parsing SimpleTypeEnumeration");

        ssp4cpp::common::xml::parse_xml(node, obj.quantity  , "quantity");
        ssp4cpp::common::xml::parse_xml(node, obj.Items     , "Item");

        log.ext_trace("Completed SimpleTypeEnumeration");
    }


    void from_xml(const xml_node &node, fmi2SimpleType &obj)
    {
        log.ext_trace("Parsing fmi2SimpleType");

        ssp4cpp::common::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.description  , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.Real         , "Real");
        ssp4cpp::common::xml::parse_xml(node, obj.Integer      , "Integer");
        ssp4cpp::common::xml::parse_xml(node, obj.Boolean      , "Boolean");
        ssp4cpp::common::xml::parse_xml(node, obj.String       , "String");
        ssp4cpp::common::xml::parse_xml(node, obj.Enumeration  , "Enumeration");

        log.ext_trace("Completed fmi2SimpleType");
    }


    void from_xml(const xml_node &node, TypeDefinitions &obj)
    {
        log.ext_trace("Parsing TypeDefinitions");

        ssp4cpp::common::xml::parse_xml(node, obj.SimpleTypes  , "SimpleType");

        log.ext_trace("Completed TypeDefinitions");
    }


    void from_xml(const xml_node &node, Category &obj)
    {
        log.ext_trace("Parsing Category");

        ssp4cpp::common::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.description  , "description");

        log.ext_trace("Completed Category");
    }


    void from_xml(const xml_node &node, LogCategories &obj)
    {
        log.ext_trace("Parsing LogCategories");

        ssp4cpp::common::xml::parse_xml(node, obj.Categories  , "Category");

        log.ext_trace("Completed LogCategories");
    }


    void from_xml(const xml_node &node, fmi2Annotation &obj)
    {
        log.ext_trace("Parsing fmi2Annotation");

        ssp4cpp::common::xml::parse_xml(node, obj.annotation  , "annotation");

        log.ext_trace("Completed fmi2Annotation");
    }


    void from_xml(const xml_node &node, VendorAnnotations &obj)
    {
        log.ext_trace("Parsing VendorAnnotations");

        ssp4cpp::common::xml::parse_xml(node, obj.Annotations  , "Annotation");

        log.ext_trace("Completed VendorAnnotations");
    }


    void from_xml(const xml_node &node, DefaultExperiment &obj)
    {
        log.ext_trace("Parsing DefaultExperiment");

        ssp4cpp::common::xml::parse_xml(node, obj.startTime  , "startTime");
        ssp4cpp::common::xml::parse_xml(node, obj.stopTime   , "stopTime");
        ssp4cpp::common::xml::parse_xml(node, obj.tolerance  , "tolerance");
        ssp4cpp::common::xml::parse_xml(node, obj.stepSize   , "stepSize");

        log.ext_trace("Completed DefaultExperiment");
    }


    void from_xml(const xml_node &node, fmi2ScalarVariable &obj)
    {
        log.ext_trace("Parsing fmi2ScalarVariable");

        ssp4cpp::common::xml::parse_xml(node, obj.name                                , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.valueReference                      , "valueReference");
        ssp4cpp::common::xml::parse_xml(node, obj.description                         , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.causality                           , "causality");
        ssp4cpp::common::xml::parse_xml(node, obj.variability                         , "variability");
        ssp4cpp::common::xml::parse_xml(node, obj.initial                             , "initial");
        ssp4cpp::common::xml::parse_xml(node, obj.canHandleMultipleSetPerTimeInstant  , "canHandleMultipleSetPerTimeInstant");
        ssp4cpp::common::xml::parse_xml(node, obj.Real                                , "Real");
        ssp4cpp::common::xml::parse_xml(node, obj.Integer                             , "Integer");
        ssp4cpp::common::xml::parse_xml(node, obj.Boolean                             , "Boolean");
        ssp4cpp::common::xml::parse_xml(node, obj.String                              , "String");
        ssp4cpp::common::xml::parse_xml(node, obj.Enumeration                         , "Enumeration");
        ssp4cpp::common::xml::parse_xml(node, obj.Annotations                         , "Annotation");

        log.ext_trace("Completed fmi2ScalarVariable");
    }


    void from_xml(const xml_node &node, Unknown &obj)
    {
        log.ext_trace("Parsing Unknown");

        ssp4cpp::common::xml::parse_xml(node, obj.index             , "index");
        ssp4cpp::common::xml::parse_xml(node, obj.dependencies      , "dependencies");
        ssp4cpp::common::xml::parse_xml(node, obj.dependenciesKind  , "dependenciesKind");

        log.ext_trace("Completed Unknown");
    }


    void from_xml(const xml_node &node, Outputs &obj)
    {
        log.ext_trace("Parsing Outputs");

        ssp4cpp::common::xml::parse_xml(node, obj.Unknowns  , "Unknown");

        log.ext_trace("Completed Outputs");
    }


    void from_xml(const xml_node &node, Derivatives &obj)
    {
        log.ext_trace("Parsing Derivatives");

        ssp4cpp::common::xml::parse_xml(node, obj.Unknowns  , "Unknown");

        log.ext_trace("Completed Derivatives");
    }


    void from_xml(const xml_node &node, InitialUnknowns &obj)
    {
        log.ext_trace("Parsing InitialUnknowns");

        ssp4cpp::common::xml::parse_xml(node, obj.Unknowns  , "Unknown");

        log.ext_trace("Completed InitialUnknowns");
    }


    void from_xml(const xml_node &node, ModelStructure &obj)
    {
        log.ext_trace("Parsing ModelStructure");

        ssp4cpp::common::xml::parse_xml(node, obj.Outputs          , "Outputs");
        ssp4cpp::common::xml::parse_xml(node, obj.Derivatives      , "Derivatives");
        ssp4cpp::common::xml::parse_xml(node, obj.InitialUnknowns  , "InitialUnknowns");

        log.ext_trace("Completed ModelStructure");
    }


    void from_xml(const xml_node &node, ModelVariables &obj)
    {
        log.ext_trace("Parsing ModelVariables");

        ssp4cpp::common::xml::parse_xml(node, obj.ScalarVariable  , "ScalarVariable");

        log.ext_trace("Completed ModelVariables");
    }


    void from_xml(const xml_node &node, File &obj)
    {
        log.ext_trace("Parsing File");

        ssp4cpp::common::xml::parse_xml(node, obj.name  , "name");

        log.ext_trace("Completed File");
    }


    void from_xml(const xml_node &node, SourceFiles &obj)
    {
        log.ext_trace("Parsing SourceFiles");

        ssp4cpp::common::xml::parse_xml(node, obj.Files  , "File");

        log.ext_trace("Completed SourceFiles");
    }


    void from_xml(const xml_node &node, ModelExchange &obj)
    {
        log.ext_trace("Parsing ModelExchange");

        ssp4cpp::common::xml::parse_xml(node, obj.modelIdentifier                      , "modelIdentifier");
        ssp4cpp::common::xml::parse_xml(node, obj.needsExecutionTool                   , "needsExecutionTool");
        ssp4cpp::common::xml::parse_xml(node, obj.completedIntegratorStepNotNeeded     , "completedIntegratorStepNotNeeded");
        ssp4cpp::common::xml::parse_xml(node, obj.canBeInstantiatedOnlyOncePerProcess  , "canBeInstantiatedOnlyOncePerProcess");
        ssp4cpp::common::xml::parse_xml(node, obj.canNotUseMemoryManagementFunctions   , "canNotUseMemoryManagementFunctions");
        ssp4cpp::common::xml::parse_xml(node, obj.canGetAndSetFMUstate                 , "canGetAndSetFMUstate");
        ssp4cpp::common::xml::parse_xml(node, obj.canSerializeFMUstate                 , "canSerializeFMUstate");
        ssp4cpp::common::xml::parse_xml(node, obj.providesDirectionalDerivatives       , "providesDirectionalDerivatives");
        ssp4cpp::common::xml::parse_xml(node, obj.SourceFiles                          , "SourceFiles");

        log.ext_trace("Completed ModelExchange");
    }


    void from_xml(const xml_node &node, CoSimulation &obj)
    {
        log.ext_trace("Parsing CoSimulation");

        ssp4cpp::common::xml::parse_xml(node, obj.modelIdentifier                         , "modelIdentifier");
        ssp4cpp::common::xml::parse_xml(node, obj.needsExecutionTool                      , "needsExecutionTool");
        ssp4cpp::common::xml::parse_xml(node, obj.canHandleVariableCommunicationStepSize  , "canHandleVariableCommunicationStepSize");
        ssp4cpp::common::xml::parse_xml(node, obj.canInterpolateInputs                    , "canInterpolateInputs");
        ssp4cpp::common::xml::parse_xml(node, obj.maxOutputDerivativeOrder                , "maxOutputDerivativeOrder");
        ssp4cpp::common::xml::parse_xml(node, obj.canRunAsynchronuously                   , "canRunAsynchronuously");
        ssp4cpp::common::xml::parse_xml(node, obj.canBeInstantiatedOnlyOncePerProcess     , "canBeInstantiatedOnlyOncePerProcess");
        ssp4cpp::common::xml::parse_xml(node, obj.canNotUseMemoryManagementFunctions      , "canNotUseMemoryManagementFunctions");
        ssp4cpp::common::xml::parse_xml(node, obj.canGetAndSetFMUstate                    , "canGetAndSetFMUstate");
        ssp4cpp::common::xml::parse_xml(node, obj.canSerializeFMUstate                    , "canSerializeFMUstate");
        ssp4cpp::common::xml::parse_xml(node, obj.providesDirectionalDerivatives          , "providesDirectionalDerivatives");
        ssp4cpp::common::xml::parse_xml(node, obj.SourceFiles                             , "SourceFiles");

        log.ext_trace("Completed CoSimulation");
    }


    void from_xml(const xml_node &node, fmi2ModelDescription &obj)
    {
        log.ext_trace("Parsing fmi2ModelDescription");

        ssp4cpp::common::xml::parse_xml(node, obj.fmiVersion                , "fmiVersion");
        ssp4cpp::common::xml::parse_xml(node, obj.modelName                 , "modelName");
        ssp4cpp::common::xml::parse_xml(node, obj.guid                      , "guid");
        ssp4cpp::common::xml::parse_xml(node, obj.description               , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.author                    , "author");
        ssp4cpp::common::xml::parse_xml(node, obj.version                   , "version");
        ssp4cpp::common::xml::parse_xml(node, obj.copyright                 , "copyright");
        ssp4cpp::common::xml::parse_xml(node, obj.license                   , "license");
        ssp4cpp::common::xml::parse_xml(node, obj.generationTool            , "generationTool");
        ssp4cpp::common::xml::parse_xml(node, obj.generationDateAndTime     , "generationDateAndTime");
        ssp4cpp::common::xml::parse_xml(node, obj.variableNamingConvention  , "variableNamingConvention");
        ssp4cpp::common::xml::parse_xml(node, obj.numberOfEventIndicators   , "numberOfEventIndicators");
        ssp4cpp::common::xml::parse_xml(node, obj.ModelExchange             , "ModelExchange");
        ssp4cpp::common::xml::parse_xml(node, obj.CoSimulation              , "CoSimulation");
        ssp4cpp::common::xml::parse_xml(node, obj.UnitDefinitions           , "UnitDefinitions");
        ssp4cpp::common::xml::parse_xml(node, obj.TypeDefinitions           , "TypeDefinitions");
        ssp4cpp::common::xml::parse_xml(node, obj.LogCategories             , "LogCategories");
        ssp4cpp::common::xml::parse_xml(node, obj.DefaultExperiment         , "DefaultExperiment");
        ssp4cpp::common::xml::parse_xml(node, obj.VendorAnnotations         , "VendorAnnotations");
        ssp4cpp::common::xml::parse_xml(node, obj.ModelVariables            , "ModelVariables");
        ssp4cpp::common::xml::parse_xml(node, obj.ModelStructure            , "ModelStructure");

        log.ext_trace("Completed fmi2ModelDescription");
    }

}
