

// This is a generated file, do not alter
// it is based on fmi2_md.toml

#include "ssp4cpp/schema/fmi2/FMI2_modelDescription.hpp"
#include "ssp4cpp/utils/string.hpp"

#include <string>

namespace ssp4cpp::fmi2::md
{
    using namespace utils::str;


     // BaseUnit
    std::string BaseUnit::to_string(void) const
    {
        return "BaseUnit { \n"
               "kg      : " + to_str( kg      ) + "\n" +
               "m       : " + to_str( m       ) + "\n" +
               "s       : " + to_str( s       ) + "\n" +
               "a       : " + to_str( a       ) + "\n" +
               "k       : " + to_str( k       ) + "\n" +
               "mol     : " + to_str( mol     ) + "\n" +
               "cd      : " + to_str( cd      ) + "\n" +
               "rad     : " + to_str( rad     ) + "\n" +
               "factor  : " + to_str( factor  ) + "\n" +
               "offset  : " + to_str( offset  ) + "\n" +
               "}";
    }

     // DisplayUnit
    std::string DisplayUnit::to_string(void) const
    {
        return "DisplayUnit { \n"
               "name    : " + to_str( name    ) + "\n" +
               "factor  : " + to_str( factor  ) + "\n" +
               "offset  : " + to_str( offset  ) + "\n" +
               "}";
    }

     // fmi2Unit
    std::string fmi2Unit::to_string(void) const
    {
        return "fmi2Unit { \n"
               "name         : " + to_str( name         ) + "\n" +
               "BaseUnit     : " + to_str( BaseUnit     ) + "\n" +
               "DisplayUnit  : " + to_str( DisplayUnit  ) + "\n" +
               "}";
    }

     // UnitDefinitions
    std::string UnitDefinitions::to_string(void) const
    {
        return "UnitDefinitions { \n"
               "Units  : " + to_str( Units  ) + "\n" +
               "}";
    }

     // Boolean
    std::string Boolean::to_string(void) const
    {
        return "Boolean { \n"
               "declaredType  : " + to_str( declaredType  ) + "\n" +
               "start         : " + to_str( start         ) + "\n" +
               "}";
    }

     // Integer
    std::string Integer::to_string(void) const
    {
        return "Integer { \n"
               "declaredType  : " + to_str( declaredType  ) + "\n" +
               "start         : " + to_str( start         ) + "\n" +
               "quantity      : " + to_str( quantity      ) + "\n" +
               "min           : " + to_str( min           ) + "\n" +
               "max           : " + to_str( max           ) + "\n" +
               "}";
    }

     // String
    std::string String::to_string(void) const
    {
        return "String { \n"
               "declaredType  : " + to_str( declaredType  ) + "\n" +
               "start         : " + to_str( start         ) + "\n" +
               "}";
    }

     // Real
    std::string Real::to_string(void) const
    {
        return "Real { \n"
               "declaredType      : " + to_str( declaredType      ) + "\n" +
               "quantity          : " + to_str( quantity          ) + "\n" +
               "unit              : " + to_str( unit              ) + "\n" +
               "displayUnit       : " + to_str( displayUnit       ) + "\n" +
               "relativeQuantity  : " + to_str( relativeQuantity  ) + "\n" +
               "min               : " + to_str( min               ) + "\n" +
               "max               : " + to_str( max               ) + "\n" +
               "nominal           : " + to_str( nominal           ) + "\n" +
               "unbounded         : " + to_str( unbounded         ) + "\n" +
               "start             : " + to_str( start             ) + "\n" +
               "derivative        : " + to_str( derivative        ) + "\n" +
               "reinit            : " + to_str( reinit            ) + "\n" +
               "}";
    }

     // Enumeration
    std::string Enumeration::to_string(void) const
    {
        return "Enumeration { \n"
               "declaredType  : " + to_str( declaredType  ) + "\n" +
               "quantity      : " + to_str( quantity      ) + "\n" +
               "min           : " + to_str( min           ) + "\n" +
               "max           : " + to_str( max           ) + "\n" +
               "start         : " + to_str( start         ) + "\n" +
               "}";
    }

     // SimpleTypeEnumerationItem
    std::string SimpleTypeEnumerationItem::to_string(void) const
    {
        return "SimpleTypeEnumerationItem { \n"
               "name         : " + to_str( name         ) + "\n" +
               "value        : " + to_str( value        ) + "\n" +
               "description  : " + to_str( description  ) + "\n" +
               "}";
    }

     // SimpleTypeEnumeration
    std::string SimpleTypeEnumeration::to_string(void) const
    {
        return "SimpleTypeEnumeration { \n"
               "quantity  : " + to_str( quantity  ) + "\n" +
               "Items     : " + to_str( Items     ) + "\n" +
               "}";
    }

