// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Epsilon5.proto

#ifndef PROTOBUF_Epsilon5_2eproto__INCLUDED
#define PROTOBUF_Epsilon5_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace Epsilon5 {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Epsilon5_2eproto();
void protobuf_AssignDesc_Epsilon5_2eproto();
void protobuf_ShutdownFile_Epsilon5_2eproto();

class Player;
class Bullet;
class World;
class Control;
class Control_KeyStatus;

// ===================================================================

class Player : public ::google::protobuf::Message {
 public:
  Player();
  virtual ~Player();
  
  Player(const Player& from);
  
  inline Player& operator=(const Player& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Player& default_instance();
  
  void Swap(Player* other);
  
  // implements Message ----------------------------------------------
  
  Player* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Player& from);
  void MergeFrom(const Player& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required int32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);
  
  // required double x = 2;
  inline bool has_x() const;
  inline void clear_x();
  static const int kXFieldNumber = 2;
  inline double x() const;
  inline void set_x(double value);
  
  // required double y = 3;
  inline bool has_y() const;
  inline void clear_y();
  static const int kYFieldNumber = 3;
  inline double y() const;
  inline void set_y(double value);
  
  // required double vx = 4;
  inline bool has_vx() const;
  inline void clear_vx();
  static const int kVxFieldNumber = 4;
  inline double vx() const;
  inline void set_vx(double value);
  
  // required double vy = 5;
  inline bool has_vy() const;
  inline void clear_vy();
  static const int kVyFieldNumber = 5;
  inline double vy() const;
  inline void set_vy(double value);
  
  // required double angle = 6;
  inline bool has_angle() const;
  inline void clear_angle();
  static const int kAngleFieldNumber = 6;
  inline double angle() const;
  inline void set_angle(double value);
  
  // optional string name = 7;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 7;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  
  // @@protoc_insertion_point(class_scope:Epsilon5.Player)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_x();
  inline void clear_has_x();
  inline void set_has_y();
  inline void clear_has_y();
  inline void set_has_vx();
  inline void clear_has_vx();
  inline void set_has_vy();
  inline void clear_has_vy();
  inline void set_has_angle();
  inline void clear_has_angle();
  inline void set_has_name();
  inline void clear_has_name();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  double x_;
  double y_;
  double vx_;
  double vy_;
  double angle_;
  ::std::string* name_;
  ::google::protobuf::int32 id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(7 + 31) / 32];
  
  friend void  protobuf_AddDesc_Epsilon5_2eproto();
  friend void protobuf_AssignDesc_Epsilon5_2eproto();
  friend void protobuf_ShutdownFile_Epsilon5_2eproto();
  
  void InitAsDefaultInstance();
  static Player* default_instance_;
};
// -------------------------------------------------------------------

class Bullet : public ::google::protobuf::Message {
 public:
  Bullet();
  virtual ~Bullet();
  
  Bullet(const Bullet& from);
  
  inline Bullet& operator=(const Bullet& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Bullet& default_instance();
  
  void Swap(Bullet* other);
  
  // implements Message ----------------------------------------------
  
  Bullet* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Bullet& from);
  void MergeFrom(const Bullet& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required double x = 1;
  inline bool has_x() const;
  inline void clear_x();
  static const int kXFieldNumber = 1;
  inline double x() const;
  inline void set_x(double value);
  
  // required double y = 2;
  inline bool has_y() const;
  inline void clear_y();
  static const int kYFieldNumber = 2;
  inline double y() const;
  inline void set_y(double value);
  
  // required double vx = 3;
  inline bool has_vx() const;
  inline void clear_vx();
  static const int kVxFieldNumber = 3;
  inline double vx() const;
  inline void set_vx(double value);
  
  // required double vy = 4;
  inline bool has_vy() const;
  inline void clear_vy();
  static const int kVyFieldNumber = 4;
  inline double vy() const;
  inline void set_vy(double value);
  
  // @@protoc_insertion_point(class_scope:Epsilon5.Bullet)
 private:
  inline void set_has_x();
  inline void clear_has_x();
  inline void set_has_y();
  inline void clear_has_y();
  inline void set_has_vx();
  inline void clear_has_vx();
  inline void set_has_vy();
  inline void clear_has_vy();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  double x_;
  double y_;
  double vx_;
  double vy_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  friend void  protobuf_AddDesc_Epsilon5_2eproto();
  friend void protobuf_AssignDesc_Epsilon5_2eproto();
  friend void protobuf_ShutdownFile_Epsilon5_2eproto();
  
  void InitAsDefaultInstance();
  static Bullet* default_instance_;
};
// -------------------------------------------------------------------

class World : public ::google::protobuf::Message {
 public:
  World();
  virtual ~World();
  
