#include "read_buffer_read_only.h"

namespace jclab_license {
//! 기본 생성자
ReadBufferReadOnly::ReadBufferReadOnly(const uint8_t* data, uint32_t length)
: data_(data),
  length_(length),
  read_index_(0)
{
}

//! \see ::EmbeddedProto::ReadBufferInterface::get_size()
uint32_t ReadBufferReadOnly::get_size() const
{
  // 전체 길이에서 현재 읽은 위치까지를 고려하여 남은 데이터 크기 반환
  return length_ - read_index_;
}

//! \see ::EmbeddedProto::ReadBufferInterface::get_max_size()
uint32_t ReadBufferReadOnly::get_max_size() const
{
  return length_;
}

//! \see ::EmbeddedProto::ReadBufferInterface::peek()
bool ReadBufferReadOnly::peek(uint8_t& byte) const
{
  const bool available = read_index_ < length_;
  if(available)
  {
    byte = data_[read_index_];
  }
  return available;
}

//! \see ::EmbeddedProto::ReadBufferInterface::advance()
bool ReadBufferReadOnly::advance()
{
  const bool available = read_index_ < length_;
  if(available)
  {
    ++read_index_;
  }
  return available;
}

//! \see ::EmbeddedProto::ReadBufferInterface::advance(const uint32_t N)
bool ReadBufferReadOnly::advance(const uint32_t N)
{
  const uint32_t new_index = read_index_ + N;
  const bool available = new_index <= length_;
  if(available)
  {
    read_index_ = new_index;
  }
  return available;
}

//! \see ::EmbeddedProto::ReadBufferInterface::pop()
bool ReadBufferReadOnly::pop(uint8_t& byte)
{
  const bool available = read_index_ < length_;
  if(available)
  {
    byte = data_[read_index_];
    ++read_index_;
  }
  return available;
}

//! 버퍼를 리셋하여 처음부터 다시 읽을 수 있도록 함
void ReadBufferReadOnly::reset()
{
  read_index_ = 0;
}

}