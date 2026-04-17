

// This is a generated file, do not alter
// it is based on fmi2_md.toml

#include "FMI2_modelDescription_XML.hpp"


#include "xml_deserialize.hpp"

#include "ssp4cpp/utils/log.hpp"

namespace ssp4cpp::fmi2::md
{
    using namespace pugi;

    quill::Logger* log()
    {
        // Cache this logger locally so we avoid eager header initialization.
        static quill::Logger* logger =
            ssp4cpp::utils::log::make_logger("ssp4cpp.fmi2.md", quill::LogLevel::TraceL1);
        return logger;
    }


    void from_xml(const xml_node &node, BaseUnit &obj)
    {
        LOG_TRACE_L1(log(), "Parsing BaseUnit");

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

        LOG_TRACE_L1(log(), "Completed BaseUnit");
    }


    void from_xml(const xml_node &node, DisplayUnit &obj)
    {
        LOG_TRACE_L1(log(), "Parsing DisplayUnit");

        utils::xml::get_attribute(node, obj.name    , "name"); // string
        utils::xml::get_optional_attribute(node, obj.factor  , "factor"); // double
        utils::xml::get_optional_attribute(node, obj.offset  , "offset"); // double

        LOG_TRACE_L1(log(), "Completed DisplayUnit");
    }


    void from_xml(const xml_node &node, fmi2Unit &obj)
    {
        LOG_TRACE_L1(log(), "Parsing fmi2Unit");

        utils::xml::get_attribute(node, obj.name         , "name"); // string
        utils::xml::get_optional_class(node, obj.BaseUnit     , "BaseUnit"); // fmi2::md::BaseUnit
        utils::xml::get_vector(node, obj.DisplayUnit  , "DisplayUnit"); // fmi2::md::DisplayUnit

        LOG_TRACE_L1(log(), "Completed fmi2Unit");
    }


    void from_xml(const xml_node &node, UnitDefinitions &obj)
    {
        LOG_TRACE_L1(log(), "Parsing UnitDefinitions");

        utils::xml::get_vector(node, obj.Units  , "Unit"); // fmi2::md::fmi2Unit

        LOG_TRACE_L1(log(), "Completed UnitDefinitions");
    }


    void from_xml(const xml_node &node, Boolean &obj)
    {
        LOG_TRACE_L1(log(), "Parsing Boolean");

        utils::xml::get_optional_attribute(node, obj.declaredType  , "declaredType"); // string
        utils::xml::get_optional_attribute(node, obj.start         , "start"); // bool

        LOG_TRACE_L1(log(), "Completed Boolean");
    }


    void from_xml(const xml_node &node, Integer &obj)
    {
        LOG_TRACE_L1(log(), "Parsing Integer");

        utils::xml::get_optional_attribute(node, obj.declaredType  , "declaredType"); // string
        utils::xml::get_optional_attribute(node, obj.start         , "start"); // int
        utils::xml::get_optional_attribute(node, obj.quantity      , "quantity"); // string
        utils::xml::get_optional_attribute(node, obj.min           , "min"); // int
        utils::xml::get_optional_attribute(node, obj.max           , "max"); // int

        LOG_TRACE_L1(log(), "Completed Integer");
    }


    void from_xml(const xml_node &node, String &obj)
    {
        LOG_TRACE_L1(log(), "Parsing String");

        utils::xml::get_optional_attribute(node, obj.declaredType  , "declaredType"); // string
        utils::xml::get_optional_attribute(node, obj.start         , "start"); // string

        LOG_TRACE_L1(log(), "Completed String");
    }


    void from_xml(const xml_node &node, Real &obj)
    {
        LOG_TRACE_L1(log(), "Parsing Real");

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

        LOG_TRACE_L1(log(), "Completed Real");
    }


    void from_xml(const xml_node &node, Enumeration &obj)
    {
        LOG_TRACE_L1(log(), "Parsing Enumeration");

        utils::xml::get_attribute(node, obj.declaredType  , "declaredType"); // string
        utils::xml::get_optional_attribute(node, obj.quantity      , "quantity"); // string
        utils::xml::get_optional_attribute(node, obj.min           , "min"); // int
        utils::xml::get_optional_attribute(node, obj.max           , "max"); // int
        utils::xml::get_optional_attribute(node, obj.start         , "start"); // int

        LOG_TRACE_L1(log(), "Completed Enumeration");
    }


