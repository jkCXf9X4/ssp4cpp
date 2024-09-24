{

    void from_xml(const xml_node &node, BaseUnit &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing BaseUnit" << std::endl;

        parse_xml(node, obj.kg      , "kg");
        parse_xml(node, obj.m       , "m");
        parse_xml(node, obj.s       , "s");
        parse_xml(node, obj.a       , "a");
        parse_xml(node, obj.k       , "k");
        parse_xml(node, obj.mol     , "mol");
        parse_xml(node, obj.cd      , "cd");
        parse_xml(node, obj.rad     , "rad");
        parse_xml(node, obj.factor  , "factor");
        parse_xml(node, obj.offset  , "offset");

        BOOST_LOG_TRIVIAL(trace) << "Completed BaseUnit" << std::endl;
    }

    void from_xml(const xml_node &node, DisplayUnit &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing DisplayUnit" << std::endl;

        parse_xml(node, obj.name    , "name");
        parse_xml(node, obj.factor  , "factor");
        parse_xml(node, obj.offset  , "offset");

        BOOST_LOG_TRIVIAL(trace) << "Completed DisplayUnit" << std::endl;
    }

    void from_xml(const xml_node &node, fmi2Unit &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing fmi2Unit" << std::endl;

        parse_xml(node, obj.name         , "name");
        parse_xml(node, obj.BaseUnit     , "BaseUnit");
        parse_xml(node, obj.DisplayUnit  , "DisplayUnit");

        BOOST_LOG_TRIVIAL(trace) << "Completed fmi2Unit" << std::endl;
    }

    void from_xml(const xml_node &node, UnitDefinitions &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing UnitDefinitions" << std::endl;

        parse_xml(node, obj.Units  , "Unit");

        BOOST_LOG_TRIVIAL(trace) << "Completed UnitDefinitions" << std::endl;
    }

    void from_xml(const xml_node &node, Boolean &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Boolean" << std::endl;

        parse_xml(node, obj.declaredType  , "declaredType");
        parse_xml(node, obj.start         , "start");

        BOOST_LOG_TRIVIAL(trace) << "Completed Boolean" << std::endl;
    }

    void from_xml(const xml_node &node, Integer &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Integer" << std::endl;

        parse_xml(node, obj.declaredType  , "declaredType");
        parse_xml(node, obj.start         , "start");
        parse_xml(node, obj.quantity      , "quantity");
        parse_xml(node, obj.min           , "min");
        parse_xml(node, obj.max           , "max");

        BOOST_LOG_TRIVIAL(trace) << "Completed Integer" << std::endl;
    }

    void from_xml(const xml_node &node, String &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing String" << std::endl;

        parse_xml(node, obj.declaredType  , "declaredType");
        parse_xml(node, obj.start         , "start");

        BOOST_LOG_TRIVIAL(trace) << "Completed String" << std::endl;
    }

    void from_xml(const xml_node &node, Real &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Real" << std::endl;

        parse_xml(node, obj.declaredType      , "declaredType");
        parse_xml(node, obj.quantity          , "quantity");
        parse_xml(node, obj.unit              , "unit");
        parse_xml(node, obj.displayUnit       , "displayUnit");
        parse_xml(node, obj.relativeQuantity  , "relativeQuantity");
        parse_xml(node, obj.min               , "min");
        parse_xml(node, obj.max               , "max");
        parse_xml(node, obj.nominal           , "nominal");
        parse_xml(node, obj.unbounded         , "unbounded");
        parse_xml(node, obj.start             , "start");
        parse_xml(node, obj.derivative        , "derivative");
        parse_xml(node, obj.reinit            , "reinit");

        BOOST_LOG_TRIVIAL(trace) << "Completed Real" << std::endl;
    }

    void from_xml(const xml_node &node, Enumeration &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Enumeration" << std::endl;

        parse_xml(node, obj.declaredType  , "declaredType");
        parse_xml(node, obj.quantity      , "quantity");
        parse_xml(node, obj.min           , "min");
        parse_xml(node, obj.max           , "max");
        parse_xml(node, obj.start         , "start");

        BOOST_LOG_TRIVIAL(trace) << "Completed Enumeration" << std::endl;
    }

    void from_xml(const xml_node &node, SimpleTypeEnumerationItem &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing SimpleTypeEnumerationItem" << std::endl;

        parse_xml(node, obj.name         , "name");
        parse_xml(node, obj.value        , "value");
        parse_xml(node, obj.description  , "description");

        BOOST_LOG_TRIVIAL(trace) << "Completed SimpleTypeEnumerationItem" << std::endl;
    }

    void from_xml(const xml_node &node, SimpleTypeEnumeration &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing SimpleTypeEnumeration" << std::endl;

        parse_xml(node, obj.quantity  , "quantity");
        parse_xml(node, obj.Items     , "Item");

        BOOST_LOG_TRIVIAL(trace) << "Completed SimpleTypeEnumeration" << std::endl;
    }

    void from_xml(const xml_node &node, fmi2SimpleType &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing fmi2SimpleType" << std::endl;

        parse_xml(node, obj.name         , "name");
        parse_xml(node, obj.description  , "description");
        parse_xml(node, obj.Real         , "Real");
        parse_xml(node, obj.Integer      , "Integer");
        parse_xml(node, obj.Boolean      , "Boolean");
        parse_xml(node, obj.String       , "String");
        parse_xml(node, obj.Enumeration  , "Enumeration");

        BOOST_LOG_TRIVIAL(trace) << "Completed fmi2SimpleType" << std::endl;
    }

    void from_xml(const xml_node &node, TypeDefinitions &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TypeDefinitions" << std::endl;

        parse_xml(node, obj.SimpleTypes  , "SimpleType");

        BOOST_LOG_TRIVIAL(trace) << "Completed TypeDefinitions" << std::endl;
    }

    void from_xml(const xml_node &node, Category &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Category" << std::endl;

        parse_xml(node, obj.name         , "name");
        parse_xml(node, obj.description  , "description");

        BOOST_LOG_TRIVIAL(trace) << "Completed Category" << std::endl;
    }

    void from_xml(const xml_node &node, LogCategories &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing LogCategories" << std::endl;

        parse_xml(node, obj.Categories  , "Category");

        BOOST_LOG_TRIVIAL(trace) << "Completed LogCategories" << std::endl;
    }

    void from_xml(const xml_node &node, fmi2Annotation &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing fmi2Annotation" << std::endl;

        parse_xml(node, obj.annotation  , "annotation");

        BOOST_LOG_TRIVIAL(trace) << "Completed fmi2Annotation" << std::endl;
    }

    void from_xml(const xml_node &node, VendorAnnotations &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing VendorAnnotations" << std::endl;

        parse_xml(node, obj.Annotations  , "Annotation");

        BOOST_LOG_TRIVIAL(trace) << "Completed VendorAnnotations" << std::endl;
    }

    void from_xml(const xml_node &node, DefaultExperiment &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing DefaultExperiment" << std::endl;

        parse_xml(node, obj.startTime  , "startTime");
        parse_xml(node, obj.stopTime   , "stopTime");
        parse_xml(node, obj.tolerance  , "tolerance");
        parse_xml(node, obj.stepSize   , "stepSize");

        BOOST_LOG_TRIVIAL(trace) << "Completed DefaultExperiment" << std::endl;
    }

    void from_xml(const xml_node &node, fmi2ScalarVariable &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing fmi2ScalarVariable" << std::endl;

        parse_xml(node, obj.name                                , "name");
        parse_xml(node, obj.valueReference                      , "valueReference");
        parse_xml(node, obj.description                         , "description");
        parse_xml(node, obj.causality                           , "causality");
        parse_xml(node, obj.variability                         , "variability");
        parse_xml(node, obj.initial                             , "initial");
        parse_xml(node, obj.canHandleMultipleSetPerTimeInstant  , "canHandleMultipleSetPerTimeInstant");
        parse_xml(node, obj.Real                                , "Real");
        parse_xml(node, obj.Integer                             , "Integer");
        parse_xml(node, obj.Boolean                             , "Boolean");
        parse_xml(node, obj.String                              , "String");
        parse_xml(node, obj.Enumeration                         , "Enumeration");
        parse_xml(node, obj.Annotations                         , "Annotation");

        BOOST_LOG_TRIVIAL(trace) << "Completed fmi2ScalarVariable" << std::endl;
    }

    void from_xml(const xml_node &node, Unknown &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Unknown" << std::endl;

        parse_xml(node, obj.index             , "index");
        parse_xml(node, obj.dependencies      , "dependencies");
        parse_xml(node, obj.dependenciesKind  , "dependenciesKind");

        BOOST_LOG_TRIVIAL(trace) << "Completed Unknown" << std::endl;
    }

    void from_xml(const xml_node &node, Outputs &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Outputs" << std::endl;

        parse_xml(node, obj.Unknowns  , "Unknown");

        BOOST_LOG_TRIVIAL(trace) << "Completed Outputs" << std::endl;
    }

    void from_xml(const xml_node &node, Derivatives &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Derivatives" << std::endl;

        parse_xml(node, obj.Unknowns  , "Unknown");

        BOOST_LOG_TRIVIAL(trace) << "Completed Derivatives" << std::endl;
    }

    void from_xml(const xml_node &node, InitialUnknowns &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing InitialUnknowns" << std::endl;

        parse_xml(node, obj.Unknowns  , "Unknown");

        BOOST_LOG_TRIVIAL(trace) << "Completed InitialUnknowns" << std::endl;
    }

    void from_xml(const xml_node &node, ModelStructure &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing ModelStructure" << std::endl;

        parse_xml(node, obj.Outputs          , "Outputs");
        parse_xml(node, obj.Derivatives      , "Derivatives");
        parse_xml(node, obj.InitialUnknowns  , "InitialUnknowns");

        BOOST_LOG_TRIVIAL(trace) << "Completed ModelStructure" << std::endl;
    }

    void from_xml(const xml_node &node, ModelVariables &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing ModelVariables" << std::endl;

        parse_xml(node, obj.ScalarVariable  , "ScalarVariable");

        BOOST_LOG_TRIVIAL(trace) << "Completed ModelVariables" << std::endl;
    }

    void from_xml(const xml_node &node, File &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing File" << std::endl;

        parse_xml(node, obj.name  , "name");

        BOOST_LOG_TRIVIAL(trace) << "Completed File" << std::endl;
    }

    void from_xml(const xml_node &node, SourceFiles &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing SourceFiles" << std::endl;

        parse_xml(node, obj.Files  , "File");

        BOOST_LOG_TRIVIAL(trace) << "Completed SourceFiles" << std::endl;
    }

    void from_xml(const xml_node &node, ModelExchange &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing ModelExchange" << std::endl;

        parse_xml(node, obj.modelIdentifier                      , "modelIdentifier");
        parse_xml(node, obj.needsExecutionTool                   , "needsExecutionTool");
        parse_xml(node, obj.completedIntegratorStepNotNeeded     , "completedIntegratorStepNotNeeded");
        parse_xml(node, obj.canBeInstantiatedOnlyOncePerProcess  , "canBeInstantiatedOnlyOncePerProcess");
        parse_xml(node, obj.canNotUseMemoryManagementFunctions   , "canNotUseMemoryManagementFunctions");
        parse_xml(node, obj.canGetAndSetFMUstate                 , "canGetAndSetFMUstate");
        parse_xml(node, obj.canSerializeFMUstate                 , "canSerializeFMUstate");
        parse_xml(node, obj.providesDirectionalDerivatives       , "providesDirectionalDerivatives");
        parse_xml(node, obj.SourceFiles                          , "SourceFiles");

        BOOST_LOG_TRIVIAL(trace) << "Completed ModelExchange" << std::endl;
    }

    void from_xml(const xml_node &node, CoSimulation &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing CoSimulation" << std::endl;

        parse_xml(node, obj.modelIdentifier                         , "modelIdentifier");
        parse_xml(node, obj.needsExecutionTool                      , "needsExecutionTool");
        parse_xml(node, obj.canHandleVariableCommunicationStepSize  , "canHandleVariableCommunicationStepSize");
        parse_xml(node, obj.canInterpolateInputs                    , "canInterpolateInputs");
        parse_xml(node, obj.maxOutputDerivativeOrder                , "maxOutputDerivativeOrder");
        parse_xml(node, obj.canRunAsynchronuously                   , "canRunAsynchronuously");
        parse_xml(node, obj.canBeInstantiatedOnlyOncePerProcess     , "canBeInstantiatedOnlyOncePerProcess");
        parse_xml(node, obj.canNotUseMemoryManagementFunctions      , "canNotUseMemoryManagementFunctions");
        parse_xml(node, obj.canGetAndSetFMUstate                    , "canGetAndSetFMUstate");
        parse_xml(node, obj.canSerializeFMUstate                    , "canSerializeFMUstate");
        parse_xml(node, obj.providesDirectionalDerivatives          , "providesDirectionalDerivatives");
        parse_xml(node, obj.SourceFiles                             , "SourceFiles");

        BOOST_LOG_TRIVIAL(trace) << "Completed CoSimulation" << std::endl;
    }

    void from_xml(const xml_node &node, fmi2ModelDescription &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing fmi2ModelDescription" << std::endl;

        parse_xml(node, obj.fmiVersion                , "fmiVersion");
        parse_xml(node, obj.modelName                 , "modelName");
        parse_xml(node, obj.guid                      , "guid");
        parse_xml(node, obj.description               , "description");
        parse_xml(node, obj.author                    , "author");
        parse_xml(node, obj.version                   , "version");
        parse_xml(node, obj.copyright                 , "copyright");
        parse_xml(node, obj.license                   , "license");
        parse_xml(node, obj.generationTool            , "generationTool");
        parse_xml(node, obj.generationDateAndTime     , "generationDateAndTime");
        parse_xml(node, obj.variableNamingConvention  , "variableNamingConvention");
        parse_xml(node, obj.numberOfEventIndicators   , "numberOfEventIndicators");
        parse_xml(node, obj.ModelExchange             , "ModelExchange");
        parse_xml(node, obj.CoSimulation              , "CoSimulation");
        parse_xml(node, obj.UnitDefinitions           , "UnitDefinitions");
        parse_xml(node, obj.TypeDefinitions           , "TypeDefinitions");
        parse_xml(node, obj.LogCategories             , "LogCategories");
        parse_xml(node, obj.DefaultExperiment         , "DefaultExperiment");
        parse_xml(node, obj.VendorAnnotations         , "VendorAnnotations");
        parse_xml(node, obj.ModelVariables            , "ModelVariables");
        parse_xml(node, obj.ModelStructure            , "ModelStructure");

        BOOST_LOG_TRIVIAL(trace) << "Completed fmi2ModelDescription" << std::endl;
    }

}
