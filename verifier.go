package jclab_license_v2

import (
	"crypto/x509"
	_ "embed"
	"encoding/base64"
	"errors"
	"github.com/jc-lab/jclab-license-v2/internal/util"
	"github.com/jc-lab/jclab-license-v2/license_proto"
	"go.mozilla.org/pkcs7"
	"google.golang.org/protobuf/proto"
	"strings"
)

type Result struct {
	*license_proto.LicensePack
}

//go:embed internal/jclabconstant/jclab_license_authority.der
var jclabLicenseAuthorityDer []byte

var illegal bool
var trustedCertPool *x509.CertPool

func init() {
	cert, err := x509.ParseCertificate(jclabLicenseAuthorityDer)
	if err != nil {
		illegal = true
		panic(err)
	}
	trustedCertPool = x509.NewCertPool()
	trustedCertPool.AddCert(cert)
}

func Verify(input []byte) (Result, error) {
	result := Result{}
	signed, err := util.Decompress(input)
	if err != nil {
		return result, nil
	}
	p7, err := pkcs7.Parse(signed)
	if err != nil {
		return result, nil
	}
	err = p7.VerifyWithChain(trustedCertPool)
	if err != nil {
		return result, err
	}
	p7.Signers = p7.Signers[0:1]
	signerCert := p7.GetOnlySigner()
	var isLicenseCert bool
	for _, identifier := range signerCert.UnknownExtKeyUsage {
		if identifier.String() == "1.3.6.1.4.1.62615.10.3.1501" {
			isLicenseCert = true
		}
	}
	if !isLicenseCert {
		return result, errors.New("invalid signer certificate")
	}
	result.LicensePack = &license_proto.LicensePack{}
	if err = proto.Unmarshal(p7.Content, result.LicensePack); err != nil {
		return result, err
	}
	_ = signerCert
	return result, nil
}

func VerifyB64(input string) (Result, error) {
	input = strings.Trim(input, "= ")
	raw, err := base64.RawURLEncoding.DecodeString(input)
	if err != nil {
		return Result{}, err
	}
	return Verify(raw)
}
