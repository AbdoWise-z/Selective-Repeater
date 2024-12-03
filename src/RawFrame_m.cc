//
// Generated file, do not edit! Created by opp_msgtool 6.0 from RawFrame.msg.
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
#include "RawFrame_m.h"

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

RawFrame_Base::RawFrame_Base(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

RawFrame_Base::RawFrame_Base(const RawFrame_Base& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

RawFrame_Base::~RawFrame_Base()
{
}

RawFrame_Base& RawFrame_Base::operator=(const RawFrame_Base& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

RawFrame_Base* RawFrame_Base::dup() const
{
    RawFrame_Base* b = new RawFrame_Base();
    b->M_Target = this->M_Target;
    b->M_Trailer = this->M_Trailer;
    b->M_Type = this->M_Type;
    b->M_header = this->M_header;
    b->M_payload = this->M_payload;

    b->modified_bit = this->modified_bit;
    b->channel_delay = this->channel_delay;
    b->dup_index = this->dup_index;
    b->is_lost = this->is_lost;
    return b;
}

void RawFrame_Base::copy(const RawFrame_Base& other)
{
    this->M_header = other.M_header;
    this->M_payload = other.M_payload;
    this->M_Trailer = other.M_Trailer;
    this->M_Type = other.M_Type;
    this->M_Target = other.M_Target;
    this->dup_index = other.dup_index;
    this->modified_bit = other.modified_bit;
    this->is_lost = other.is_lost;
    this->channel_delay = other.channel_delay;
}

void RawFrame_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->M_header);
    doParsimPacking(b,this->M_payload);
    doParsimPacking(b,this->M_Trailer);
    doParsimPacking(b,this->M_Type);
    doParsimPacking(b,this->M_Target);
    doParsimPacking(b,this->dup_index);
    doParsimPacking(b,this->modified_bit);
    doParsimPacking(b,this->is_lost);
    doParsimPacking(b,this->channel_delay);
}

void RawFrame_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->M_header);
    doParsimUnpacking(b,this->M_payload);
    doParsimUnpacking(b,this->M_Trailer);
    doParsimUnpacking(b,this->M_Type);
    doParsimUnpacking(b,this->M_Target);
    doParsimUnpacking(b,this->dup_index);
    doParsimUnpacking(b,this->modified_bit);
    doParsimUnpacking(b,this->is_lost);
    doParsimUnpacking(b,this->channel_delay);
}

int RawFrame_Base::getM_header() const
{
    return this->M_header;
}

void RawFrame_Base::setM_header(int M_header)
{
    this->M_header = M_header;
}

const char * RawFrame_Base::getM_payload() const
{
    return this->M_payload.c_str();
}

void RawFrame_Base::setM_payload(const char * M_payload)
{
    this->M_payload = M_payload;
}

const char * RawFrame_Base::getM_Trailer() const
{
    return this->M_Trailer.c_str();
}

void RawFrame_Base::setM_Trailer(const char * M_Trailer)
{
    this->M_Trailer = M_Trailer;
}

int RawFrame_Base::getM_Type() const
{
    return this->M_Type;
}

void RawFrame_Base::setM_Type(int M_Type)
{
    this->M_Type = M_Type;
}

int RawFrame_Base::getM_Target() const
{
    return this->M_Target;
}

void RawFrame_Base::setM_Target(int M_Target)
{
    this->M_Target = M_Target;
}

int RawFrame_Base::getDup_index() const
{
    return this->dup_index;
}

void RawFrame_Base::setDup_index(int dup_index)
{
    this->dup_index = dup_index;
}

int RawFrame_Base::getModified_bit() const
{
    return this->modified_bit;
}

void RawFrame_Base::setModified_bit(int modified_bit)
{
    this->modified_bit = modified_bit;
}

bool RawFrame_Base::getIs_lost() const
{
    return this->is_lost;
}

void RawFrame_Base::setIs_lost(bool is_lost)
{
    this->is_lost = is_lost;
}

double RawFrame_Base::getChannel_delay() const
{
    return this->channel_delay;
}

void RawFrame_Base::setChannel_delay(double channel_delay)
{
    this->channel_delay = channel_delay;
}

class RawFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_M_header,
        FIELD_M_payload,
        FIELD_M_Trailer,
        FIELD_M_Type,
        FIELD_M_Target,
        FIELD_dup_index,
        FIELD_modified_bit,
        FIELD_is_lost,
        FIELD_channel_delay,
    };
  public:
    RawFrameDescriptor();
    virtual ~RawFrameDescriptor();

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

Register_ClassDescriptor(RawFrameDescriptor)

RawFrameDescriptor::RawFrameDescriptor() : omnetpp::cClassDescriptor("RawFrame", "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

RawFrameDescriptor::~RawFrameDescriptor()
{
    delete[] propertyNames;
}

bool RawFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RawFrame_Base *>(obj)!=nullptr;
}

const char **RawFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RawFrameDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "customize")) return "true";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RawFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 9+base->getFieldCount() : 9;
}

