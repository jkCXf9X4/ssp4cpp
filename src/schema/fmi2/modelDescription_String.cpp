
#include <string>

#include <optional>
#include <vector>

#include "modelDescription.hpp"
#include "to_string.hpp"

using namespace std;
using namespace ssp4cpp::str;

namespace ssp4cpp::fmi2
{

     // BaseUnit
    string to_string(const BaseUnit &obj)
    {
        return "BaseUnit { \n"
               "kg       : " + std::to_string( obj.kg.value_or(0) )           + "\n" +
               "m        : " + std::to_string( obj.m.value_or(0) )            + "\n" +
               "s        : " + std::to_string( obj.s.value_or(0) )            + "\n" +
               "a        : " + std::to_string( obj.a.value_or(0) )            + "\n" +
               "k        : " + std::to_string( obj.k.value_or(0) )            + "\n" +
               "mol      : " + std::to_string( obj.mol.value_or(0) )          + "\n" +
               "cd       : " + std::to_string( obj.cd.value_or(0) )           + "\n" +
               "rad      : " + std::to_string( obj.rad.value_or(0) )          + "\n" +
               "factor   : " + std::to_string( obj.factor.value_or(0.0) )     + "\n" +
               "offset   : " + std::to_string( obj.offset.value_or(0.0) )     + "\n" +
               "}";
    }
    string to_string(const optional<BaseUnit> &obj) { return to_string_optional(obj); }
    string to_string(const vector<BaseUnit> &obj) { return to_string_vector(obj); }

     // DisplayUnit
    string to_string(const DisplayUnit &obj)
    {
        return "DisplayUnit { \n"
               "name     : " + obj.name                                       + "\n" +
               "factor   : " + std::to_string( obj.factor.value_or(0.0) )     + "\n" +
               "offset   : " + std::to_string( obj.offset.value_or(0.0) )     + "\n" +
               "}";
    }
    string to_string(const optional<DisplayUnit> &obj) { return to_string_optional(obj); }
    string to_string(const vector<DisplayUnit> &obj) { return to_string_vector(obj); }

     // fmi2Unit
    string to_string(const fmi2Unit &obj)
    {
        return "fmi2Unit { \n"
               "name          : " + obj.name                                            + "\n" +
               "BaseUnit      : " + to_string( obj.BaseUnit )                           + "\n" +
               "DisplayUnit   : " + to_string(obj.DisplayUnit    ) + "\n" +
               "}";
    }
    string to_string(const optional<fmi2Unit> &obj) { return to_string_optional(obj); }
    string to_string(const vector<fmi2Unit> &obj) { return to_string_vector(obj); }

     // UnitDefinitions
    string to_string(const UnitDefinitions &obj)
    {
        return "UnitDefinitions { \n"
               "Units   : " + to_string(obj.Units    ) + "\n" +
               "}";
    }
    string to_string(const optional<UnitDefinitions> &obj) { return to_string_optional(obj); }
    string to_string(const vector<UnitDefinitions> &obj) { return to_string_vector(obj); }

     // Boolean
    string to_string(const Boolean &obj)
    {
        return "Boolean { \n"
               "declaredType   : " + obj.declaredType.value_or("null")                    + "\n" +
               "start          : " + obj.start.value_or("null")                           + "\n" +
               "}";
    }
    string to_string(const optional<Boolean> &obj) { return to_string_optional(obj); }
    string to_string(const vector<Boolean> &obj) { return to_string_vector(obj); }

     // Integer
    string to_string(const Integer &obj)
    {
        return "Integer { \n"
               "declaredType   : " + obj.declaredType.value_or("null")                    + "\n" +
               "start          : " + obj.start.value_or("null")                           + "\n" +
               "quantity       : " + obj.quantity.value_or("null")                        + "\n" +
               "min            : " + std::to_string( obj.min.value_or(0) )                + "\n" +
               "max            : " + std::to_string( obj.max.value_or(0) )                + "\n" +
               "}";
    }
    string to_string(const optional<Integer> &obj) { return to_string_optional(obj); }
    string to_string(const vector<Integer> &obj) { return to_string_vector(obj); }

