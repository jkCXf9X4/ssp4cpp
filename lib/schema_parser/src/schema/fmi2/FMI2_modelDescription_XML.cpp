

// This is a generated file, do not alter
// it is based on fmi2_md.toml

#include "FMI2_modelDescription_XML.hpp"


#include "xml_deserialize.hpp"

#include "common_log.hpp"

namespace ssp4cpp::fmi2::md
{
    using namespace pugi;
    using namespace common;


    void from_xml(const xml_node &node, BaseUnit &obj)
    {
        Logger::trace("Parsing BaseUnit");

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

        Logger::trace("Completed BaseUnit");
    }


    void from_xml(const xml_node &node, DisplayUnit &obj)
    {
        Logger::trace("Parsing DisplayUnit");

        ssp4cpp::common::xml::parse_xml(node, obj.name    , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.factor  , "factor");
        ssp4cpp::common::xml::parse_xml(node, obj.offset  , "offset");

        Logger::trace("Completed DisplayUnit");
    }


    void from_xml(const xml_node &node, fmi2Unit &obj)
    {
        Logger::trace("Parsing fmi2Unit");

        ssp4cpp::common::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.BaseUnit     , "BaseUnit");
        ssp4cpp::common::xml::parse_xml(node, obj.DisplayUnit  , "DisplayUnit");

