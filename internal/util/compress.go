package util

import (
	"bytes"
	"compress/zlib"
	"io"
)

func Decompress(input []byte) ([]byte, error) {
	r, err := zlib.NewReader(bytes.NewReader(input))
	if err != nil {
		return nil, err
	}
	decompressed, err := io.ReadAll(r)
	if err != nil {
		return nil, err
	}

	return decompressed, nil
}
