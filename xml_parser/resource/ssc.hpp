{
    class Annotation
    {
    public:
        optional<string> annotation_type;
        optional<string> any;
    };
    string to_string(const Annotation &obj);
    string to_string(const optional<Annotation> &obj);
    string to_string(const vector<Annotation> &obj);

    class TAnnotations
    {
    public:
        vector<Annotation> list;
    };
    string to_string(const TAnnotations &obj);
    string to_string(const optional<TAnnotations> &obj);
    string to_string(const vector<TAnnotations> &obj);

    class BooleanMapEntry
    {
    public:
        bool source;
        bool target;
    };
    string to_string(const BooleanMapEntry &obj);
    string to_string(const optional<BooleanMapEntry> &obj);
    string to_string(const vector<BooleanMapEntry> &obj);

    class BooleanMappingTransformation
    {
    public:
        vector<BooleanMapEntry> list;
    };
    string to_string(const BooleanMappingTransformation &obj);
    string to_string(const optional<BooleanMappingTransformation> &obj);
    string to_string(const vector<BooleanMappingTransformation> &obj);

    class IntegerMapEntry
    {
    public:
        int source;
        int target;
    };
    string to_string(const IntegerMapEntry &obj);
    string to_string(const optional<IntegerMapEntry> &obj);
    string to_string(const vector<IntegerMapEntry> &obj);

    class IntegerMappingTransformation
    {
    public:
        vector<IntegerMapEntry> list;
    };
    string to_string(const IntegerMappingTransformation &obj);
    string to_string(const optional<IntegerMappingTransformation> &obj);
    string to_string(const vector<IntegerMappingTransformation> &obj);

    class EnumerationMapEntry
    {
    public:
        string source;
        string target;
    };
    string to_string(const EnumerationMapEntry &obj);
    string to_string(const optional<EnumerationMapEntry> &obj);
    string to_string(const vector<EnumerationMapEntry> &obj);

    class EnumerationMappingTransformation
    {
    public:
        vector<EnumerationMapEntry> list;
    };
    string to_string(const EnumerationMappingTransformation &obj);
    string to_string(const optional<EnumerationMappingTransformation> &obj);
    string to_string(const vector<EnumerationMappingTransformation> &obj);

    class TEnumerations
    {
    public:

    };
    string to_string(const TEnumerations &obj);
    string to_string(const optional<TEnumerations> &obj);
    string to_string(const vector<TEnumerations> &obj);

    class BaseUnit
    {
    public:
        optional<int> kg;
        optional<int> m;
        optional<int> s;
        optional<int> a;
        optional<int> k;
        optional<int> mol;
        optional<int> cd;
        optional<int> rad;
        optional<double> factor;
        optional<double> offset;
    };
    string to_string(const BaseUnit &obj);
    string to_string(const optional<BaseUnit> &obj);
    string to_string(const vector<BaseUnit> &obj);

    class TUnits
    {
    public:
        optional<string> id;
        optional<string> description;
        string name;
        BaseUnit baseUnit;
        optional<TAnnotations> annotations;
    };
    string to_string(const TUnits &obj);
    string to_string(const optional<TUnits> &obj);
    string to_string(const vector<TUnits> &obj);

    class GTypeReal
    {
    public:
        optional<string> unit;
    };
    string to_string(const GTypeReal &obj);
    string to_string(const optional<GTypeReal> &obj);
    string to_string(const vector<GTypeReal> &obj);

    class GTypeInteger
    {
    public:

    };
    string to_string(const GTypeInteger &obj);
    string to_string(const optional<GTypeInteger> &obj);
    string to_string(const vector<GTypeInteger> &obj);

    class GTypeBoolean
    {
    public:

    };
    string to_string(const GTypeBoolean &obj);
    string to_string(const optional<GTypeBoolean> &obj);
    string to_string(const vector<GTypeBoolean> &obj);

    class GTypeString
    {
    public:

    };
    string to_string(const GTypeString &obj);
    string to_string(const optional<GTypeString> &obj);
    string to_string(const vector<GTypeString> &obj);

    class GTypeEnumeration
    {
    public:
        optional<string> name;
    };
    string to_string(const GTypeEnumeration &obj);
    string to_string(const optional<GTypeEnumeration> &obj);
    string to_string(const vector<GTypeEnumeration> &obj);

    class GTypeBinary
    {
    public:
        optional<string> mime_type;
    };
    string to_string(const GTypeBinary &obj);
    string to_string(const optional<GTypeBinary> &obj);
    string to_string(const vector<GTypeBinary> &obj);

    class LinearTransformation
    {
    public:
        optional<double> factor;
        optional<double> offset;
    };
    string to_string(const LinearTransformation &obj);
    string to_string(const optional<LinearTransformation> &obj);
    string to_string(const vector<LinearTransformation> &obj);
}