

// This is a generated file, do not alter
// it is based on fmi2_md.toml

#include "ssp4cpp/schema/fmi2/FMI2_modelDescription.hpp"
#include "ssp4cpp/utils/string.hpp"

#include <string>

namespace ssp4cpp::fmi2::md
{


     // BaseUnit
    std::string BaseUnit::to_string(void) const
    {
        return "BaseUnit { \n"
               "kg      : " + utils::str::to_string( kg      ) + "\n" +
               "m       : " + utils::str::to_string( m       ) + "\n" +
               "s       : " + utils::str::to_string( s       ) + "\n" +
               "a       : " + utils::str::to_string( a       ) + "\n" +
               "k       : " + utils::str::to_string( k       ) + "\n" +
               "mol     : " + utils::str::to_string( mol     ) + "\n" +
               "cd      : " + utils::str::to_string( cd      ) + "\n" +
               "rad     : " + utils::str::to_string( rad     ) + "\n" +
               "factor  : " + utils::str::to_string( factor  ) + "\n" +
               "offset  : " + utils::str::to_string( offset  ) + "\n" +
               "}";
    }

     // DisplayUnit
    std::string DisplayUnit::to_string(void) const
    {
        return "DisplayUnit { \n"
               "name    : " + utils::str::to_string( name    ) + "\n" +
               "factor  : " + utils::str::to_string( factor  ) + "\n" +
               "offset  : " + utils::str::to_string( offset  ) + "\n" +
               "}";
    }

     // fmi2Unit
    std::string fmi2Unit::to_string(void) const
    {
        return "fmi2Unit { \n"
               "name         : " + utils::str::to_string( name         ) + "\n" +
               "BaseUnit     : " + utils::str::to_string( BaseUnit     ) + "\n" +
               "DisplayUnit  : " + utils::str::to_string( DisplayUnit  ) + "\n" +
               "}";
    }

     // UnitDefinitions
    std::string UnitDefinitions::to_string(void) const
    {
        return "UnitDefinitions { \n"
               "Units  : " + utils::str::to_string( Units  ) + "\n" +
               "}";
    }

     // Boolean
    std::string Boolean::to_string(void) const
    {
        return "Boolean { \n"
               "declaredType  : " + utils::str::to_string( declaredType  ) + "\n" +
               "start         : " + utils::str::to_string( start         ) + "\n" +
               "}";
    }

     // Integer
    std::string Integer::to_string(void) const
    {
        return "Integer { \n"
               "declaredType  : " + utils::str::to_string( declaredType  ) + "\n" +
               "start         : " + utils::str::to_string( start         ) + "\n" +
               "quantity      : " + utils::str::to_string( quantity      ) + "\n" +
               "min           : " + utils::str::to_string( min           ) + "\n" +
               "max           : " + utils::str::to_string( max           ) + "\n" +
               "}";
    }

     // String
    std::string String::to_string(void) const
    {
        return "String { \n"
               "declaredType  : " + utils::str::to_string( declaredType  ) + "\n" +
               "start         : " + utils::str::to_string( start         ) + "\n" +
               "}";
    }

     // Real
    std::string Real::to_string(void) const
    {
        return "Real { \n"
               "declaredType      : " + utils::str::to_string( declaredType      ) + "\n" +
               "quantity          : " + utils::str::to_string( quantity          ) + "\n" +
               "unit              : " + utils::str::to_string( unit              ) + "\n" +
               "displayUnit       : " + utils::str::to_string( displayUnit       ) + "\n" +
               "relativeQuantity  : " + utils::str::to_string( relativeQuantity  ) + "\n" +
               "min               : " + utils::str::to_string( min               ) + "\n" +
               "max               : " + utils::str::to_string( max               ) + "\n" +
               "nominal           : " + utils::str::to_string( nominal           ) + "\n" +
               "unbounded         : " + utils::str::to_string( unbounded         ) + "\n" +
               "start             : " + utils::str::to_string( start             ) + "\n" +
               "derivative        : " + utils::str::to_string( derivative        ) + "\n" +
               "reinit            : " + utils::str::to_string( reinit            ) + "\n" +
               "}";
    }

