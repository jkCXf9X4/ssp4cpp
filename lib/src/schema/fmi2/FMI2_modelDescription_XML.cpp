

// This is a generated file, do not alter
// it is based on fmi2_md.toml

#include "FMI2_modelDescription_XML.hpp"


#include "xml_deserialize.hpp"

#include "cutecpp/log.hpp"

namespace ssp4cpp::fmi2::md
{
    using namespace pugi;

    auto log = Logger("ssp4cpp.fmi2.md", LogLevel::info);


    void from_xml(const xml_node &node, BaseUnit &obj)
    {
        log(ext_trace)("Parsing BaseUnit");
        

        utils::xml::parse_xml(node, obj.kg      , "kg");
        utils::xml::parse_xml(node, obj.m       , "m");
        utils::xml::parse_xml(node, obj.s       , "s");
        utils::xml::parse_xml(node, obj.a       , "a");
        utils::xml::parse_xml(node, obj.k       , "k");
        utils::xml::parse_xml(node, obj.mol     , "mol");
        utils::xml::parse_xml(node, obj.cd      , "cd");
        utils::xml::parse_xml(node, obj.rad     , "rad");
        utils::xml::parse_xml(node, obj.factor  , "factor");
        utils::xml::parse_xml(node, obj.offset  , "offset");

        log(ext_trace)("Completed BaseUnit");
    }


    void from_xml(const xml_node &node, DisplayUnit &obj)
    {
        log(ext_trace)("Parsing DisplayUnit");
        

        utils::xml::parse_xml(node, obj.name    , "name");
        utils::xml::parse_xml(node, obj.factor  , "factor");
        utils::xml::parse_xml(node, obj.offset  , "offset");

        log(ext_trace)("Completed DisplayUnit");
    }


    void from_xml(const xml_node &node, fmi2Unit &obj)
    {
        log(ext_trace)("Parsing fmi2Unit");
        

        utils::xml::parse_xml(node, obj.name         , "name");
        utils::xml::parse_xml(node, obj.BaseUnit     , "BaseUnit");
        utils::xml::parse_xml(node, obj.DisplayUnit  , "DisplayUnit");

        log(ext_trace)("Completed fmi2Unit");
    }


    void from_xml(const xml_node &node, UnitDefinitions &obj)
    {
        log(ext_trace)("Parsing UnitDefinitions");
        

        utils::xml::parse_xml(node, obj.Units  , "Unit");

        log(ext_trace)("Completed UnitDefinitions");
    }


    void from_xml(const xml_node &node, Boolean &obj)
    {
        log(ext_trace)("Parsing Boolean");
        

        utils::xml::parse_xml(node, obj.declaredType  , "declaredType");
        utils::xml::parse_xml(node, obj.start         , "start");

        log(ext_trace)("Completed Boolean");
    }


    void from_xml(const xml_node &node, Integer &obj)
    {
        log(ext_trace)("Parsing Integer");
        

        utils::xml::parse_xml(node, obj.declaredType  , "declaredType");
        utils::xml::parse_xml(node, obj.start         , "start");
        utils::xml::parse_xml(node, obj.quantity      , "quantity");
        utils::xml::parse_xml(node, obj.min           , "min");
        utils::xml::parse_xml(node, obj.max           , "max");

        log(ext_trace)("Completed Integer");
    }


    void from_xml(const xml_node &node, String &obj)
    {
        log(ext_trace)("Parsing String");
        

        utils::xml::parse_xml(node, obj.declaredType  , "declaredType");
        utils::xml::parse_xml(node, obj.start         , "start");

        log(ext_trace)("Completed String");
    }


    void from_xml(const xml_node &node, Real &obj)
    {
        log(ext_trace)("Parsing Real");
        

        utils::xml::parse_xml(node, obj.declaredType      , "declaredType");
        utils::xml::parse_xml(node, obj.quantity          , "quantity");
        utils::xml::parse_xml(node, obj.unit              , "unit");
        utils::xml::parse_xml(node, obj.displayUnit       , "displayUnit");
        utils::xml::parse_xml(node, obj.relativeQuantity  , "relativeQuantity");
        utils::xml::parse_xml(node, obj.min               , "min");
        utils::xml::parse_xml(node, obj.max               , "max");
        utils::xml::parse_xml(node, obj.nominal           , "nominal");
        utils::xml::parse_xml(node, obj.unbounded         , "unbounded");
        utils::xml::parse_xml(node, obj.start             , "start");
        utils::xml::parse_xml(node, obj.derivative        , "derivative");
        utils::xml::parse_xml(node, obj.reinit            , "reinit");

        log(ext_trace)("Completed Real");
    }