  World(const World& from);
  
  inline World& operator=(const World& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const World& default_instance();
  
  void Swap(World* other);
  
  // implements Message ----------------------------------------------
  
  World* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const World& from);
  void MergeFrom(const World& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // repeated .Epsilon5.Player players = 1;
  inline int players_size() const;
  inline void clear_players();
  static const int kPlayersFieldNumber = 1;
  inline const ::Epsilon5::Player& players(int index) const;
  inline ::Epsilon5::Player* mutable_players(int index);
  inline ::Epsilon5::Player* add_players();
  inline const ::google::protobuf::RepeatedPtrField< ::Epsilon5::Player >&
      players() const;
  inline ::google::protobuf::RepeatedPtrField< ::Epsilon5::Player >*
      mutable_players();
  
  // repeated .Epsilon5.Bullet bullets = 2;
  inline int bullets_size() const;
  inline void clear_bullets();
  static const int kBulletsFieldNumber = 2;
  inline const ::Epsilon5::Bullet& bullets(int index) const;
  inline ::Epsilon5::Bullet* mutable_bullets(int index);
  inline ::Epsilon5::Bullet* add_bullets();
  inline const ::google::protobuf::RepeatedPtrField< ::Epsilon5::Bullet >&
      bullets() const;
  inline ::google::protobuf::RepeatedPtrField< ::Epsilon5::Bullet >*
      mutable_bullets();
  
  // required int32 playerId = 3;
  inline bool has_playerid() const;
  inline void clear_playerid();
  static const int kPlayerIdFieldNumber = 3;
  inline ::google::protobuf::int32 playerid() const;
  inline void set_playerid(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:Epsilon5.World)
 private:
  inline void set_has_playerid();
  inline void clear_has_playerid();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::Epsilon5::Player > players_;
  ::google::protobuf::RepeatedPtrField< ::Epsilon5::Bullet > bullets_;
  ::google::protobuf::int32 playerid_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_Epsilon5_2eproto();
  friend void protobuf_AssignDesc_Epsilon5_2eproto();
  friend void protobuf_ShutdownFile_Epsilon5_2eproto();
  
  void InitAsDefaultInstance();
  static World* default_instance_;
};
// -------------------------------------------------------------------

class Control_KeyStatus : public ::google::protobuf::Message {
 public:
  Control_KeyStatus();
  virtual ~Control_KeyStatus();
  
  Control_KeyStatus(const Control_KeyStatus& from);
  
  inline Control_KeyStatus& operator=(const Control_KeyStatus& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Control_KeyStatus& default_instance();
  
  void Swap(Control_KeyStatus* other);
  
  // implements Message ----------------------------------------------
  
  Control_KeyStatus* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Control_KeyStatus& from);
  void MergeFrom(const Control_KeyStatus& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required bool keyUp = 1;
  inline bool has_keyup() const;
  inline void clear_keyup();
  static const int kKeyUpFieldNumber = 1;
  inline bool keyup() const;
  inline void set_keyup(bool value);
  
  // required bool keyDown = 2;
  inline bool has_keydown() const;
  inline void clear_keydown();
  static const int kKeyDownFieldNumber = 2;
  inline bool keydown() const;
  inline void set_keydown(bool value);
  
  // required bool keyLeft = 3;
  inline bool has_keyleft() const;
  inline void clear_keyleft();
  static const int kKeyLeftFieldNumber = 3;
  inline bool keyleft() const;
  inline void set_keyleft(bool value);
  
  // required bool keyRight = 4;
  inline bool has_keyright() const;
  inline void clear_keyright();
  static const int kKeyRightFieldNumber = 4;
  inline bool keyright() const;
  inline void set_keyright(bool value);
  
  // required bool keyAttack1 = 5;
  inline bool has_keyattack1() const;
  inline void clear_keyattack1();
  static const int kKeyAttack1FieldNumber = 5;
  inline bool keyattack1() const;
  inline void set_keyattack1(bool value);
  
  // required bool keyAttack2 = 6;
  inline bool has_keyattack2() const;
  inline void clear_keyattack2();
  static const int kKeyAttack2FieldNumber = 6;
  inline bool keyattack2() const;
  inline void set_keyattack2(bool value);
  
  // @@protoc_insertion_point(class_scope:Epsilon5.Control.KeyStatus)
 private:
  inline void set_has_keyup();
  inline void clear_has_keyup();
  inline void set_has_keydown();
  inline void clear_has_keydown();
  inline void set_has_keyleft();
  inline void clear_has_keyleft();
  inline void set_has_keyright();
  inline void clear_has_keyright();
  inline void set_has_keyattack1();
  inline void clear_has_keyattack1();
  inline void set_has_keyattack2();
  inline void clear_has_keyattack2();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  bool keyup_;
  bool keydown_;
  bool keyleft_;
  bool keyright_;
  bool keyattack1_;
  bool keyattack2_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(6 + 31) / 32];
  