     // Enumeration
    std::string Enumeration::to_string(void) const
    {
        return "Enumeration { \n"
               "declaredType  : " + utils::str::to_string( declaredType  ) + "\n" +
               "quantity      : " + utils::str::to_string( quantity      ) + "\n" +
               "min           : " + utils::str::to_string( min           ) + "\n" +
               "max           : " + utils::str::to_string( max           ) + "\n" +
               "start         : " + utils::str::to_string( start         ) + "\n" +
               "}";
    }

     // SimpleTypeEnumerationItem
    std::string SimpleTypeEnumerationItem::to_string(void) const
    {
        return "SimpleTypeEnumerationItem { \n"
               "name         : " + utils::str::to_string( name         ) + "\n" +
               "value        : " + utils::str::to_string( value        ) + "\n" +
               "description  : " + utils::str::to_string( description  ) + "\n" +
               "}";
    }

     // SimpleTypeEnumeration
    std::string SimpleTypeEnumeration::to_string(void) const
    {
        return "SimpleTypeEnumeration { \n"
               "quantity  : " + utils::str::to_string( quantity  ) + "\n" +
               "Items     : " + utils::str::to_string( Items     ) + "\n" +
               "}";
    }

     // fmi2SimpleType
    std::string fmi2SimpleType::to_string(void) const
    {
        return "fmi2SimpleType { \n"
               "name         : " + utils::str::to_string( name         ) + "\n" +
               "description  : " + utils::str::to_string( description  ) + "\n" +
               "Real         : " + utils::str::to_string( Real         ) + "\n" +
               "Integer      : " + utils::str::to_string( Integer      ) + "\n" +
               "Boolean      : " + utils::str::to_string( Boolean      ) + "\n" +
               "String       : " + utils::str::to_string( String       ) + "\n" +
               "Enumeration  : " + utils::str::to_string( Enumeration  ) + "\n" +
               "}";
    }

     // TypeDefinitions
    std::string TypeDefinitions::to_string(void) const
    {
        return "TypeDefinitions { \n"
               "SimpleTypes  : " + utils::str::to_string( SimpleTypes  ) + "\n" +
               "}";
    }

     // Category
    std::string Category::to_string(void) const
    {
        return "Category { \n"
               "name         : " + utils::str::to_string( name         ) + "\n" +
               "description  : " + utils::str::to_string( description  ) + "\n" +
               "}";
    }

     // LogCategories
    std::string LogCategories::to_string(void) const
    {
        return "LogCategories { \n"
               "Categories  : " + utils::str::to_string( Categories  ) + "\n" +
               "}";
    }

     // fmi2Annotation
    std::string fmi2Annotation::to_string(void) const
    {
        return "fmi2Annotation { \n"
               "annotation  : " + utils::str::to_string( annotation  ) + "\n" +
               "}";
    }

     // VendorAnnotations
    std::string VendorAnnotations::to_string(void) const
    {
        return "VendorAnnotations { \n"
               "Annotations  : " + utils::str::to_string( Annotations  ) + "\n" +
               "}";
    }

     // DefaultExperiment
    std::string DefaultExperiment::to_string(void) const
    {
        return "DefaultExperiment { \n"
               "startTime  : " + utils::str::to_string( startTime  ) + "\n" +
               "stopTime   : " + utils::str::to_string( stopTime   ) + "\n" +
               "tolerance  : " + utils::str::to_string( tolerance  ) + "\n" +
               "stepSize   : " + utils::str::to_string( stepSize   ) + "\n" +
               "}";
    }