     // String
    string to_string(const String &obj)
    {
        return "String { \n"
               "declaredType   : " + obj.declaredType.value_or("null")                    + "\n" +
               "start          : " + obj.start.value_or("null")                           + "\n" +
               "}";
    }
    string to_string(const optional<String> &obj) { return to_string_optional(obj); }
    string to_string(const vector<String> &obj) { return to_string_vector(obj); }

     // Real
    string to_string(const Real &obj)
    {
        return "Real { \n"
               "declaredType       : " + obj.declaredType.value_or("null")                        + "\n" +
               "quantity           : " + obj.quantity.value_or("null")                            + "\n" +
               "unit               : " + obj.unit.value_or("null")                                + "\n" +
               "displayUnit        : " + obj.displayUnit.value_or("null")                         + "\n" +
               "relativeQuantity   : " + std::to_string( obj.relativeQuantity.value_or(false) )   + "\n" +
               "min                : " + std::to_string( obj.min.value_or(0.0) )                  + "\n" +
               "max                : " + std::to_string( obj.max.value_or(0.0) )                  + "\n" +
               "nominal            : " + std::to_string( obj.nominal.value_or(0.0) )              + "\n" +
               "unbounded          : " + std::to_string( obj.unbounded.value_or(false) )          + "\n" +
               "start              : " + std::to_string( obj.start.value_or(0.0) )                + "\n" +
               "derivative         : " + std::to_string( obj.derivative.value_or(0) )             + "\n" +
               "reinit             : " + std::to_string( obj.reinit.value_or(false) )             + "\n" +
               "}";
    }
    string to_string(const optional<Real> &obj) { return to_string_optional(obj); }
    string to_string(const vector<Real> &obj) { return to_string_vector(obj); }

     // Enumeration
    string to_string(const Enumeration &obj)
    {
        return "Enumeration { \n"
               "declaredType   : " + obj.declaredType                                     + "\n" +
               "quantity       : " + obj.quantity.value_or("null")                        + "\n" +
               "min            : " + std::to_string( obj.min.value_or(0) )                + "\n" +
               "max            : " + std::to_string( obj.max.value_or(0) )                + "\n" +
               "start          : " + std::to_string( obj.start.value_or(0) )              + "\n" +
               "}";
    }
    string to_string(const optional<Enumeration> &obj) { return to_string_optional(obj); }
    string to_string(const vector<Enumeration> &obj) { return to_string_vector(obj); }

     // SimpleTypeEnumerationItem
    string to_string(const SimpleTypeEnumerationItem &obj)
    {
        return "SimpleTypeEnumerationItem { \n"
               "name          : " + obj.name                                            + "\n" +
               "value         : " + std::to_string( obj.value )                         + "\n" +
               "description   : " + obj.description.value_or("null")                    + "\n" +
               "}";
    }
    string to_string(const optional<SimpleTypeEnumerationItem> &obj) { return to_string_optional(obj); }
    string to_string(const vector<SimpleTypeEnumerationItem> &obj) { return to_string_vector(obj); }

     // SimpleTypeEnumeration
    string to_string(const SimpleTypeEnumeration &obj)
    {
        return "SimpleTypeEnumeration { \n"
               "quantity   : " + obj.quantity.value_or("null")                    + "\n" +
               "item       : " + to_string(obj.item        ) + "\n" +
               "}";
    }
    string to_string(const optional<SimpleTypeEnumeration> &obj) { return to_string_optional(obj); }
    string to_string(const vector<SimpleTypeEnumeration> &obj) { return to_string_vector(obj); }

