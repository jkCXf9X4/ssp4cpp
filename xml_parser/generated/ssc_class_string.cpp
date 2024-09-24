{
     // Annotation
    string Annotation::to_string(void) const
    {
        return "Annotation { \n"
               "type  : " + to_str( type  ) + "\n" +
               "any   : " + to_str( any   ) + "\n" +
               "}";
    }

     // TAnnotations
    string TAnnotations::to_string(void) const
    {
        return "TAnnotations { \n"
               "Annotations  : " + to_str( Annotations  ) + "\n" +
               "}";
    }

     // LinearTransformation
    string LinearTransformation::to_string(void) const
    {
        return "LinearTransformation { \n"
               "factor  : " + to_str( factor  ) + "\n" +
               "offset  : " + to_str( offset  ) + "\n" +
               "}";
    }

     // BooleanMapEntry
    string BooleanMapEntry::to_string(void) const
    {
        return "BooleanMapEntry { \n"
               "source  : " + to_str( source  ) + "\n" +
               "target  : " + to_str( target  ) + "\n" +
               "}";
    }

     // BooleanMappingTransformation
    string BooleanMappingTransformation::to_string(void) const
    {
        return "BooleanMappingTransformation { \n"
               "MapEntrys  : " + to_str( MapEntrys  ) + "\n" +
               "}";
    }

     // IntegerMapEntry
    string IntegerMapEntry::to_string(void) const
    {
        return "IntegerMapEntry { \n"
               "source  : " + to_str( source  ) + "\n" +
               "target  : " + to_str( target  ) + "\n" +
               "}";
    }

     // IntegerMappingTransformation
    string IntegerMappingTransformation::to_string(void) const
    {
        return "IntegerMappingTransformation { \n"
               "MapEntrys  : " + to_str( MapEntrys  ) + "\n" +
               "}";
    }

     // EnumerationMapEntry
    string EnumerationMapEntry::to_string(void) const
    {
        return "EnumerationMapEntry { \n"
               "source  : " + to_str( source  ) + "\n" +
               "target  : " + to_str( target  ) + "\n" +
               "}";
    }

     // EnumerationMappingTransformation
    string EnumerationMappingTransformation::to_string(void) const
    {
        return "EnumerationMappingTransformation { \n"
               "MapEntrys  : " + to_str( MapEntrys  ) + "\n" +
               "}";
    }

     // Item
    string Item::to_string(void) const
    {
        return "Item { \n"
               "name   : " + to_str( name   ) + "\n" +
               "value  : " + to_str( value  ) + "\n" +
               "}";
    }

     // TEnumeration
    string TEnumeration::to_string(void) const
    {
        return "TEnumeration { \n"
               "id           : " + to_str( id           ) + "\n" +
               "description  : " + to_str( description  ) + "\n" +
               "name         : " + to_str( name         ) + "\n" +
               "Item         : " + to_str( Item         ) + "\n" +
               "Annotations  : " + to_str( Annotations  ) + "\n" +
               "}";
    }

     // TEnumerations
    string TEnumerations::to_string(void) const
    {
        return "TEnumerations { \n"
               "Enumerations  : " + to_str( Enumerations  ) + "\n" +
               "}";
    }

     // BaseUnit
    string BaseUnit::to_string(void) const
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

     // TUnit
    string TUnit::to_string(void) const
    {
        return "TUnit { \n"
               "id           : " + to_str( id           ) + "\n" +
               "description  : " + to_str( description  ) + "\n" +
               "name         : " + to_str( name         ) + "\n" +
               "BaseUnit     : " + to_str( BaseUnit     ) + "\n" +
               "Annotations  : " + to_str( Annotations  ) + "\n" +
               "}";
    }

     // TUnits
    string TUnits::to_string(void) const
    {
        return "TUnits { \n"
               "Units  : " + to_str( Units  ) + "\n" +
               "}";
    }

     // GTypeReal
    string GTypeReal::to_string(void) const
    {
        return "GTypeReal { \n"
               "unit  : " + to_str( unit  ) + "\n" +
               "}";
    }

     // GTypeInteger
    string GTypeInteger::to_string(void) const
    {
        return "GTypeInteger { \n"

               "}";
    }

     // GTypeBoolean
    string GTypeBoolean::to_string(void) const
    {
        return "GTypeBoolean { \n"

               "}";
    }

     // GTypeString
    string GTypeString::to_string(void) const
    {
        return "GTypeString { \n"

               "}";
    }

     // GTypeEnumeration
    string GTypeEnumeration::to_string(void) const
    {
        return "GTypeEnumeration { \n"
               "name  : " + to_str( name  ) + "\n" +
               "}";
    }

     // GTypeBinary
    string GTypeBinary::to_string(void) const
    {
        return "GTypeBinary { \n"
               "mime_type  : " + to_str( mime_type  ) + "\n" +
               "}";
    }


}
