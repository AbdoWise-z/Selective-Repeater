//
// Generated file, do not edit! Created by opp_msgtool 6.0 from Frame.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "Frame_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Frame_Base::Frame_Base(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

Frame_Base::Frame_Base(const Frame_Base& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

Frame_Base::~Frame_Base()
{
}

Frame_Base& Frame_Base::operator=(const Frame_Base& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void Frame_Base::copy(const Frame_Base& other)
{
    this->M_header = other.M_header;
    this->M_payload = other.M_payload;
    this->M_Trailer = other.M_Trailer;
    this->M_Type = other.M_Type;
    this->M_Target = other.M_Target;
}

void Frame_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->M_header);
    doParsimPacking(b,this->M_payload);
    doParsimPacking(b,this->M_Trailer);
    doParsimPacking(b,this->M_Type);
    doParsimPacking(b,this->M_Target);
}

void Frame_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->M_header);
    doParsimUnpacking(b,this->M_payload);
    doParsimUnpacking(b,this->M_Trailer);
    doParsimUnpacking(b,this->M_Type);
    doParsimUnpacking(b,this->M_Target);
}

Frame_Base* Frame_Base::dup() const
{
    Frame_Base* b = new Frame_Base();
    b->M_Target = this->M_Target;
    b->M_Trailer = this->M_Trailer;
    b->M_Type = this->M_Type;
    b->M_header = this->M_header;
    b->M_payload = this->M_payload;
    return b;
}

int Frame_Base::getM_header() const
{
    return this->M_header;
}

void Frame_Base::setM_header(int M_header)
{
    this->M_header = M_header;
}

const char * Frame_Base::getM_payload() const
{
    return this->M_payload.c_str();
}

void Frame_Base::setM_payload(const char * M_payload)
{
    this->M_payload = M_payload;
}

const char * Frame_Base::getM_Trailer() const
{
    return this->M_Trailer.c_str();
}

void Frame_Base::setM_Trailer(const char * M_Trailer)
{
    this->M_Trailer = M_Trailer;
}

int Frame_Base::getM_Type() const
{
    return this->M_Type;
}

void Frame_Base::setM_Type(int M_Type)
{
    this->M_Type = M_Type;
}

int Frame_Base::getM_Target() const
{
    return this->M_Target;
}

void Frame_Base::setM_Target(int M_Target)
{
    this->M_Target = M_Target;
}

class FrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_M_header,
        FIELD_M_payload,
        FIELD_M_Trailer,
        FIELD_M_Type,
        FIELD_M_Target,
    };
  public:
    FrameDescriptor();
    virtual ~FrameDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(FrameDescriptor)

FrameDescriptor::FrameDescriptor() : omnetpp::cClassDescriptor("Frame", "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

FrameDescriptor::~FrameDescriptor()
{
    delete[] propertyNames;
}

bool FrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Frame_Base *>(obj)!=nullptr;
}

const char **FrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *FrameDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "customize")) return "true";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int FrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int FrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_M_header
        FD_ISEDITABLE,    // FIELD_M_payload
        FD_ISEDITABLE,    // FIELD_M_Trailer
        FD_ISEDITABLE,    // FIELD_M_Type
        FD_ISEDITABLE,    // FIELD_M_Target
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *FrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "M_header",
        "M_payload",
        "M_Trailer",
        "M_Type",
        "M_Target",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int FrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "M_header") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "M_payload") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "M_Trailer") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "M_Type") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "M_Target") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *FrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_M_header
        "string",    // FIELD_M_payload
        "string",    // FIELD_M_Trailer
        "int",    // FIELD_M_Type
        "int",    // FIELD_M_Target
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **FrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *FrameDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int FrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Frame_Base *pp = omnetpp::fromAnyPtr<Frame_Base>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void FrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Frame_Base *pp = omnetpp::fromAnyPtr<Frame_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Frame_Base'", field);
    }
}

const char *FrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Frame_Base *pp = omnetpp::fromAnyPtr<Frame_Base>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Frame_Base *pp = omnetpp::fromAnyPtr<Frame_Base>(object); (void)pp;
    switch (field) {
        case FIELD_M_header: return long2string(pp->getM_header());
        case FIELD_M_payload: return oppstring2string(pp->getM_payload());
        case FIELD_M_Trailer: return oppstring2string(pp->getM_Trailer());
        case FIELD_M_Type: return long2string(pp->getM_Type());
        case FIELD_M_Target: return long2string(pp->getM_Target());
        default: return "";
    }
}

void FrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Frame_Base *pp = omnetpp::fromAnyPtr<Frame_Base>(object); (void)pp;
    switch (field) {
        case FIELD_M_header: pp->setM_header(string2long(value)); break;
        case FIELD_M_payload: pp->setM_payload((value)); break;
        case FIELD_M_Trailer: pp->setM_Trailer((value)); break;
        case FIELD_M_Type: pp->setM_Type(string2long(value)); break;
        case FIELD_M_Target: pp->setM_Target(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Frame_Base'", field);
    }
}

omnetpp::cValue FrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Frame_Base *pp = omnetpp::fromAnyPtr<Frame_Base>(object); (void)pp;
    switch (field) {
        case FIELD_M_header: return pp->getM_header();
        case FIELD_M_payload: return pp->getM_payload();
        case FIELD_M_Trailer: return pp->getM_Trailer();
        case FIELD_M_Type: return pp->getM_Type();
        case FIELD_M_Target: return pp->getM_Target();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Frame_Base' as cValue -- field index out of range?", field);
    }
}

void FrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Frame_Base *pp = omnetpp::fromAnyPtr<Frame_Base>(object); (void)pp;
    switch (field) {
        case FIELD_M_header: pp->setM_header(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_M_payload: pp->setM_payload(value.stringValue()); break;
        case FIELD_M_Trailer: pp->setM_Trailer(value.stringValue()); break;
        case FIELD_M_Type: pp->setM_Type(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_M_Target: pp->setM_Target(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Frame_Base'", field);
    }
}

const char *FrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr FrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Frame_Base *pp = omnetpp::fromAnyPtr<Frame_Base>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void FrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Frame_Base *pp = omnetpp::fromAnyPtr<Frame_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Frame_Base'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