    void from_xml(const xml_node &node, Enumeration &obj)
    {
        log(ext_trace)("Parsing Enumeration");
        

        utils::xml::parse_xml(node, obj.declaredType  , "declaredType");
        utils::xml::parse_xml(node, obj.quantity      , "quantity");
        utils::xml::parse_xml(node, obj.min           , "min");
        utils::xml::parse_xml(node, obj.max           , "max");
        utils::xml::parse_xml(node, obj.start         , "start");

        log(ext_trace)("Completed Enumeration");
    }


    void from_xml(const xml_node &node, SimpleTypeEnumerationItem &obj)
    {
        log(ext_trace)("Parsing SimpleTypeEnumerationItem");
        

        utils::xml::parse_xml(node, obj.name         , "name");
        utils::xml::parse_xml(node, obj.value        , "value");
        utils::xml::parse_xml(node, obj.description  , "description");

        log(ext_trace)("Completed SimpleTypeEnumerationItem");
    }


    void from_xml(const xml_node &node, SimpleTypeEnumeration &obj)
    {
        log(ext_trace)("Parsing SimpleTypeEnumeration");
        

        utils::xml::parse_xml(node, obj.quantity  , "quantity");
        utils::xml::parse_xml(node, obj.Items     , "Item");

        log(ext_trace)("Completed SimpleTypeEnumeration");
    }


    void from_xml(const xml_node &node, fmi2SimpleType &obj)
    {
        log(ext_trace)("Parsing fmi2SimpleType");
        

        utils::xml::parse_xml(node, obj.name         , "name");
        utils::xml::parse_xml(node, obj.description  , "description");
        utils::xml::parse_xml(node, obj.Real         , "Real");
        utils::xml::parse_xml(node, obj.Integer      , "Integer");
        utils::xml::parse_xml(node, obj.Boolean      , "Boolean");
        utils::xml::parse_xml(node, obj.String       , "String");
        utils::xml::parse_xml(node, obj.Enumeration  , "Enumeration");

        log(ext_trace)("Completed fmi2SimpleType");
    }


    void from_xml(const xml_node &node, TypeDefinitions &obj)
    {
        log(ext_trace)("Parsing TypeDefinitions");
        

        utils::xml::parse_xml(node, obj.SimpleTypes  , "SimpleType");

        log(ext_trace)("Completed TypeDefinitions");
    }


    void from_xml(const xml_node &node, Category &obj)
    {
        log(ext_trace)("Parsing Category");
        

        utils::xml::parse_xml(node, obj.name         , "name");
        utils::xml::parse_xml(node, obj.description  , "description");

        log(ext_trace)("Completed Category");
    }


    void from_xml(const xml_node &node, LogCategories &obj)
    {
        log(ext_trace)("Parsing LogCategories");
        

        utils::xml::parse_xml(node, obj.Categories  , "Category");

        log(ext_trace)("Completed LogCategories");
    }


    void from_xml(const xml_node &node, fmi2Annotation &obj)
    {
        log(ext_trace)("Parsing fmi2Annotation");
        

        utils::xml::parse_xml(node, obj.annotation  , "annotation");

        log(ext_trace)("Completed fmi2Annotation");
    }


    void from_xml(const xml_node &node, VendorAnnotations &obj)
    {
        log(ext_trace)("Parsing VendorAnnotations");
        

        utils::xml::parse_xml(node, obj.Annotations  , "Annotation");

        log(ext_trace)("Completed VendorAnnotations");
    }


    void from_xml(const xml_node &node, DefaultExperiment &obj)
    {
        log(ext_trace)("Parsing DefaultExperiment");
        

        utils::xml::parse_xml(node, obj.startTime  , "startTime");
        utils::xml::parse_xml(node, obj.stopTime   , "stopTime");
        utils::xml::parse_xml(node, obj.tolerance  , "tolerance");
        utils::xml::parse_xml(node, obj.stepSize   , "stepSize");

        log(ext_trace)("Completed DefaultExperiment");
    }


