//
// Generated file, do not edit! Created by opp_msgtool 6.0 from Frame.msg.
//

#ifndef __FRAME_M_H
#define __FRAME_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class Frame;
/**
 * Class generated from <tt>Frame.msg:17</tt> by opp_msgtool.
 * <pre>
 * packet Frame
 * {
 *     \@customize(true);
 *     int M_header;        // the seuqnce number
 *     string M_payload;    // the message content
 *     string M_Trailer;    // the CRC
 *     int M_Type;          // type: 2 = Data, 1 = ACK, 0 = NACK
 *     int M_Target;        // target ACK / NACK value
 * }
 * </pre>
 *
 * Frame_Base is only useful if it gets subclassed, and Frame is derived from it.
 * The minimum code to be written for Frame is the following:
 *
 * <pre>
 * class Frame : public Frame_Base
 * {
 *   private:
 *     void copy(const Frame& other) { ... }

 *   public:
 *     Frame(const char *name=nullptr, short kind=0) : Frame_Base(name,kind) {}
 *     Frame(const Frame& other) : Frame_Base(other) {copy(other);}
 *     Frame& operator=(const Frame& other) {if (this==&other) return *this; Frame_Base::operator=(other); copy(other); return *this;}
 *     virtual Frame *dup() const override {return new Frame(*this);}
 *     // ADD CODE HERE to redefine and implement pure virtual functions from Frame_Base
 * };
 * </pre>
 *
 * The following should go into a .cc (.cpp) file:
 *
 * <pre>
 * Register_Class(Frame)
 * </pre>
 */
class Frame_Base : public ::omnetpp::cPacket
{
  protected:
    int M_header = 0;  // sequence number
    omnetpp::opp_string M_payload; // message in binary
    omnetpp::opp_string M_Trailer; // CRC check
    int M_Type = 0;    // 0 -> data, 1 -> ACK, 2 -> NACK
    int M_Target = 0;  // ACK number

  private:
    void copy(const Frame_Base& other);

  protected:
    bool operator==(const Frame_Base&) = delete;
    // make constructors protected to avoid instantiation

    // make assignment operator protected to force the user override it
    Frame_Base& operator=(const Frame_Base& other);

  public:
    Frame_Base(const Frame_Base& other);
    Frame_Base(const char *name=nullptr, short kind=0);

    virtual ~Frame_Base();
    virtual Frame_Base *dup() const override;
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getM_header() const;
    virtual void setM_header(int M_header);

    virtual const char * getM_payload() const;
    virtual void setM_payload(const char * M_payload);

    virtual const char * getM_Trailer() const;
    virtual void setM_Trailer(const char * M_Trailer);

    virtual int getM_Type() const;
    virtual void setM_Type(int M_Type);

    virtual int getM_Target() const;
    virtual void setM_Target(int M_Target);
};


namespace omnetpp {

template<> inline Frame_Base *fromAnyPtr(any_ptr ptr) { return check_and_cast<Frame_Base*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __FRAME_M_H