     // fmi2SimpleType
    string to_string(const fmi2SimpleType &obj)
    {
        return "fmi2SimpleType { \n"
               "name          : " + obj.name                                            + "\n" +
               "description   : " + obj.description.value_or("null")                    + "\n" +
               "Real          : " + to_string( obj.Real )                               + "\n" +
               "Integer       : " + to_string( obj.Integer )                            + "\n" +
               "Boolean       : " + to_string( obj.Boolean )                            + "\n" +
               "String        : " + to_string( obj.String )                             + "\n" +
               "Enumeration   : " + to_string( obj.Enumeration )                        + "\n" +
               "}";
    }
    string to_string(const optional<fmi2SimpleType> &obj) { return to_string_optional(obj); }
    string to_string(const vector<fmi2SimpleType> &obj) { return to_string_vector(obj); }

     // TypeDefinitions
    string to_string(const TypeDefinitions &obj)
    {
        return "TypeDefinitions { \n"
               "SimpleTypes   : " + to_string(obj.SimpleTypes    ) + "\n" +
               "}";
    }
    string to_string(const optional<TypeDefinitions> &obj) { return to_string_optional(obj); }
    string to_string(const vector<TypeDefinitions> &obj) { return to_string_vector(obj); }

     // Category
    string to_string(const Category &obj)
    {
        return "Category { \n"
               "name          : " + obj.name                                            + "\n" +
               "description   : " + obj.description.value_or("null")                    + "\n" +
               "}";
    }
    string to_string(const optional<Category> &obj) { return to_string_optional(obj); }
    string to_string(const vector<Category> &obj) { return to_string_vector(obj); }

     // LogCategories
    string to_string(const LogCategories &obj)
    {
        return "LogCategories { \n"
               "categories   : " + to_string(obj.categories    ) + "\n" +
               "}";
    }
    string to_string(const optional<LogCategories> &obj) { return to_string_optional(obj); }
    string to_string(const vector<LogCategories> &obj) { return to_string_vector(obj); }

     // fmi2Annotation
    string to_string(const fmi2Annotation &obj)
    {
        return "fmi2Annotation { \n"
               "annotation   : " + obj.annotation                                     + "\n" +
               "}";
    }
    string to_string(const optional<fmi2Annotation> &obj) { return to_string_optional(obj); }
    string to_string(const vector<fmi2Annotation> &obj) { return to_string_vector(obj); }

     // VendorAnnotations
    string to_string(const VendorAnnotations &obj)
    {
        return "VendorAnnotations { \n"
               "Annotations   : " + to_string(obj.Annotations    ) + "\n" +
               "}";
    }
    string to_string(const optional<VendorAnnotations> &obj) { return to_string_optional(obj); }
    string to_string(const vector<VendorAnnotations> &obj) { return to_string_vector(obj); }

     // DefaultExperiment
    string to_string(const DefaultExperiment &obj)
    {
        return "DefaultExperiment { \n"
               "startTime   : " + std::to_string( obj.startTime.value_or(0.0) )     + "\n" +
               "stopTime    : " + std::to_string( obj.stopTime.value_or(0.0) )      + "\n" +
               "tolerance   : " + std::to_string( obj.tolerance.value_or(0.0) )     + "\n" +
               "stepSize    : " + std::to_string( obj.stepSize.value_or(0.0) )      + "\n" +
               "}";
    }
    string to_string(const optional<DefaultExperiment> &obj) { return to_string_optional(obj); }
    string to_string(const vector<DefaultExperiment> &obj) { return to_string_vector(obj); }

     // fmi2ScalarVariable
    string to_string(const fmi2ScalarVariable &obj)
    {
        return "fmi2ScalarVariable { \n"
               "name                                 : " + obj.name                                                                   + "\n" +
               "valueReference                       : " + std::to_string( obj.valueReference.value_or(0) )                           + "\n" +
               "description                          : " + obj.description.value_or("null")                                           + "\n" +
               "causality                            : " + obj.causality.value_or("null")                                             + "\n" +
               "variability                          : " + obj.variability.value_or("null")                                           + "\n" +
               "initial                              : " + obj.initial.value_or("null")                                               + "\n" +
               "canHandleMultipleSetPerTimeInstant   : " + std::to_string( obj.canHandleMultipleSetPerTimeInstant.value_or(false) )   + "\n" +
               "Real                                 : " + to_string( obj.Real )                                                      + "\n" +
               "Integer                              : " + to_string( obj.Integer )                                                   + "\n" +
               "Boolean                              : " + to_string( obj.Boolean )                                                   + "\n" +
               "String                               : " + to_string( obj.String )                                                    + "\n" +
               "Enumeration                          : " + to_string( obj.Enumeration )                                               + "\n" +
               "Annotations                          : " + to_string(obj.Annotations                           ) + "\n" +
               "}";
    }
    string to_string(const optional<fmi2ScalarVariable> &obj) { return to_string_optional(obj); }
    string to_string(const vector<fmi2ScalarVariable> &obj) { return to_string_vector(obj); }