     // fmi2ScalarVariable
    std::string fmi2ScalarVariable::to_string(void) const
    {
        return "fmi2ScalarVariable { \n"
               "name                                : " + utils::str::to_string( name                                ) + "\n" +
               "valueReference                      : " + utils::str::to_string( valueReference                      ) + "\n" +
               "description                         : " + utils::str::to_string( description                         ) + "\n" +
               "causality                           : " + utils::str::to_string( causality                           ) + "\n" +
               "variability                         : " + utils::str::to_string( variability                         ) + "\n" +
               "initial                             : " + utils::str::to_string( initial                             ) + "\n" +
               "canHandleMultipleSetPerTimeInstant  : " + utils::str::to_string( canHandleMultipleSetPerTimeInstant  ) + "\n" +
               "Real                                : " + utils::str::to_string( Real                                ) + "\n" +
               "Integer                             : " + utils::str::to_string( Integer                             ) + "\n" +
               "Boolean                             : " + utils::str::to_string( Boolean                             ) + "\n" +
               "String                              : " + utils::str::to_string( String                              ) + "\n" +
               "Enumeration                         : " + utils::str::to_string( Enumeration                         ) + "\n" +
               "Annotations                         : " + utils::str::to_string( Annotations                         ) + "\n" +
               "}";
    }

     // Unknown
    std::string Unknown::to_string(void) const
    {
        return "Unknown { \n"
               "index             : " + utils::str::to_string( index             ) + "\n" +
               "dependencies      : " + utils::str::to_string( dependencies      ) + "\n" +
               "dependenciesKind  : " + utils::str::to_string( dependenciesKind  ) + "\n" +
               "}";
    }

     // Outputs
    std::string Outputs::to_string(void) const
    {
        return "Outputs { \n"
               "Unknowns  : " + utils::str::to_string( Unknowns  ) + "\n" +
               "}";
    }

     // Derivatives
    std::string Derivatives::to_string(void) const
    {
        return "Derivatives { \n"
               "Unknowns  : " + utils::str::to_string( Unknowns  ) + "\n" +
               "}";
    }

     // InitialUnknowns
    std::string InitialUnknowns::to_string(void) const
    {
        return "InitialUnknowns { \n"
               "Unknowns  : " + utils::str::to_string( Unknowns  ) + "\n" +
               "}";
    }

     // ModelStructure
    std::string ModelStructure::to_string(void) const
    {
        return "ModelStructure { \n"
               "Outputs          : " + utils::str::to_string( Outputs          ) + "\n" +
               "Derivatives      : " + utils::str::to_string( Derivatives      ) + "\n" +
               "InitialUnknowns  : " + utils::str::to_string( InitialUnknowns  ) + "\n" +
               "}";
    }

     // ModelVariables
    std::string ModelVariables::to_string(void) const
    {
        return "ModelVariables { \n"
               "ScalarVariable  : " + utils::str::to_string( ScalarVariable  ) + "\n" +
               "}";
    }

     // File
    std::string File::to_string(void) const
    {
        return "File { \n"
               "name  : " + utils::str::to_string( name  ) + "\n" +
               "}";
    }

     // SourceFiles
    std::string SourceFiles::to_string(void) const
    {
        return "SourceFiles { \n"
               "Files  : " + utils::str::to_string( Files  ) + "\n" +
               "}";
    }

     // ModelExchange
    std::string ModelExchange::to_string(void) const
    {
        return "ModelExchange { \n"
               "modelIdentifier                      : " + utils::str::to_string( modelIdentifier                      ) + "\n" +
               "needsExecutionTool                   : " + utils::str::to_string( needsExecutionTool                   ) + "\n" +
               "completedIntegratorStepNotNeeded     : " + utils::str::to_string( completedIntegratorStepNotNeeded     ) + "\n" +
               "canBeInstantiatedOnlyOncePerProcess  : " + utils::str::to_string( canBeInstantiatedOnlyOncePerProcess  ) + "\n" +
               "canNotUseMemoryManagementFunctions   : " + utils::str::to_string( canNotUseMemoryManagementFunctions   ) + "\n" +
               "canGetAndSetFMUstate                 : " + utils::str::to_string( canGetAndSetFMUstate                 ) + "\n" +
               "canSerializeFMUstate                 : " + utils::str::to_string( canSerializeFMUstate                 ) + "\n" +
               "providesDirectionalDerivatives       : " + utils::str::to_string( providesDirectionalDerivatives       ) + "\n" +
               "SourceFiles                          : " + utils::str::to_string( SourceFiles                          ) + "\n" +
               "}";
    }