     // fmi2SimpleType
    std::string fmi2SimpleType::to_string(void) const
    {
        return "fmi2SimpleType { \n"
               "name         : " + to_str( name         ) + "\n" +
               "description  : " + to_str( description  ) + "\n" +
               "Real         : " + to_str( Real         ) + "\n" +
               "Integer      : " + to_str( Integer      ) + "\n" +
               "Boolean      : " + to_str( Boolean      ) + "\n" +
               "String       : " + to_str( String       ) + "\n" +
               "Enumeration  : " + to_str( Enumeration  ) + "\n" +
               "}";
    }

     // TypeDefinitions
    std::string TypeDefinitions::to_string(void) const
    {
        return "TypeDefinitions { \n"
               "SimpleTypes  : " + to_str( SimpleTypes  ) + "\n" +
               "}";
    }

     // Category
    std::string Category::to_string(void) const
    {
        return "Category { \n"
               "name         : " + to_str( name         ) + "\n" +
               "description  : " + to_str( description  ) + "\n" +
               "}";
    }

     // LogCategories
    std::string LogCategories::to_string(void) const
    {
        return "LogCategories { \n"
               "Categories  : " + to_str( Categories  ) + "\n" +
               "}";
    }

     // fmi2Annotation
    std::string fmi2Annotation::to_string(void) const
    {
        return "fmi2Annotation { \n"
               "annotation  : " + to_str( annotation  ) + "\n" +
               "}";
    }

     // VendorAnnotations
    std::string VendorAnnotations::to_string(void) const
    {
        return "VendorAnnotations { \n"
               "Annotations  : " + to_str( Annotations  ) + "\n" +
               "}";
    }

     // DefaultExperiment
    std::string DefaultExperiment::to_string(void) const
    {
        return "DefaultExperiment { \n"
               "startTime  : " + to_str( startTime  ) + "\n" +
               "stopTime   : " + to_str( stopTime   ) + "\n" +
               "tolerance  : " + to_str( tolerance  ) + "\n" +
               "stepSize   : " + to_str( stepSize   ) + "\n" +
               "}";
    }

     // fmi2ScalarVariable
    std::string fmi2ScalarVariable::to_string(void) const
    {
        return "fmi2ScalarVariable { \n"
               "name                                : " + to_str( name                                ) + "\n" +
               "valueReference                      : " + to_str( valueReference                      ) + "\n" +
               "description                         : " + to_str( description                         ) + "\n" +
               "causality                           : " + to_str( causality                           ) + "\n" +
               "variability                         : " + to_str( variability                         ) + "\n" +
               "initial                             : " + to_str( initial                             ) + "\n" +
               "canHandleMultipleSetPerTimeInstant  : " + to_str( canHandleMultipleSetPerTimeInstant  ) + "\n" +
               "Real                                : " + to_str( Real                                ) + "\n" +
               "Integer                             : " + to_str( Integer                             ) + "\n" +
               "Boolean                             : " + to_str( Boolean                             ) + "\n" +
               "String                              : " + to_str( String                              ) + "\n" +
               "Enumeration                         : " + to_str( Enumeration                         ) + "\n" +
               "Annotations                         : " + to_str( Annotations                         ) + "\n" +
               "}";
    }

     // Unknown
    std::string Unknown::to_string(void) const
    {
        return "Unknown { \n"
               "index             : " + to_str( index             ) + "\n" +
               "dependencies      : " + to_str( dependencies      ) + "\n" +
               "dependenciesKind  : " + to_str( dependenciesKind  ) + "\n" +
               "}";
    }

     // Outputs
    std::string Outputs::to_string(void) const
    {
        return "Outputs { \n"
               "Unknowns  : " + to_str( Unknowns  ) + "\n" +
               "}";
    }

     // Derivatives
    std::string Derivatives::to_string(void) const
    {
        return "Derivatives { \n"
               "Unknowns  : " + to_str( Unknowns  ) + "\n" +
               "}";
    }

     // InitialUnknowns
    std::string InitialUnknowns::to_string(void) const
    {
        return "InitialUnknowns { \n"
               "Unknowns  : " + to_str( Unknowns  ) + "\n" +
               "}";
    }

     // ModelStructure
    std::string ModelStructure::to_string(void) const
    {
        return "ModelStructure { \n"
               "Outputs          : " + to_str( Outputs          ) + "\n" +
               "Derivatives      : " + to_str( Derivatives      ) + "\n" +
               "InitialUnknowns  : " + to_str( InitialUnknowns  ) + "\n" +
               "}";
    }

     // ModelVariables
    std::string ModelVariables::to_string(void) const
    {
        return "ModelVariables { \n"
               "ScalarVariable  : " + to_str( ScalarVariable  ) + "\n" +
               "}";
    }