     // unknown
    string to_string(const unknown &obj)
    {
        return "unknown { \n"
               "index                   : " + std::to_string( obj.index )                                   + "\n" +
            //    "dependencies            : " + to_string(obj.dependencies             ) + "\n" +
               "dependencies_kind_str   : " + str::to_string(obj.dependencies_kind_str    ) + "\n" +
               "dependencies_kind       : " + to_string(obj.dependencies_kind        ) + "\n" +
               "}";
    }
    string to_string(const optional<unknown> &obj) { return to_string_optional(obj); }
    string to_string(const vector<unknown> &obj) { return to_string_vector(obj); }

     // ModelStructure
    string to_string(const ModelStructure &obj)
    {
        return "ModelStructure { \n"
               "outputs           : " + to_string(obj.outputs            ) + "\n" +
               "derivatives       : " + to_string(obj.derivatives        ) + "\n" +
               "initialUnknowns   : " + to_string(obj.initialUnknowns    ) + "\n" +
               "}";
    }
    string to_string(const optional<ModelStructure> &obj) { return to_string_optional(obj); }
    string to_string(const vector<ModelStructure> &obj) { return to_string_vector(obj); }

     // ModelVariables
    string to_string(const ModelVariables &obj)
    {
        return "ModelVariables { \n"
               "list   : " + to_string(obj.list    ) + "\n" +
               "}";
    }
    string to_string(const optional<ModelVariables> &obj) { return to_string_optional(obj); }
    string to_string(const vector<ModelVariables> &obj) { return to_string_vector(obj); }

     // File
    string to_string(const File &obj)
    {
        return "File { \n"
               "name   : " + obj.name                                     + "\n" +
               "}";
    }
    string to_string(const optional<File> &obj) { return to_string_optional(obj); }
    string to_string(const vector<File> &obj) { return to_string_vector(obj); }

     // ModelExchange
    string to_string(const ModelExchange &obj)
    {
        return "ModelExchange { \n"
               "modelIdentifier                       : " + obj.modelIdentifier                                                         + "\n" +
               "needsExecutionTool                    : " + std::to_string( obj.needsExecutionTool.value_or(false) )                    + "\n" +
               "completedIntegratorStepNotNeeded      : " + std::to_string( obj.completedIntegratorStepNotNeeded.value_or(false) )      + "\n" +
               "canBeInstantiatedOnlyOncePerProcess   : " + std::to_string( obj.canBeInstantiatedOnlyOncePerProcess.value_or(false) )   + "\n" +
               "canNotUseMemoryManagementFunctions    : " + std::to_string( obj.canNotUseMemoryManagementFunctions.value_or(false) )    + "\n" +
               "canGetAndSetFMUstate                  : " + std::to_string( obj.canGetAndSetFMUstate.value_or(false) )                  + "\n" +
               "canSerializeFMUstate                  : " + std::to_string( obj.canSerializeFMUstate.value_or(false) )                  + "\n" +
               "providesDirectionalDerivatives        : " + std::to_string( obj.providesDirectionalDerivatives.value_or(false) )        + "\n" +
               "SourceFiles                           : " + to_string(obj.SourceFiles                            ) + "\n" +
               "}";
    }
    string to_string(const optional<ModelExchange> &obj) { return to_string_optional(obj); }
    string to_string(const vector<ModelExchange> &obj) { return to_string_vector(obj); }