    void from_xml(const xml_node &node, SimpleTypeEnumerationItem &obj)
    {
        LOG_TRACE_L1(log(), "Parsing SimpleTypeEnumerationItem");

        utils::xml::get_attribute(node, obj.name         , "name"); // string
        utils::xml::get_attribute(node, obj.value        , "value"); // int
        utils::xml::get_optional_attribute(node, obj.description  , "description"); // string

        LOG_TRACE_L1(log(), "Completed SimpleTypeEnumerationItem");
    }


    void from_xml(const xml_node &node, SimpleTypeEnumeration &obj)
    {
        LOG_TRACE_L1(log(), "Parsing SimpleTypeEnumeration");

        utils::xml::get_optional_attribute(node, obj.quantity  , "quantity"); // string
        utils::xml::get_vector(node, obj.Items     , "Item"); // fmi2::md::SimpleTypeEnumerationItem

        LOG_TRACE_L1(log(), "Completed SimpleTypeEnumeration");
    }


    void from_xml(const xml_node &node, fmi2SimpleType &obj)
    {
        LOG_TRACE_L1(log(), "Parsing fmi2SimpleType");

        utils::xml::get_attribute(node, obj.name         , "name"); // string
        utils::xml::get_optional_attribute(node, obj.description  , "description"); // string
        utils::xml::get_optional_class(node, obj.Real         , "Real"); // fmi2::md::Real
        utils::xml::get_optional_class(node, obj.Integer      , "Integer"); // fmi2::md::Integer
        utils::xml::get_optional_class(node, obj.Boolean      , "Boolean"); // fmi2::md::Boolean
        utils::xml::get_optional_class(node, obj.String       , "String"); // fmi2::md::String
        utils::xml::get_optional_class(node, obj.Enumeration  , "Enumeration"); // fmi2::md::SimpleTypeEnumeration

        LOG_TRACE_L1(log(), "Completed fmi2SimpleType");
    }


    void from_xml(const xml_node &node, TypeDefinitions &obj)
    {
        LOG_TRACE_L1(log(), "Parsing TypeDefinitions");

        utils::xml::get_vector(node, obj.SimpleTypes  , "SimpleType"); // fmi2::md::fmi2SimpleType

        LOG_TRACE_L1(log(), "Completed TypeDefinitions");
    }


    void from_xml(const xml_node &node, Category &obj)
    {
        LOG_TRACE_L1(log(), "Parsing Category");

        utils::xml::get_attribute(node, obj.name         , "name"); // string
        utils::xml::get_optional_attribute(node, obj.description  , "description"); // string

        LOG_TRACE_L1(log(), "Completed Category");
    }


    void from_xml(const xml_node &node, LogCategories &obj)
    {
        LOG_TRACE_L1(log(), "Parsing LogCategories");

        utils::xml::get_vector(node, obj.Categories  , "Category"); // fmi2::md::Category

        LOG_TRACE_L1(log(), "Completed LogCategories");
    }


    void from_xml(const xml_node &node, fmi2Annotation &obj)
    {
        LOG_TRACE_L1(log(), "Parsing fmi2Annotation");

        utils::xml::get_attribute(node, obj.annotation  , "annotation"); // string

        LOG_TRACE_L1(log(), "Completed fmi2Annotation");
    }


    void from_xml(const xml_node &node, VendorAnnotations &obj)
    {
        LOG_TRACE_L1(log(), "Parsing VendorAnnotations");

        utils::xml::get_vector(node, obj.Annotations  , "Annotation"); // fmi2::md::fmi2Annotation

        LOG_TRACE_L1(log(), "Completed VendorAnnotations");
    }


    void from_xml(const xml_node &node, DefaultExperiment &obj)
    {
        LOG_TRACE_L1(log(), "Parsing DefaultExperiment");

        utils::xml::get_optional_attribute(node, obj.startTime  , "startTime"); // double
        utils::xml::get_optional_attribute(node, obj.stopTime   , "stopTime"); // double
        utils::xml::get_optional_attribute(node, obj.tolerance  , "tolerance"); // double
        utils::xml::get_optional_attribute(node, obj.stepSize   , "stepSize"); // double

        LOG_TRACE_L1(log(), "Completed DefaultExperiment");
    }


    void from_xml(const xml_node &node, fmi2ScalarVariable &obj)
    {
        LOG_TRACE_L1(log(), "Parsing fmi2ScalarVariable");

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

        LOG_TRACE_L1(log(), "Completed fmi2ScalarVariable");
    }


    void from_xml(const xml_node &node, Unknown &obj)
    {
        LOG_TRACE_L1(log(), "Parsing Unknown");

        utils::xml::get_attribute(node, obj.index             , "index"); // int
        utils::xml::get_readable_vector(node, obj.dependencies      , "dependencies", " "); // int
        utils::xml::get_readable_vector(node, obj.dependenciesKind  , "dependenciesKind", " "); // fmi2::md::DependenciesKind

        LOG_TRACE_L1(log(), "Completed Unknown");
    }


