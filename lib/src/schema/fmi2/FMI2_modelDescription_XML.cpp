

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

        utils::xml::get_optional_attribute(node, obj.kg      , "kg"); // int
        utils::xml::get_optional_attribute(node, obj.m       , "m"); // int
        utils::xml::get_optional_attribute(node, obj.s       , "s"); // int
        utils::xml::get_optional_attribute(node, obj.a       , "a"); // int
        utils::xml::get_optional_attribute(node, obj.k       , "k"); // int
        utils::xml::get_optional_attribute(node, obj.mol     , "mol"); // int
        utils::xml::get_optional_attribute(node, obj.cd      , "cd"); // int
        utils::xml::get_optional_attribute(node, obj.rad     , "rad"); // int
        utils::xml::get_optional_attribute(node, obj.factor  , "factor"); // double
        utils::xml::get_optional_attribute(node, obj.offset  , "offset"); // double

        log(ext_trace)("Completed BaseUnit");
    }


    void from_xml(const xml_node &node, DisplayUnit &obj)
    {
        log(ext_trace)("Parsing DisplayUnit");

        utils::xml::get_attribute(node, obj.name    , "name"); // string
        utils::xml::get_optional_attribute(node, obj.factor  , "factor"); // double
        utils::xml::get_optional_attribute(node, obj.offset  , "offset"); // double

        log(ext_trace)("Completed DisplayUnit");
    }


    void from_xml(const xml_node &node, fmi2Unit &obj)
    {
        log(ext_trace)("Parsing fmi2Unit");

        utils::xml::get_attribute(node, obj.name         , "name"); // string
        utils::xml::get_optional_class(node, obj.BaseUnit     , "BaseUnit"); // fmi2::md::BaseUnit
        utils::xml::get_vector(node, obj.DisplayUnit  , "DisplayUnit"); // fmi2::md::DisplayUnit

        log(ext_trace)("Completed fmi2Unit");
    }


    void from_xml(const xml_node &node, UnitDefinitions &obj)
    {
        log(ext_trace)("Parsing UnitDefinitions");

        utils::xml::get_vector(node, obj.Units  , "Unit"); // fmi2::md::fmi2Unit

        log(ext_trace)("Completed UnitDefinitions");
    }


    void from_xml(const xml_node &node, Boolean &obj)
    {
        log(ext_trace)("Parsing Boolean");

        utils::xml::get_optional_attribute(node, obj.declaredType  , "declaredType"); // string
        utils::xml::get_optional_attribute(node, obj.start         , "start"); // bool

        log(ext_trace)("Completed Boolean");
    }


    void from_xml(const xml_node &node, Integer &obj)
    {
        log(ext_trace)("Parsing Integer");

        utils::xml::get_optional_attribute(node, obj.declaredType  , "declaredType"); // string
        utils::xml::get_optional_attribute(node, obj.start         , "start"); // int
        utils::xml::get_optional_attribute(node, obj.quantity      , "quantity"); // string
        utils::xml::get_optional_attribute(node, obj.min           , "min"); // int
        utils::xml::get_optional_attribute(node, obj.max           , "max"); // int

        log(ext_trace)("Completed Integer");
    }


    void from_xml(const xml_node &node, String &obj)
    {
        log(ext_trace)("Parsing String");

        utils::xml::get_optional_attribute(node, obj.declaredType  , "declaredType"); // string
        utils::xml::get_optional_attribute(node, obj.start         , "start"); // string

        log(ext_trace)("Completed String");
    }


    void from_xml(const xml_node &node, Real &obj)
    {
        log(ext_trace)("Parsing Real");

        utils::xml::get_optional_attribute(node, obj.declaredType      , "declaredType"); // string
        utils::xml::get_optional_attribute(node, obj.quantity          , "quantity"); // string
        utils::xml::get_optional_attribute(node, obj.unit              , "unit"); // string
        utils::xml::get_optional_attribute(node, obj.displayUnit       , "displayUnit"); // string
        utils::xml::get_optional_attribute(node, obj.relativeQuantity  , "relativeQuantity"); // bool
        utils::xml::get_optional_attribute(node, obj.min               , "min"); // double
        utils::xml::get_optional_attribute(node, obj.max               , "max"); // double
        utils::xml::get_optional_attribute(node, obj.nominal           , "nominal"); // double
        utils::xml::get_optional_attribute(node, obj.unbounded         , "unbounded"); // bool
        utils::xml::get_optional_attribute(node, obj.start             , "start"); // double
        utils::xml::get_optional_attribute(node, obj.derivative        , "derivative"); // unsigned int
        utils::xml::get_optional_attribute(node, obj.reinit            , "reinit"); // bool

        log(ext_trace)("Completed Real");
    }


    void from_xml(const xml_node &node, Enumeration &obj)
    {
        log(ext_trace)("Parsing Enumeration");

        utils::xml::get_attribute(node, obj.declaredType  , "declaredType"); // string
        utils::xml::get_optional_attribute(node, obj.quantity      , "quantity"); // string
        utils::xml::get_optional_attribute(node, obj.min           , "min"); // int
        utils::xml::get_optional_attribute(node, obj.max           , "max"); // int
        utils::xml::get_optional_attribute(node, obj.start         , "start"); // int

        log(ext_trace)("Completed Enumeration");
    }


    void from_xml(const xml_node &node, SimpleTypeEnumerationItem &obj)
    {
        log(ext_trace)("Parsing SimpleTypeEnumerationItem");

        utils::xml::get_attribute(node, obj.name         , "name"); // string
        utils::xml::get_attribute(node, obj.value        , "value"); // int
        utils::xml::get_optional_attribute(node, obj.description  , "description"); // string

        log(ext_trace)("Completed SimpleTypeEnumerationItem");
    }


    void from_xml(const xml_node &node, SimpleTypeEnumeration &obj)
    {
        log(ext_trace)("Parsing SimpleTypeEnumeration");

        utils::xml::get_optional_attribute(node, obj.quantity  , "quantity"); // string
        utils::xml::get_vector(node, obj.Items     , "Item"); // fmi2::md::SimpleTypeEnumerationItem

        log(ext_trace)("Completed SimpleTypeEnumeration");
    }


    void from_xml(const xml_node &node, fmi2SimpleType &obj)
    {
        log(ext_trace)("Parsing fmi2SimpleType");

        utils::xml::get_attribute(node, obj.name         , "name"); // string
        utils::xml::get_optional_attribute(node, obj.description  , "description"); // string
        utils::xml::get_optional_class(node, obj.Real         , "Real"); // fmi2::md::Real
        utils::xml::get_optional_class(node, obj.Integer      , "Integer"); // fmi2::md::Integer
        utils::xml::get_optional_class(node, obj.Boolean      , "Boolean"); // fmi2::md::Boolean
        utils::xml::get_optional_class(node, obj.String       , "String"); // fmi2::md::String
        utils::xml::get_optional_class(node, obj.Enumeration  , "Enumeration"); // fmi2::md::SimpleTypeEnumeration

        log(ext_trace)("Completed fmi2SimpleType");
    }


    void from_xml(const xml_node &node, TypeDefinitions &obj)
    {
        log(ext_trace)("Parsing TypeDefinitions");

        utils::xml::get_vector(node, obj.SimpleTypes  , "SimpleType"); // fmi2::md::fmi2SimpleType

        log(ext_trace)("Completed TypeDefinitions");
    }


    void from_xml(const xml_node &node, Category &obj)
    {
        log(ext_trace)("Parsing Category");

        utils::xml::get_attribute(node, obj.name         , "name"); // string
        utils::xml::get_optional_attribute(node, obj.description  , "description"); // string

        log(ext_trace)("Completed Category");
    }


    void from_xml(const xml_node &node, LogCategories &obj)
    {
        log(ext_trace)("Parsing LogCategories");

        utils::xml::get_vector(node, obj.Categories  , "Category"); // fmi2::md::Category

        log(ext_trace)("Completed LogCategories");
    }


    void from_xml(const xml_node &node, fmi2Annotation &obj)
    {
        log(ext_trace)("Parsing fmi2Annotation");

        utils::xml::get_attribute(node, obj.annotation  , "annotation"); // string

        log(ext_trace)("Completed fmi2Annotation");
    }


    void from_xml(const xml_node &node, VendorAnnotations &obj)
    {
        log(ext_trace)("Parsing VendorAnnotations");

        utils::xml::get_vector(node, obj.Annotations  , "Annotation"); // fmi2::md::fmi2Annotation

        log(ext_trace)("Completed VendorAnnotations");
    }


    void from_xml(const xml_node &node, DefaultExperiment &obj)
    {
        log(ext_trace)("Parsing DefaultExperiment");

        utils::xml::get_optional_attribute(node, obj.startTime  , "startTime"); // double
        utils::xml::get_optional_attribute(node, obj.stopTime   , "stopTime"); // double
        utils::xml::get_optional_attribute(node, obj.tolerance  , "tolerance"); // double
        utils::xml::get_optional_attribute(node, obj.stepSize   , "stepSize"); // double

        log(ext_trace)("Completed DefaultExperiment");
    }


    void from_xml(const xml_node &node, fmi2ScalarVariable &obj)
    {
        log(ext_trace)("Parsing fmi2ScalarVariable");

        utils::xml::get_attribute(node, obj.name                                , "name"); // string
        utils::xml::get_optional_attribute(node, obj.valueReference                      , "valueReference"); // unsigned int
        utils::xml::get_optional_attribute(node, obj.description                         , "description"); // string
        utils::xml::get_optional_enum(node, obj.causality                           , "causality"); // fmi2::md::Causality
        utils::xml::get_optional_enum(node, obj.variability                         , "variability"); // fmi2::md::Variability
        utils::xml::get_optional_enum(node, obj.initial                             , "initial"); // fmi2::md::Initial
        utils::xml::get_optional_attribute(node, obj.canHandleMultipleSetPerTimeInstant  , "canHandleMultipleSetPerTimeInstant"); // bool
        utils::xml::get_optional_class(node, obj.Real                                , "Real"); // fmi2::md::Real
        utils::xml::get_optional_class(node, obj.Integer                             , "Integer"); // fmi2::md::Integer
        utils::xml::get_optional_class(node, obj.Boolean                             , "Boolean"); // fmi2::md::Boolean
        utils::xml::get_optional_class(node, obj.String                              , "String"); // fmi2::md::String
        utils::xml::get_optional_class(node, obj.Enumeration                         , "Enumeration"); // fmi2::md::Enumeration
        utils::xml::get_vector(node, obj.Annotations                         , "Annotation"); // fmi2::md::fmi2Annotation

        log(ext_trace)("Completed fmi2ScalarVariable");
    }


    void from_xml(const xml_node &node, Unknown &obj)
    {
        log(ext_trace)("Parsing Unknown");

        utils::xml::get_attribute(node, obj.index             , "index"); // int
        utils::xml::get_readable_vector(node, obj.dependencies      , "dependencies", " "); // int
        utils::xml::get_readable_vector(node, obj.dependenciesKind  , "dependenciesKind", " "); // fmi2::md::DependenciesKind

        log(ext_trace)("Completed Unknown");
    }


    void from_xml(const xml_node &node, Outputs &obj)
    {
        log(ext_trace)("Parsing Outputs");

        utils::xml::get_vector(node, obj.Unknowns  , "Unknown"); // fmi2::md::Unknown

        log(ext_trace)("Completed Outputs");
    }


    void from_xml(const xml_node &node, Derivatives &obj)
    {
        log(ext_trace)("Parsing Derivatives");

        utils::xml::get_vector(node, obj.Unknowns  , "Unknown"); // fmi2::md::Unknown

        log(ext_trace)("Completed Derivatives");
    }


    void from_xml(const xml_node &node, InitialUnknowns &obj)
    {
        log(ext_trace)("Parsing InitialUnknowns");

        utils::xml::get_vector(node, obj.Unknowns  , "Unknown"); // fmi2::md::Unknown

        log(ext_trace)("Completed InitialUnknowns");
    }


    void from_xml(const xml_node &node, ModelStructure &obj)
    {
        log(ext_trace)("Parsing ModelStructure");

        utils::xml::get_optional_class(node, obj.Outputs          , "Outputs"); // fmi2::md::Outputs
        utils::xml::get_optional_class(node, obj.Derivatives      , "Derivatives"); // fmi2::md::Derivatives
        utils::xml::get_optional_class(node, obj.InitialUnknowns  , "InitialUnknowns"); // fmi2::md::InitialUnknowns

        log(ext_trace)("Completed ModelStructure");
    }


    void from_xml(const xml_node &node, ModelVariables &obj)
    {
        log(ext_trace)("Parsing ModelVariables");

        utils::xml::get_vector(node, obj.ScalarVariable  , "ScalarVariable"); // fmi2::md::fmi2ScalarVariable

        log(ext_trace)("Completed ModelVariables");
    }


    void from_xml(const xml_node &node, File &obj)
    {
        log(ext_trace)("Parsing File");

        utils::xml::get_attribute(node, obj.name  , "name"); // string

        log(ext_trace)("Completed File");
    }


    void from_xml(const xml_node &node, SourceFiles &obj)
    {
        log(ext_trace)("Parsing SourceFiles");

        utils::xml::get_vector(node, obj.Files  , "File"); // fmi2::md::File

        log(ext_trace)("Completed SourceFiles");
    }


    void from_xml(const xml_node &node, ModelExchange &obj)
    {
        log(ext_trace)("Parsing ModelExchange");

        utils::xml::get_attribute(node, obj.modelIdentifier                      , "modelIdentifier"); // string
        utils::xml::get_optional_attribute(node, obj.needsExecutionTool                   , "needsExecutionTool"); // bool
        utils::xml::get_optional_attribute(node, obj.completedIntegratorStepNotNeeded     , "completedIntegratorStepNotNeeded"); // bool
        utils::xml::get_optional_attribute(node, obj.canBeInstantiatedOnlyOncePerProcess  , "canBeInstantiatedOnlyOncePerProcess"); // bool
        utils::xml::get_optional_attribute(node, obj.canNotUseMemoryManagementFunctions   , "canNotUseMemoryManagementFunctions"); // bool
        utils::xml::get_optional_attribute(node, obj.canGetAndSetFMUstate                 , "canGetAndSetFMUstate"); // bool
        utils::xml::get_optional_attribute(node, obj.canSerializeFMUstate                 , "canSerializeFMUstate"); // bool
        utils::xml::get_optional_attribute(node, obj.providesDirectionalDerivatives       , "providesDirectionalDerivatives"); // bool
        utils::xml::get_optional_class(node, obj.SourceFiles                          , "SourceFiles"); // fmi2::md::SourceFiles

        log(ext_trace)("Completed ModelExchange");
    }


    void from_xml(const xml_node &node, CoSimulation &obj)
    {
        log(ext_trace)("Parsing CoSimulation");

        utils::xml::get_attribute(node, obj.modelIdentifier                         , "modelIdentifier"); // string
        utils::xml::get_optional_attribute(node, obj.needsExecutionTool                      , "needsExecutionTool"); // bool
        utils::xml::get_optional_attribute(node, obj.canHandleVariableCommunicationStepSize  , "canHandleVariableCommunicationStepSize"); // bool
        utils::xml::get_optional_attribute(node, obj.canInterpolateInputs                    , "canInterpolateInputs"); // bool
        utils::xml::get_optional_attribute(node, obj.maxOutputDerivativeOrder                , "maxOutputDerivativeOrder"); // bool
        utils::xml::get_optional_attribute(node, obj.canRunAsynchronuously                   , "canRunAsynchronuously"); // bool
        utils::xml::get_optional_attribute(node, obj.canBeInstantiatedOnlyOncePerProcess     , "canBeInstantiatedOnlyOncePerProcess"); // bool
        utils::xml::get_optional_attribute(node, obj.canNotUseMemoryManagementFunctions      , "canNotUseMemoryManagementFunctions"); // bool
        utils::xml::get_optional_attribute(node, obj.canGetAndSetFMUstate                    , "canGetAndSetFMUstate"); // bool
        utils::xml::get_optional_attribute(node, obj.canSerializeFMUstate                    , "canSerializeFMUstate"); // bool
        utils::xml::get_optional_attribute(node, obj.providesDirectionalDerivatives          , "providesDirectionalDerivatives"); // bool
        utils::xml::get_optional_class(node, obj.SourceFiles                             , "SourceFiles"); // fmi2::md::SourceFiles

        log(ext_trace)("Completed CoSimulation");
    }


    void from_xml(const xml_node &node, fmi2ModelDescription &obj)
    {
        log(ext_trace)("Parsing fmi2ModelDescription");

        utils::xml::get_attribute(node, obj.fmiVersion                , "fmiVersion"); // string
        utils::xml::get_attribute(node, obj.modelName                 , "modelName"); // string
        utils::xml::get_attribute(node, obj.guid                      , "guid"); // string
        utils::xml::get_optional_attribute(node, obj.description               , "description"); // string
        utils::xml::get_optional_attribute(node, obj.author                    , "author"); // string
        utils::xml::get_optional_attribute(node, obj.version                   , "version"); // string
        utils::xml::get_optional_attribute(node, obj.copyright                 , "copyright"); // string
        utils::xml::get_optional_attribute(node, obj.license                   , "license"); // string
        utils::xml::get_optional_attribute(node, obj.generationTool            , "generationTool"); // string
        utils::xml::get_optional_attribute(node, obj.generationDateAndTime     , "generationDateAndTime"); // string
        utils::xml::get_optional_attribute(node, obj.variableNamingConvention  , "variableNamingConvention"); // string
        utils::xml::get_optional_attribute(node, obj.numberOfEventIndicators   , "numberOfEventIndicators"); // string
        utils::xml::get_optional_class(node, obj.ModelExchange             , "ModelExchange"); // fmi2::md::ModelExchange
        utils::xml::get_optional_class(node, obj.CoSimulation              , "CoSimulation"); // fmi2::md::CoSimulation
        utils::xml::get_optional_class(node, obj.UnitDefinitions           , "UnitDefinitions"); // fmi2::md::UnitDefinitions
        utils::xml::get_optional_class(node, obj.TypeDefinitions           , "TypeDefinitions"); // fmi2::md::TypeDefinitions
        utils::xml::get_optional_class(node, obj.LogCategories             , "LogCategories"); // fmi2::md::LogCategories
        utils::xml::get_optional_class(node, obj.DefaultExperiment         , "DefaultExperiment"); // fmi2::md::DefaultExperiment
        utils::xml::get_optional_class(node, obj.VendorAnnotations         , "VendorAnnotations"); // fmi2::md::VendorAnnotations
        utils::xml::get_class(node, obj.ModelVariables            , "ModelVariables"); // fmi2::md::ModelVariables
        utils::xml::get_class(node, obj.ModelStructure            , "ModelStructure"); // fmi2::md::ModelStructure

        log(ext_trace)("Completed fmi2ModelDescription");
    }

}