     // CoSimulation
    string to_string(const CoSimulation &obj)
    {
        return "CoSimulation { \n"
               "modelIdentifier                          : " + obj.modelIdentifier                                                            + "\n" +
               "needsExecutionTool                       : " + std::to_string( obj.needsExecutionTool.value_or(false) )                       + "\n" +
               "canHandleVariableCommunicationStepSize   : " + std::to_string( obj.canHandleVariableCommunicationStepSize.value_or(false) )   + "\n" +
               "canInterpolateInputs                     : " + std::to_string( obj.canInterpolateInputs.value_or(false) )                     + "\n" +
               "maxOutputDerivativeOrder                 : " + std::to_string( obj.maxOutputDerivativeOrder.value_or(false) )                 + "\n" +
               "canRunAsynchronuously                    : " + std::to_string( obj.canRunAsynchronuously.value_or(false) )                    + "\n" +
               "canBeInstantiatedOnlyOncePerProcess      : " + std::to_string( obj.canBeInstantiatedOnlyOncePerProcess.value_or(false) )      + "\n" +
               "canNotUseMemoryManagementFunctions       : " + std::to_string( obj.canNotUseMemoryManagementFunctions.value_or(false) )       + "\n" +
               "canGetAndSetFMUstate                     : " + std::to_string( obj.canGetAndSetFMUstate.value_or(false) )                     + "\n" +
               "canSerializeFMUstate                     : " + std::to_string( obj.canSerializeFMUstate.value_or(false) )                     + "\n" +
               "providesDirectionalDerivatives           : " + std::to_string( obj.providesDirectionalDerivatives.value_or(false) )           + "\n" +
               "SourceFiles                              : " + to_string(obj.SourceFiles                               ) + "\n" +
               "}";
    }
    string to_string(const optional<CoSimulation> &obj) { return to_string_optional(obj); }
    string to_string(const vector<CoSimulation> &obj) { return to_string_vector(obj); }

     // fmi2ModelDescription
    string to_string(const fmi2ModelDescription &obj)
    {
        return "fmi2ModelDescription { \n"
               "fmiVersion                 : " + obj.fmiVersion                                                   + "\n" +
               "modelName                  : " + obj.modelName                                                    + "\n" +
               "guid                       : " + obj.guid                                                         + "\n" +
               "description                : " + obj.description.value_or("null")                                 + "\n" +
               "author                     : " + obj.author.value_or("null")                                      + "\n" +
               "version                    : " + obj.version.value_or("null")                                     + "\n" +
               "copyright                  : " + obj.copyright.value_or("null")                                   + "\n" +
               "license                    : " + obj.license.value_or("null")                                     + "\n" +
               "generationTool             : " + obj.generationTool.value_or("null")                              + "\n" +
               "generationDateAndTime      : " + obj.generationDateAndTime.value_or("null")                       + "\n" +
               "variableNamingConvention   : " + obj.variableNamingConvention.value_or("null")                    + "\n" +
               "numberOfEventIndicators    : " + obj.numberOfEventIndicators.value_or("null")                     + "\n" +
               "ModelExchange              : " + to_string( obj.ModelExchange )                                   + "\n" +
               "CoSimulation               : " + to_string( obj.CoSimulation )                                    + "\n" +
               "UnitDefinitions            : " + to_string( obj.UnitDefinitions )                                 + "\n" +
               "TypeDefinitions            : " + to_string( obj.TypeDefinitions )                                 + "\n" +
               "LogCategories              : " + to_string( obj.LogCategories )                                   + "\n" +
               "DefaultExperiment          : " + to_string( obj.DefaultExperiment )                               + "\n" +
               "VendorAnnotations          : " + to_string( obj.VendorAnnotations )                               + "\n" +
               "ModelVariables             : " + to_string( obj.ModelVariables )                                  + "\n" +
               "ModelStructure             : " + to_string( obj.ModelStructure )                                  + "\n" +
               "}";
    }
    string to_string(const optional<fmi2ModelDescription> &obj) { return to_string_optional(obj); }
    string to_string(const vector<fmi2ModelDescription> &obj) { return to_string_vector(obj); }


}