    void from_xml(const xml_node &node, fmi2ScalarVariable &obj)
    {
        log(ext_trace)("Parsing fmi2ScalarVariable");
        

        utils::xml::parse_xml(node, obj.name                                , "name");
        utils::xml::parse_xml(node, obj.valueReference                      , "valueReference");
        utils::xml::parse_xml(node, obj.description                         , "description");
        utils::xml::parse_xml(node, obj.causality                           , "causality");
        utils::xml::parse_xml(node, obj.variability                         , "variability");
        utils::xml::parse_xml(node, obj.initial                             , "initial");
        utils::xml::parse_xml(node, obj.canHandleMultipleSetPerTimeInstant  , "canHandleMultipleSetPerTimeInstant");
        utils::xml::parse_xml(node, obj.Real                                , "Real");
        utils::xml::parse_xml(node, obj.Integer                             , "Integer");
        utils::xml::parse_xml(node, obj.Boolean                             , "Boolean");
        utils::xml::parse_xml(node, obj.String                              , "String");
        utils::xml::parse_xml(node, obj.Enumeration                         , "Enumeration");
        utils::xml::parse_xml(node, obj.Annotations                         , "Annotation");

        log(ext_trace)("Completed fmi2ScalarVariable");
    }


    void from_xml(const xml_node &node, Unknown &obj)
    {
        log(ext_trace)("Parsing Unknown");
        

        utils::xml::parse_xml(node, obj.index             , "index");
        utils::xml::parse_xml(node, obj.dependencies      , "dependencies");
        utils::xml::parse_xml(node, obj.dependenciesKind  , "dependenciesKind");

        log(ext_trace)("Completed Unknown");
    }


    void from_xml(const xml_node &node, Outputs &obj)
    {
        log(ext_trace)("Parsing Outputs");
        

        utils::xml::parse_xml(node, obj.Unknowns  , "Unknown");

        log(ext_trace)("Completed Outputs");
    }


    void from_xml(const xml_node &node, Derivatives &obj)
    {
        log(ext_trace)("Parsing Derivatives");
        

        utils::xml::parse_xml(node, obj.Unknowns  , "Unknown");

        log(ext_trace)("Completed Derivatives");
    }


    void from_xml(const xml_node &node, InitialUnknowns &obj)
    {
        log(ext_trace)("Parsing InitialUnknowns");
        

        utils::xml::parse_xml(node, obj.Unknowns  , "Unknown");

        log(ext_trace)("Completed InitialUnknowns");
    }


    void from_xml(const xml_node &node, ModelStructure &obj)
    {
        log(ext_trace)("Parsing ModelStructure");
        

        utils::xml::parse_xml(node, obj.Outputs          , "Outputs");
        utils::xml::parse_xml(node, obj.Derivatives      , "Derivatives");
        utils::xml::parse_xml(node, obj.InitialUnknowns  , "InitialUnknowns");

        log(ext_trace)("Completed ModelStructure");
    }


    void from_xml(const xml_node &node, ModelVariables &obj)
    {
        log(ext_trace)("Parsing ModelVariables");
        

        utils::xml::parse_xml(node, obj.ScalarVariable  , "ScalarVariable");

        log(ext_trace)("Completed ModelVariables");
    }


    void from_xml(const xml_node &node, File &obj)
    {
        log(ext_trace)("Parsing File");
        

        utils::xml::parse_xml(node, obj.name  , "name");

        log(ext_trace)("Completed File");
    }


    void from_xml(const xml_node &node, SourceFiles &obj)
    {
        log(ext_trace)("Parsing SourceFiles");
        

        utils::xml::parse_xml(node, obj.Files  , "File");

        log(ext_trace)("Completed SourceFiles");
    }