unsigned int RawFrameDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISEDITABLE,    // FIELD_dup_index
        FD_ISEDITABLE,    // FIELD_modified_bit
        FD_ISEDITABLE,    // FIELD_is_lost
        FD_ISEDITABLE,    // FIELD_channel_delay
    };
    return (field >= 0 && field < 9) ? fieldTypeFlags[field] : 0;
}

const char *RawFrameDescriptor::getFieldName(int field) const
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
        "dup_index",
        "modified_bit",
        "is_lost",
        "channel_delay",
    };
    return (field >= 0 && field < 9) ? fieldNames[field] : nullptr;
}

int RawFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "M_header") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "M_payload") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "M_Trailer") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "M_Type") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "M_Target") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "dup_index") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "modified_bit") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "is_lost") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "channel_delay") == 0) return baseIndex + 8;
    return base ? base->findField(fieldName) : -1;
}

const char *RawFrameDescriptor::getFieldTypeString(int field) const
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
        "int",    // FIELD_dup_index
        "int",    // FIELD_modified_bit
        "bool",    // FIELD_is_lost
        "double",    // FIELD_channel_delay
    };
    return (field >= 0 && field < 9) ? fieldTypeStrings[field] : nullptr;
}

const char **RawFrameDescriptor::getFieldPropertyNames(int field) const
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

const char *RawFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RawFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RawFrame_Base *pp = omnetpp::fromAnyPtr<RawFrame_Base>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RawFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RawFrame_Base *pp = omnetpp::fromAnyPtr<RawFrame_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RawFrame_Base'", field);
    }
}

const char *RawFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RawFrame_Base *pp = omnetpp::fromAnyPtr<RawFrame_Base>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RawFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RawFrame_Base *pp = omnetpp::fromAnyPtr<RawFrame_Base>(object); (void)pp;
    switch (field) {
        case FIELD_M_header: return long2string(pp->getM_header());
        case FIELD_M_payload: return oppstring2string(pp->getM_payload());
        case FIELD_M_Trailer: return oppstring2string(pp->getM_Trailer());
        case FIELD_M_Type: return long2string(pp->getM_Type());
        case FIELD_M_Target: return long2string(pp->getM_Target());
        case FIELD_dup_index: return long2string(pp->getDup_index());
        case FIELD_modified_bit: return long2string(pp->getModified_bit());
        case FIELD_is_lost: return bool2string(pp->getIs_lost());
        case FIELD_channel_delay: return double2string(pp->getChannel_delay());
        default: return "";
    }
}

void RawFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RawFrame_Base *pp = omnetpp::fromAnyPtr<RawFrame_Base>(object); (void)pp;
    switch (field) {
        case FIELD_M_header: pp->setM_header(string2long(value)); break;
        case FIELD_M_payload: pp->setM_payload((value)); break;
        case FIELD_M_Trailer: pp->setM_Trailer((value)); break;
        case FIELD_M_Type: pp->setM_Type(string2long(value)); break;
        case FIELD_M_Target: pp->setM_Target(string2long(value)); break;
        case FIELD_dup_index: pp->setDup_index(string2long(value)); break;
        case FIELD_modified_bit: pp->setModified_bit(string2long(value)); break;
        case FIELD_is_lost: pp->setIs_lost(string2bool(value)); break;
        case FIELD_channel_delay: pp->setChannel_delay(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RawFrame_Base'", field);
    }
}

omnetpp::cValue RawFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RawFrame_Base *pp = omnetpp::fromAnyPtr<RawFrame_Base>(object); (void)pp;
    switch (field) {
        case FIELD_M_header: return pp->getM_header();
        case FIELD_M_payload: return pp->getM_payload();
        case FIELD_M_Trailer: return pp->getM_Trailer();
        case FIELD_M_Type: return pp->getM_Type();
        case FIELD_M_Target: return pp->getM_Target();
        case FIELD_dup_index: return pp->getDup_index();
        case FIELD_modified_bit: return pp->getModified_bit();
        case FIELD_is_lost: return pp->getIs_lost();
        case FIELD_channel_delay: return pp->getChannel_delay();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RawFrame_Base' as cValue -- field index out of range?", field);
    }
}

void RawFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RawFrame_Base *pp = omnetpp::fromAnyPtr<RawFrame_Base>(object); (void)pp;
    switch (field) {
        case FIELD_M_header: pp->setM_header(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_M_payload: pp->setM_payload(value.stringValue()); break;
        case FIELD_M_Trailer: pp->setM_Trailer(value.stringValue()); break;
        case FIELD_M_Type: pp->setM_Type(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_M_Target: pp->setM_Target(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_dup_index: pp->setDup_index(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_modified_bit: pp->setModified_bit(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_is_lost: pp->setIs_lost(value.boolValue()); break;
        case FIELD_channel_delay: pp->setChannel_delay(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RawFrame_Base'", field);
    }
}

const char *RawFrameDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RawFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RawFrame_Base *pp = omnetpp::fromAnyPtr<RawFrame_Base>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RawFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RawFrame_Base *pp = omnetpp::fromAnyPtr<RawFrame_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RawFrame_Base'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

