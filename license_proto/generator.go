package license_proto

// prepare
// go install google.golang.org/protobuf/cmd/protoc-gen-go@latest

//go:generate protoc --proto_path=../java/jclab-license-model/src/main/proto/ --go_out=. --go_opt=paths=source_relative jclab-license.proto
