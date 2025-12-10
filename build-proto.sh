#!/bin/bash

export CMAKE_CURRENT_SOURCE_DIR=$PWD

PROTO_FILE=${CMAKE_CURRENT_SOURCE_DIR}/java/jclab-license-model/src/main/proto/jclab_license.proto

if [ ! -d ${CMAKE_CURRENT_SOURCE_DIR}/third_party/EmbeddedProto/venv ]; then
  (cd ${CMAKE_CURRENT_SOURCE_DIR}/third_party/EmbeddedProto/ && python3 ./setup.py)
fi

export PATH=${CMAKE_CURRENT_SOURCE_DIR}/third_party/EmbeddedProto/venv/bin:$PATH

protoc \
  --plugin=protoc-gen-eams=${CMAKE_CURRENT_SOURCE_DIR}/third_party/EmbeddedProto/venv/bin/protoc-gen-eams \
  --eams_out=${CMAKE_CURRENT_SOURCE_DIR}/include/jclab_license/generated \
  --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/java/jclab-license-model/src/main/proto \
  ${PROTO_FILE}