     // File
    std::string File::to_string(void) const
    {
        return "File { \n"
               "name  : " + to_str( name  ) + "\n" +
               "}";
    }

     // SourceFiles
    std::string SourceFiles::to_string(void) const
    {
        return "SourceFiles { \n"
               "Files  : " + to_str( Files  ) + "\n" +
               "}";
    }

     // ModelExchange
    std::string ModelExchange::to_string(void) const
    {
        return "ModelExchange { \n"
               "modelIdentifier                      : " + to_str( modelIdentifier                      ) + "\n" +
               "needsExecutionTool                   : " + to_str( needsExecutionTool                   ) + "\n" +
               "completedIntegratorStepNotNeeded     : " + to_str( completedIntegratorStepNotNeeded     ) + "\n" +
               "canBeInstantiatedOnlyOncePerProcess  : " + to_str( canBeInstantiatedOnlyOncePerProcess  ) + "\n" +
               "canNotUseMemoryManagementFunctions   : " + to_str( canNotUseMemoryManagementFunctions   ) + "\n" +
               "canGetAndSetFMUstate                 : " + to_str( canGetAndSetFMUstate                 ) + "\n" +
               "canSerializeFMUstate                 : " + to_str( canSerializeFMUstate                 ) + "\n" +
               "providesDirectionalDerivatives       : " + to_str( providesDirectionalDerivatives       ) + "\n" +
               "SourceFiles                          : " + to_str( SourceFiles                          ) + "\n" +
               "}";
    }

     // CoSimulation
    std::string CoSimulation::to_string(void) const
    {
        return "CoSimulation { \n"
               "modelIdentifier                         : " + to_str( modelIdentifier                         ) + "\n" +
               "needsExecutionTool                      : " + to_str( needsExecutionTool                      ) + "\n" +
               "canHandleVariableCommunicationStepSize  : " + to_str( canHandleVariableCommunicationStepSize  ) + "\n" +
               "canInterpolateInputs                    : " + to_str( canInterpolateInputs                    ) + "\n" +
               "maxOutputDerivativeOrder                : " + to_str( maxOutputDerivativeOrder                ) + "\n" +
               "canRunAsynchronuously                   : " + to_str( canRunAsynchronuously                   ) + "\n" +
               "canBeInstantiatedOnlyOncePerProcess     : " + to_str( canBeInstantiatedOnlyOncePerProcess     ) + "\n" +
               "canNotUseMemoryManagementFunctions      : " + to_str( canNotUseMemoryManagementFunctions      ) + "\n" +
               "canGetAndSetFMUstate                    : " + to_str( canGetAndSetFMUstate                    ) + "\n" +
               "canSerializeFMUstate                    : " + to_str( canSerializeFMUstate                    ) + "\n" +
               "providesDirectionalDerivatives          : " + to_str( providesDirectionalDerivatives          ) + "\n" +
               "SourceFiles                             : " + to_str( SourceFiles                             ) + "\n" +
               "}";
    }

     // fmi2ModelDescription
    std::string fmi2ModelDescription::to_string(void) const
    {
        return "fmi2ModelDescription { \n"
               "fmiVersion                : " + to_str( fmiVersion                ) + "\n" +
               "modelName                 : " + to_str( modelName                 ) + "\n" +
               "guid                      : " + to_str( guid                      ) + "\n" +
               "description               : " + to_str( description               ) + "\n" +
               "author                    : " + to_str( author                    ) + "\n" +
               "version                   : " + to_str( version                   ) + "\n" +
               "copyright                 : " + to_str( copyright                 ) + "\n" +
               "license                   : " + to_str( license                   ) + "\n" +
               "generationTool            : " + to_str( generationTool            ) + "\n" +
               "generationDateAndTime     : " + to_str( generationDateAndTime     ) + "\n" +
               "variableNamingConvention  : " + to_str( variableNamingConvention  ) + "\n" +
               "numberOfEventIndicators   : " + to_str( numberOfEventIndicators   ) + "\n" +
               "ModelExchange             : " + to_str( ModelExchange             ) + "\n" +
               "CoSimulation              : " + to_str( CoSimulation              ) + "\n" +
               "UnitDefinitions           : " + to_str( UnitDefinitions           ) + "\n" +
               "TypeDefinitions           : " + to_str( TypeDefinitions           ) + "\n" +
               "LogCategories             : " + to_str( LogCategories             ) + "\n" +
               "DefaultExperiment         : " + to_str( DefaultExperiment         ) + "\n" +
               "VendorAnnotations         : " + to_str( VendorAnnotations         ) + "\n" +
               "ModelVariables            : " + to_str( ModelVariables            ) + "\n" +
               "ModelStructure            : " + to_str( ModelStructure            ) + "\n" +
               "}";
    }

}