    void from_xml(const xml_node &node, ModelExchange &obj)
    {
        log(ext_trace)("Parsing ModelExchange");
        

        utils::xml::parse_xml(node, obj.modelIdentifier                      , "modelIdentifier");
        utils::xml::parse_xml(node, obj.needsExecutionTool                   , "needsExecutionTool");
        utils::xml::parse_xml(node, obj.completedIntegratorStepNotNeeded     , "completedIntegratorStepNotNeeded");
        utils::xml::parse_xml(node, obj.canBeInstantiatedOnlyOncePerProcess  , "canBeInstantiatedOnlyOncePerProcess");
        utils::xml::parse_xml(node, obj.canNotUseMemoryManagementFunctions   , "canNotUseMemoryManagementFunctions");
        utils::xml::parse_xml(node, obj.canGetAndSetFMUstate                 , "canGetAndSetFMUstate");
        utils::xml::parse_xml(node, obj.canSerializeFMUstate                 , "canSerializeFMUstate");
        utils::xml::parse_xml(node, obj.providesDirectionalDerivatives       , "providesDirectionalDerivatives");
        utils::xml::parse_xml(node, obj.SourceFiles                          , "SourceFiles");

        log(ext_trace)("Completed ModelExchange");
    }


    void from_xml(const xml_node &node, CoSimulation &obj)
    {
        log(ext_trace)("Parsing CoSimulation");
        

        utils::xml::parse_xml(node, obj.modelIdentifier                         , "modelIdentifier");
        utils::xml::parse_xml(node, obj.needsExecutionTool                      , "needsExecutionTool");
        utils::xml::parse_xml(node, obj.canHandleVariableCommunicationStepSize  , "canHandleVariableCommunicationStepSize");
        utils::xml::parse_xml(node, obj.canInterpolateInputs                    , "canInterpolateInputs");
        utils::xml::parse_xml(node, obj.maxOutputDerivativeOrder                , "maxOutputDerivativeOrder");
        utils::xml::parse_xml(node, obj.canRunAsynchronuously                   , "canRunAsynchronuously");
        utils::xml::parse_xml(node, obj.canBeInstantiatedOnlyOncePerProcess     , "canBeInstantiatedOnlyOncePerProcess");
        utils::xml::parse_xml(node, obj.canNotUseMemoryManagementFunctions      , "canNotUseMemoryManagementFunctions");
        utils::xml::parse_xml(node, obj.canGetAndSetFMUstate                    , "canGetAndSetFMUstate");
        utils::xml::parse_xml(node, obj.canSerializeFMUstate                    , "canSerializeFMUstate");
        utils::xml::parse_xml(node, obj.providesDirectionalDerivatives          , "providesDirectionalDerivatives");
        utils::xml::parse_xml(node, obj.SourceFiles                             , "SourceFiles");

        log(ext_trace)("Completed CoSimulation");
    }


    void from_xml(const xml_node &node, fmi2ModelDescription &obj)
    {
        log(ext_trace)("Parsing fmi2ModelDescription");
        

        utils::xml::parse_xml(node, obj.fmiVersion                , "fmiVersion");
        utils::xml::parse_xml(node, obj.modelName                 , "modelName");
        utils::xml::parse_xml(node, obj.guid                      , "guid");
        utils::xml::parse_xml(node, obj.description               , "description");
        utils::xml::parse_xml(node, obj.author                    , "author");
        utils::xml::parse_xml(node, obj.version                   , "version");
        utils::xml::parse_xml(node, obj.copyright                 , "copyright");
        utils::xml::parse_xml(node, obj.license                   , "license");
        utils::xml::parse_xml(node, obj.generationTool            , "generationTool");
        utils::xml::parse_xml(node, obj.generationDateAndTime     , "generationDateAndTime");
        utils::xml::parse_xml(node, obj.variableNamingConvention  , "variableNamingConvention");
        utils::xml::parse_xml(node, obj.numberOfEventIndicators   , "numberOfEventIndicators");
        utils::xml::parse_xml(node, obj.ModelExchange             , "ModelExchange");
        utils::xml::parse_xml(node, obj.CoSimulation              , "CoSimulation");
        utils::xml::parse_xml(node, obj.UnitDefinitions           , "UnitDefinitions");
        utils::xml::parse_xml(node, obj.TypeDefinitions           , "TypeDefinitions");
        utils::xml::parse_xml(node, obj.LogCategories             , "LogCategories");
        utils::xml::parse_xml(node, obj.DefaultExperiment         , "DefaultExperiment");
        utils::xml::parse_xml(node, obj.VendorAnnotations         , "VendorAnnotations");
        utils::xml::parse_xml(node, obj.ModelVariables            , "ModelVariables");
        utils::xml::parse_xml(node, obj.ModelStructure            , "ModelStructure");

        log(ext_trace)("Completed fmi2ModelDescription");
    }

}