  friend void  protobuf_AddDesc_Epsilon5_2eproto();
  friend void protobuf_AssignDesc_Epsilon5_2eproto();
  friend void protobuf_ShutdownFile_Epsilon5_2eproto();
  
  void InitAsDefaultInstance();
  static Control_KeyStatus* default_instance_;
};
// -------------------------------------------------------------------

class Control : public ::google::protobuf::Message {
 public:
  Control();
  virtual ~Control();
  
  Control(const Control& from);
  
  inline Control& operator=(const Control& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Control& default_instance();
  
  void Swap(Control* other);
  
  // implements Message ----------------------------------------------
  
  Control* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Control& from);
  void MergeFrom(const Control& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  typedef Control_KeyStatus KeyStatus;
  
  // accessors -------------------------------------------------------
  
  // required .Epsilon5.Control.KeyStatus keyStatus = 1;
  inline bool has_keystatus() const;
  inline void clear_keystatus();
  static const int kKeyStatusFieldNumber = 1;
  inline const ::Epsilon5::Control_KeyStatus& keystatus() const;
  inline ::Epsilon5::Control_KeyStatus* mutable_keystatus();
  inline ::Epsilon5::Control_KeyStatus* release_keystatus();
  
  // required double angle = 2;
  inline bool has_angle() const;
  inline void clear_angle();
  static const int kAngleFieldNumber = 2;
  inline double angle() const;
  inline void set_angle(double value);
  
  // @@protoc_insertion_point(class_scope:Epsilon5.Control)
 private:
  inline void set_has_keystatus();
  inline void clear_has_keystatus();
  inline void set_has_angle();
  inline void clear_has_angle();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::Epsilon5::Control_KeyStatus* keystatus_;
  double angle_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_Epsilon5_2eproto();
  friend void protobuf_AssignDesc_Epsilon5_2eproto();
  friend void protobuf_ShutdownFile_Epsilon5_2eproto();
  
  void InitAsDefaultInstance();
  static Control* default_instance_;
};
// ===================================================================


// ===================================================================

// Player

// required int32 id = 1;
inline bool Player::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Player::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Player::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Player::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 Player::id() const {
  return id_;
}
inline void Player::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
}

// required double x = 2;
inline bool Player::has_x() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Player::set_has_x() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Player::clear_has_x() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Player::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline double Player::x() const {
  return x_;
}
inline void Player::set_x(double value) {
  set_has_x();
  x_ = value;
}

// required double y = 3;
inline bool Player::has_y() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Player::set_has_y() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Player::clear_has_y() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Player::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline double Player::y() const {
  return y_;
}
inline void Player::set_y(double value) {
  set_has_y();
  y_ = value;
}

// required double vx = 4;
inline bool Player::has_vx() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Player::set_has_vx() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Player::clear_has_vx() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Player::clear_vx() {
  vx_ = 0;
  clear_has_vx();
}
inline double Player::vx() const {
  return vx_;
}
inline void Player::set_vx(double value) {
  set_has_vx();
  vx_ = value;
}

// required double vy = 5;
inline bool Player::has_vy() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Player::set_has_vy() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Player::clear_has_vy() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Player::clear_vy() {
  vy_ = 0;
  clear_has_vy();
}
inline double Player::vy() const {
  return vy_;
}
inline void Player::set_vy(double value) {
  set_has_vy();
  vy_ = value;
}

// required double angle = 6;
inline bool Player::has_angle() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Player::set_has_angle() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Player::clear_has_angle() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Player::clear_angle() {
  angle_ = 0;
  clear_has_angle();
}
inline double Player::angle() const {
  return angle_;
}
inline void Player::set_angle(double value) {
  set_has_angle();
  angle_ = value;
}

// optional string name = 7;
inline bool Player::has_name() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void Player::set_has_name() {
  _has_bits_[0] |= 0x00000040u;
}
inline void Player::clear_has_name() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void Player::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& Player::name() const {
  return *name_;
}
inline void Player::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Player::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Player::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Player::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* Player::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// Bullet

// required double x = 1;
inline bool Bullet::has_x() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Bullet::set_has_x() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Bullet::clear_has_x() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Bullet::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline double Bullet::x() const {
  return x_;
}
inline void Bullet::set_x(double value) {
  set_has_x();
  x_ = value;
}

// required double y = 2;
inline bool Bullet::has_y() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Bullet::set_has_y() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Bullet::clear_has_y() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Bullet::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline double Bullet::y() const {
  return y_;
}
inline void Bullet::set_y(double value) {
  set_has_y();
  y_ = value;
}

// required double vx = 3;
inline bool Bullet::has_vx() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Bullet::set_has_vx() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Bullet::clear_has_vx() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Bullet::clear_vx() {
  vx_ = 0;
  clear_has_vx();
}
inline double Bullet::vx() const {
  return vx_;
}
inline void Bullet::set_vx(double value) {
  set_has_vx();
  vx_ = value;
}

// required double vy = 4;
inline bool Bullet::has_vy() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Bullet::set_has_vy() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Bullet::clear_has_vy() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Bullet::clear_vy() {
  vy_ = 0;
  clear_has_vy();
}
inline double Bullet::vy() const {
  return vy_;
}
inline void Bullet::set_vy(double value) {
  set_has_vy();
  vy_ = value;
}

// -------------------------------------------------------------------

// World

// repeated .Epsilon5.Player players = 1;
inline int World::players_size() const {
  return players_.size();
}
inline void World::clear_players() {
  players_.Clear();
}
inline const ::Epsilon5::Player& World::players(int index) const {
  return players_.Get(index);
}
inline ::Epsilon5::Player* World::mutable_players(int index) {
  return players_.Mutable(index);
}
inline ::Epsilon5::Player* World::add_players() {
  return players_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Epsilon5::Player >&
World::players() const {
  return players_;
}
inline ::google::protobuf::RepeatedPtrField< ::Epsilon5::Player >*
World::mutable_players() {
  return &players_;
}

// repeated .Epsilon5.Bullet bullets = 2;
inline int World::bullets_size() const {
  return bullets_.size();
}
inline void World::clear_bullets() {
  bullets_.Clear();
}
inline const ::Epsilon5::Bullet& World::bullets(int index) const {
  return bullets_.Get(index);
}
inline ::Epsilon5::Bullet* World::mutable_bullets(int index) {
  return bullets_.Mutable(index);
}
inline ::Epsilon5::Bullet* World::add_bullets() {
  return bullets_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Epsilon5::Bullet >&
World::bullets() const {
  return bullets_;
}
inline ::google::protobuf::RepeatedPtrField< ::Epsilon5::Bullet >*
World::mutable_bullets() {
  return &bullets_;
}

// required int32 playerId = 3;
inline bool World::has_playerid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void World::set_has_playerid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void World::clear_has_playerid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void World::clear_playerid() {
  playerid_ = 0;
  clear_has_playerid();
}
inline ::google::protobuf::int32 World::playerid() const {
  return playerid_;
}
inline void World::set_playerid(::google::protobuf::int32 value) {
  set_has_playerid();
  playerid_ = value;
}

// -------------------------------------------------------------------

// Control_KeyStatus

// required bool keyUp = 1;
inline bool Control_KeyStatus::has_keyup() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Control_KeyStatus::set_has_keyup() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Control_KeyStatus::clear_has_keyup() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Control_KeyStatus::clear_keyup() {
  keyup_ = false;
  clear_has_keyup();
}
inline bool Control_KeyStatus::keyup() const {
  return keyup_;
}
inline void Control_KeyStatus::set_keyup(bool value) {
  set_has_keyup();
  keyup_ = value;
}

// required bool keyDown = 2;
inline bool Control_KeyStatus::has_keydown() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Control_KeyStatus::set_has_keydown() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Control_KeyStatus::clear_has_keydown() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Control_KeyStatus::clear_keydown() {
  keydown_ = false;
  clear_has_keydown();
}
inline bool Control_KeyStatus::keydown() const {
  return keydown_;
}
inline void Control_KeyStatus::set_keydown(bool value) {
  set_has_keydown();
  keydown_ = value;
}

// required bool keyLeft = 3;
inline bool Control_KeyStatus::has_keyleft() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Control_KeyStatus::set_has_keyleft() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Control_KeyStatus::clear_has_keyleft() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Control_KeyStatus::clear_keyleft() {
  keyleft_ = false;
  clear_has_keyleft();
}
inline bool Control_KeyStatus::keyleft() const {
  return keyleft_;
}
inline void Control_KeyStatus::set_keyleft(bool value) {
  set_has_keyleft();
  keyleft_ = value;
}

// required bool keyRight = 4;
inline bool Control_KeyStatus::has_keyright() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Control_KeyStatus::set_has_keyright() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Control_KeyStatus::clear_has_keyright() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Control_KeyStatus::clear_keyright() {
  keyright_ = false;
  clear_has_keyright();
}
inline bool Control_KeyStatus::keyright() const {
  return keyright_;
}
inline void Control_KeyStatus::set_keyright(bool value) {
  set_has_keyright();
  keyright_ = value;
}

// required bool keyAttack1 = 5;
inline bool Control_KeyStatus::has_keyattack1() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Control_KeyStatus::set_has_keyattack1() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Control_KeyStatus::clear_has_keyattack1() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Control_KeyStatus::clear_keyattack1() {
  keyattack1_ = false;
  clear_has_keyattack1();
}
inline bool Control_KeyStatus::keyattack1() const {
  return keyattack1_;
}
inline void Control_KeyStatus::set_keyattack1(bool value) {
  set_has_keyattack1();
  keyattack1_ = value;
}

// required bool keyAttack2 = 6;
inline bool Control_KeyStatus::has_keyattack2() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Control_KeyStatus::set_has_keyattack2() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Control_KeyStatus::clear_has_keyattack2() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Control_KeyStatus::clear_keyattack2() {
  keyattack2_ = false;
  clear_has_keyattack2();
}
inline bool Control_KeyStatus::keyattack2() const {
  return keyattack2_;
}
inline void Control_KeyStatus::set_keyattack2(bool value) {
  set_has_keyattack2();
  keyattack2_ = value;
}

// -------------------------------------------------------------------

// Control

// required .Epsilon5.Control.KeyStatus keyStatus = 1;
inline bool Control::has_keystatus() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Control::set_has_keystatus() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Control::clear_has_keystatus() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Control::clear_keystatus() {
  if (keystatus_ != NULL) keystatus_->::Epsilon5::Control_KeyStatus::Clear();
  clear_has_keystatus();
}
inline const ::Epsilon5::Control_KeyStatus& Control::keystatus() const {
  return keystatus_ != NULL ? *keystatus_ : *default_instance_->keystatus_;
}
inline ::Epsilon5::Control_KeyStatus* Control::mutable_keystatus() {
  set_has_keystatus();
  if (keystatus_ == NULL) keystatus_ = new ::Epsilon5::Control_KeyStatus;
  return keystatus_;
}
inline ::Epsilon5::Control_KeyStatus* Control::release_keystatus() {
  clear_has_keystatus();
  ::Epsilon5::Control_KeyStatus* temp = keystatus_;
  keystatus_ = NULL;
  return temp;
}

// required double angle = 2;
inline bool Control::has_angle() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Control::set_has_angle() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Control::clear_has_angle() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Control::clear_angle() {
  angle_ = 0;
  clear_has_angle();
}
inline double Control::angle() const {
  return angle_;
}
inline void Control::set_angle(double value) {
  set_has_angle();
  angle_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Epsilon5

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Epsilon5_2eproto__INCLUDED