     // CoSimulation
    std::string CoSimulation::to_string(void) const
    {
        return "CoSimulation { \n"
               "modelIdentifier                         : " + utils::str::to_string( modelIdentifier                         ) + "\n" +
               "needsExecutionTool                      : " + utils::str::to_string( needsExecutionTool                      ) + "\n" +
               "canHandleVariableCommunicationStepSize  : " + utils::str::to_string( canHandleVariableCommunicationStepSize  ) + "\n" +
               "canInterpolateInputs                    : " + utils::str::to_string( canInterpolateInputs                    ) + "\n" +
               "maxOutputDerivativeOrder                : " + utils::str::to_string( maxOutputDerivativeOrder                ) + "\n" +
               "canRunAsynchronuously                   : " + utils::str::to_string( canRunAsynchronuously                   ) + "\n" +
               "canBeInstantiatedOnlyOncePerProcess     : " + utils::str::to_string( canBeInstantiatedOnlyOncePerProcess     ) + "\n" +
               "canNotUseMemoryManagementFunctions      : " + utils::str::to_string( canNotUseMemoryManagementFunctions      ) + "\n" +
               "canGetAndSetFMUstate                    : " + utils::str::to_string( canGetAndSetFMUstate                    ) + "\n" +
               "canSerializeFMUstate                    : " + utils::str::to_string( canSerializeFMUstate                    ) + "\n" +
               "providesDirectionalDerivatives          : " + utils::str::to_string( providesDirectionalDerivatives          ) + "\n" +
               "SourceFiles                             : " + utils::str::to_string( SourceFiles                             ) + "\n" +
               "}";
    }

     // fmi2ModelDescription
    std::string fmi2ModelDescription::to_string(void) const
    {
        return "fmi2ModelDescription { \n"
               "fmiVersion                : " + utils::str::to_string( fmiVersion                ) + "\n" +
               "modelName                 : " + utils::str::to_string( modelName                 ) + "\n" +
               "guid                      : " + utils::str::to_string( guid                      ) + "\n" +
               "description               : " + utils::str::to_string( description               ) + "\n" +
               "author                    : " + utils::str::to_string( author                    ) + "\n" +
               "version                   : " + utils::str::to_string( version                   ) + "\n" +
               "copyright                 : " + utils::str::to_string( copyright                 ) + "\n" +
               "license                   : " + utils::str::to_string( license                   ) + "\n" +
               "generationTool            : " + utils::str::to_string( generationTool            ) + "\n" +
               "generationDateAndTime     : " + utils::str::to_string( generationDateAndTime     ) + "\n" +
               "variableNamingConvention  : " + utils::str::to_string( variableNamingConvention  ) + "\n" +
               "numberOfEventIndicators   : " + utils::str::to_string( numberOfEventIndicators   ) + "\n" +
               "ModelExchange             : " + utils::str::to_string( ModelExchange             ) + "\n" +
               "CoSimulation              : " + utils::str::to_string( CoSimulation              ) + "\n" +
               "UnitDefinitions           : " + utils::str::to_string( UnitDefinitions           ) + "\n" +
               "TypeDefinitions           : " + utils::str::to_string( TypeDefinitions           ) + "\n" +
               "LogCategories             : " + utils::str::to_string( LogCategories             ) + "\n" +
               "DefaultExperiment         : " + utils::str::to_string( DefaultExperiment         ) + "\n" +
               "VendorAnnotations         : " + utils::str::to_string( VendorAnnotations         ) + "\n" +
               "ModelVariables            : " + utils::str::to_string( ModelVariables            ) + "\n" +
               "ModelStructure            : " + utils::str::to_string( ModelStructure            ) + "\n" +
               "}";
    }

}