        Logger::trace("Completed fmi2Unit");
    }


    void from_xml(const xml_node &node, UnitDefinitions &obj)
    {
        Logger::trace("Parsing UnitDefinitions");

        ssp4cpp::common::xml::parse_xml(node, obj.Units  , "Unit");

        Logger::trace("Completed UnitDefinitions");
    }


    void from_xml(const xml_node &node, Boolean &obj)
    {
        Logger::trace("Parsing Boolean");

        ssp4cpp::common::xml::parse_xml(node, obj.declaredType  , "declaredType");
        ssp4cpp::common::xml::parse_xml(node, obj.start         , "start");

        Logger::trace("Completed Boolean");
    }


    void from_xml(const xml_node &node, Integer &obj)
    {
        Logger::trace("Parsing Integer");

        ssp4cpp::common::xml::parse_xml(node, obj.declaredType  , "declaredType");
        ssp4cpp::common::xml::parse_xml(node, obj.start         , "start");
        ssp4cpp::common::xml::parse_xml(node, obj.quantity      , "quantity");
        ssp4cpp::common::xml::parse_xml(node, obj.min           , "min");
        ssp4cpp::common::xml::parse_xml(node, obj.max           , "max");

        Logger::trace("Completed Integer");
    }


    void from_xml(const xml_node &node, String &obj)
    {
        Logger::trace("Parsing String");

        ssp4cpp::common::xml::parse_xml(node, obj.declaredType  , "declaredType");
        ssp4cpp::common::xml::parse_xml(node, obj.start         , "start");

        Logger::trace("Completed String");
    }


    void from_xml(const xml_node &node, Real &obj)
    {
        Logger::trace("Parsing Real");

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

        Logger::trace("Completed Real");
    }


    void from_xml(const xml_node &node, Enumeration &obj)
    {
        Logger::trace("Parsing Enumeration");

        ssp4cpp::common::xml::parse_xml(node, obj.declaredType  , "declaredType");
        ssp4cpp::common::xml::parse_xml(node, obj.quantity      , "quantity");
        ssp4cpp::common::xml::parse_xml(node, obj.min           , "min");
        ssp4cpp::common::xml::parse_xml(node, obj.max           , "max");
        ssp4cpp::common::xml::parse_xml(node, obj.start         , "start");

        Logger::trace("Completed Enumeration");
    }


    void from_xml(const xml_node &node, SimpleTypeEnumerationItem &obj)
    {
        Logger::trace("Parsing SimpleTypeEnumerationItem");

        ssp4cpp::common::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.value        , "value");
        ssp4cpp::common::xml::parse_xml(node, obj.description  , "description");

        Logger::trace("Completed SimpleTypeEnumerationItem");
    }


    void from_xml(const xml_node &node, SimpleTypeEnumeration &obj)
    {
        Logger::trace("Parsing SimpleTypeEnumeration");

        ssp4cpp::common::xml::parse_xml(node, obj.quantity  , "quantity");
        ssp4cpp::common::xml::parse_xml(node, obj.Items     , "Item");

        Logger::trace("Completed SimpleTypeEnumeration");
    }


    void from_xml(const xml_node &node, fmi2SimpleType &obj)
    {
        Logger::trace("Parsing fmi2SimpleType");

        ssp4cpp::common::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.description  , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.Real         , "Real");
        ssp4cpp::common::xml::parse_xml(node, obj.Integer      , "Integer");
        ssp4cpp::common::xml::parse_xml(node, obj.Boolean      , "Boolean");
        ssp4cpp::common::xml::parse_xml(node, obj.String       , "String");
        ssp4cpp::common::xml::parse_xml(node, obj.Enumeration  , "Enumeration");

        Logger::trace("Completed fmi2SimpleType");
    }


    void from_xml(const xml_node &node, TypeDefinitions &obj)
    {
        Logger::trace("Parsing TypeDefinitions");

        ssp4cpp::common::xml::parse_xml(node, obj.SimpleTypes  , "SimpleType");

        Logger::trace("Completed TypeDefinitions");
    }


    void from_xml(const xml_node &node, Category &obj)
    {
        Logger::trace("Parsing Category");

        ssp4cpp::common::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.description  , "description");

        Logger::trace("Completed Category");
    }


    void from_xml(const xml_node &node, LogCategories &obj)
    {
        Logger::trace("Parsing LogCategories");

        ssp4cpp::common::xml::parse_xml(node, obj.Categories  , "Category");

        Logger::trace("Completed LogCategories");
    }


    void from_xml(const xml_node &node, fmi2Annotation &obj)
    {
        Logger::trace("Parsing fmi2Annotation");

        ssp4cpp::common::xml::parse_xml(node, obj.annotation  , "annotation");

        Logger::trace("Completed fmi2Annotation");
    }


    void from_xml(const xml_node &node, VendorAnnotations &obj)
    {
        Logger::trace("Parsing VendorAnnotations");

        ssp4cpp::common::xml::parse_xml(node, obj.Annotations  , "Annotation");

        Logger::trace("Completed VendorAnnotations");
    }


    void from_xml(const xml_node &node, DefaultExperiment &obj)
    {
        Logger::trace("Parsing DefaultExperiment");

        ssp4cpp::common::xml::parse_xml(node, obj.startTime  , "startTime");
        ssp4cpp::common::xml::parse_xml(node, obj.stopTime   , "stopTime");
        ssp4cpp::common::xml::parse_xml(node, obj.tolerance  , "tolerance");
        ssp4cpp::common::xml::parse_xml(node, obj.stepSize   , "stepSize");

        Logger::trace("Completed DefaultExperiment");
    }


    void from_xml(const xml_node &node, fmi2ScalarVariable &obj)
    {
        Logger::trace("Parsing fmi2ScalarVariable");

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

        Logger::trace("Completed fmi2ScalarVariable");
    }


    void from_xml(const xml_node &node, Unknown &obj)
    {
        Logger::trace("Parsing Unknown");

        ssp4cpp::common::xml::parse_xml(node, obj.index             , "index");
        ssp4cpp::common::xml::parse_xml(node, obj.dependencies      , "dependencies");
        ssp4cpp::common::xml::parse_xml(node, obj.dependenciesKind  , "dependenciesKind");

        Logger::trace("Completed Unknown");
    }


    void from_xml(const xml_node &node, Outputs &obj)
    {
        Logger::trace("Parsing Outputs");

        ssp4cpp::common::xml::parse_xml(node, obj.Unknowns  , "Unknown");

        Logger::trace("Completed Outputs");
    }


    void from_xml(const xml_node &node, Derivatives &obj)
    {
        Logger::trace("Parsing Derivatives");

        ssp4cpp::common::xml::parse_xml(node, obj.Unknowns  , "Unknown");

        Logger::trace("Completed Derivatives");
    }


    void from_xml(const xml_node &node, InitialUnknowns &obj)
    {
        Logger::trace("Parsing InitialUnknowns");

        ssp4cpp::common::xml::parse_xml(node, obj.Unknowns  , "Unknown");

        Logger::trace("Completed InitialUnknowns");
    }


    void from_xml(const xml_node &node, ModelStructure &obj)
    {
        Logger::trace("Parsing ModelStructure");

        ssp4cpp::common::xml::parse_xml(node, obj.Outputs          , "Outputs");
        ssp4cpp::common::xml::parse_xml(node, obj.Derivatives      , "Derivatives");
        ssp4cpp::common::xml::parse_xml(node, obj.InitialUnknowns  , "InitialUnknowns");

        Logger::trace("Completed ModelStructure");
    }


    void from_xml(const xml_node &node, ModelVariables &obj)
    {
        Logger::trace("Parsing ModelVariables");

        ssp4cpp::common::xml::parse_xml(node, obj.ScalarVariable  , "ScalarVariable");

        Logger::trace("Completed ModelVariables");
    }


    void from_xml(const xml_node &node, File &obj)
    {
        Logger::trace("Parsing File");

        ssp4cpp::common::xml::parse_xml(node, obj.name  , "name");

        Logger::trace("Completed File");
    }


    void from_xml(const xml_node &node, SourceFiles &obj)
    {
        Logger::trace("Parsing SourceFiles");

        ssp4cpp::common::xml::parse_xml(node, obj.Files  , "File");

        Logger::trace("Completed SourceFiles");
    }


    void from_xml(const xml_node &node, ModelExchange &obj)
    {
        Logger::trace("Parsing ModelExchange");

        ssp4cpp::common::xml::parse_xml(node, obj.modelIdentifier                      , "modelIdentifier");
        ssp4cpp::common::xml::parse_xml(node, obj.needsExecutionTool                   , "needsExecutionTool");
        ssp4cpp::common::xml::parse_xml(node, obj.completedIntegratorStepNotNeeded     , "completedIntegratorStepNotNeeded");
        ssp4cpp::common::xml::parse_xml(node, obj.canBeInstantiatedOnlyOncePerProcess  , "canBeInstantiatedOnlyOncePerProcess");
        ssp4cpp::common::xml::parse_xml(node, obj.canNotUseMemoryManagementFunctions   , "canNotUseMemoryManagementFunctions");
        ssp4cpp::common::xml::parse_xml(node, obj.canGetAndSetFMUstate                 , "canGetAndSetFMUstate");
        ssp4cpp::common::xml::parse_xml(node, obj.canSerializeFMUstate                 , "canSerializeFMUstate");
        ssp4cpp::common::xml::parse_xml(node, obj.providesDirectionalDerivatives       , "providesDirectionalDerivatives");
        ssp4cpp::common::xml::parse_xml(node, obj.SourceFiles                          , "SourceFiles");

        Logger::trace("Completed ModelExchange");
    }


    void from_xml(const xml_node &node, CoSimulation &obj)
    {
        Logger::trace("Parsing CoSimulation");

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

        Logger::trace("Completed CoSimulation");
    }


    void from_xml(const xml_node &node, fmi2ModelDescription &obj)
    {
        Logger::trace("Parsing fmi2ModelDescription");

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

        Logger::trace("Completed fmi2ModelDescription");
    }

}
