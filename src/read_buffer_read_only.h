//
// Created by joseph on 12/10/25.
//

#ifndef JCLAB_LICENSE_READ_BUFFER_READ_ONLY_H
#define JCLAB_LICENSE_READ_BUFFER_READ_ONLY_H

#include <stdint.h>

#include "ReadBufferInterface.h"

namespace jclab_license {
class ReadBufferReadOnly : public ::EmbeddedProto::ReadBufferInterface
{
public:
  //! 기본 생성자
  ReadBufferReadOnly(const uint8_t* data, uint32_t length);

  //! 기본 소멸자
  ~ReadBufferReadOnly() override = default;

  //! \see ::EmbeddedProto::ReadBufferInterface::get_size()
  uint32_t get_size() const override;

  //! \see ::EmbeddedProto::ReadBufferInterface::get_max_size()
  uint32_t get_max_size() const override;

  //! \see ::EmbeddedProto::ReadBufferInterface::peek()
  bool peek(uint8_t& byte) const override;

  //! \see ::EmbeddedProto::ReadBufferInterface::advance()
  bool advance() override;

  //! \see ::EmbeddedProto::ReadBufferInterface::advance(const uint32_t N)
  bool advance(const uint32_t N) override;

  //! \see ::EmbeddedProto::ReadBufferInterface::pop()
  bool pop(uint8_t& byte) override;

  //! 버퍼를 리셋하여 처음부터 다시 읽을 수 있도록 함
  void reset();

private:
  //! 외부 버퍼 데이터 (읽기 전용)
  const uint8_t* data_ = nullptr;

  //! 버퍼 길이
  uint32_t length_ = 0;

  //! 현재 읽기 인덱스
  uint32_t read_index_ = 0;
};

}

#endif // JCLAB_LICENSE_READ_BUFFER_READ_ONLY_H