    void from_xml(const xml_node &node, Outputs &obj)
    {
        LOG_TRACE_L1(log(), "Parsing Outputs");

        utils::xml::get_vector(node, obj.Unknowns  , "Unknown"); // fmi2::md::Unknown

        LOG_TRACE_L1(log(), "Completed Outputs");
    }


    void from_xml(const xml_node &node, Derivatives &obj)
    {
        LOG_TRACE_L1(log(), "Parsing Derivatives");

        utils::xml::get_vector(node, obj.Unknowns  , "Unknown"); // fmi2::md::Unknown

        LOG_TRACE_L1(log(), "Completed Derivatives");
    }


    void from_xml(const xml_node &node, InitialUnknowns &obj)
    {
        LOG_TRACE_L1(log(), "Parsing InitialUnknowns");

        utils::xml::get_vector(node, obj.Unknowns  , "Unknown"); // fmi2::md::Unknown

        LOG_TRACE_L1(log(), "Completed InitialUnknowns");
    }


    void from_xml(const xml_node &node, ModelStructure &obj)
    {
        LOG_TRACE_L1(log(), "Parsing ModelStructure");

        utils::xml::get_optional_class(node, obj.Outputs          , "Outputs"); // fmi2::md::Outputs
        utils::xml::get_optional_class(node, obj.Derivatives      , "Derivatives"); // fmi2::md::Derivatives
        utils::xml::get_optional_class(node, obj.InitialUnknowns  , "InitialUnknowns"); // fmi2::md::InitialUnknowns

        LOG_TRACE_L1(log(), "Completed ModelStructure");
    }


    void from_xml(const xml_node &node, ModelVariables &obj)
    {
        LOG_TRACE_L1(log(), "Parsing ModelVariables");

        utils::xml::get_vector(node, obj.ScalarVariable  , "ScalarVariable"); // fmi2::md::fmi2ScalarVariable

        LOG_TRACE_L1(log(), "Completed ModelVariables");
    }


    void from_xml(const xml_node &node, File &obj)
    {
        LOG_TRACE_L1(log(), "Parsing File");

        utils::xml::get_attribute(node, obj.name  , "name"); // string

        LOG_TRACE_L1(log(), "Completed File");
    }


    void from_xml(const xml_node &node, SourceFiles &obj)
    {
        LOG_TRACE_L1(log(), "Parsing SourceFiles");

        utils::xml::get_vector(node, obj.Files  , "File"); // fmi2::md::File

        LOG_TRACE_L1(log(), "Completed SourceFiles");
    }


    void from_xml(const xml_node &node, ModelExchange &obj)
    {
        LOG_TRACE_L1(log(), "Parsing ModelExchange");

        utils::xml::get_attribute(node, obj.modelIdentifier                      , "modelIdentifier"); // string
        utils::xml::get_optional_attribute(node, obj.needsExecutionTool                   , "needsExecutionTool"); // bool
        utils::xml::get_optional_attribute(node, obj.completedIntegratorStepNotNeeded     , "completedIntegratorStepNotNeeded"); // bool
        utils::xml::get_optional_attribute(node, obj.canBeInstantiatedOnlyOncePerProcess  , "canBeInstantiatedOnlyOncePerProcess"); // bool
        utils::xml::get_optional_attribute(node, obj.canNotUseMemoryManagementFunctions   , "canNotUseMemoryManagementFunctions"); // bool
        utils::xml::get_optional_attribute(node, obj.canGetAndSetFMUstate                 , "canGetAndSetFMUstate"); // bool
        utils::xml::get_optional_attribute(node, obj.canSerializeFMUstate                 , "canSerializeFMUstate"); // bool
        utils::xml::get_optional_attribute(node, obj.providesDirectionalDerivatives       , "providesDirectionalDerivatives"); // bool
        utils::xml::get_optional_class(node, obj.SourceFiles                          , "SourceFiles"); // fmi2::md::SourceFiles

        LOG_TRACE_L1(log(), "Completed ModelExchange");
    }


    void from_xml(const xml_node &node, CoSimulation &obj)
    {
        LOG_TRACE_L1(log(), "Parsing CoSimulation");

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

        LOG_TRACE_L1(log(), "Completed CoSimulation");
    }


    void from_xml(const xml_node &node, fmi2ModelDescription &obj)
    {
        LOG_TRACE_L1(log(), "Parsing fmi2ModelDescription");

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

        LOG_TRACE_L1(log(), "Completed fmi2ModelDescription");
    }

}
