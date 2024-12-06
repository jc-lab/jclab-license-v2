package jclab_license_v2

import (
	"fmt"
	"github.com/jc-lab/jclab-license-v2/license_proto"
	"google.golang.org/protobuf/proto"
	"testing"
)

func TestVerify(t *testing.T) {
	tests := []struct {
		input   string
		want    Result
		wantErr bool
	}{
		{
			"eJwzaGDj1GrzaPvOy8jOtKDBoIGJkdGQ14CbjTOhzYMxlZmFidEASQnjggaVBhZPjk0vTjzYaRTEVpJaXJJaFCUEoR1SKxJzC3JS9ZLzcxcxshWDOR8YL7QxL2IT5eKB8PUzUnNy8oVYw_2DfFwYwABobxPTeiA2WcDMxMjEJCKb5R3o8M9oLrvCJMvk0_XzNjN4fDTgYuMAOuOcLQszs4GyoaKBPBtzKAszj4SXs65PYpKCT2Zyal5xqoJjaUlGflFmSaWBnDivkYmhoYGRoYmBubFJFJBrBucaRxm4GKoYKEEMkUYzJDgzPS8zL13ByABoAr8BL0gVFw8bRJUhtwEnSIBNmMk7yCDSQJiNHewwJkaoC5kZ2ZmdGFhkrV9nb1-tee_StmhG55oDk8MyxRbOmf3zeIY2g70Tl5rh5pl613cpTK--Yr_4yjSzkENP8zZtbmPJU1uxcGtJXdj194ubGJUNmhjlDXiAtskKMzL-Z2EyYAD7W1aZRcJArEFklmLhmRjWyt2TRX69f_5Pet6fqNnsBuIgBaosAgZ8bDzabIwsjM0vxbmYu2MNGpeCZORZGucaNM4yaJy-IGdBVltGRklJgZW-fnKiXg7E93pZyTmJSXrZRfqpWUnJifoFpUlAmfLUJH0gTsksLtFPTi0qATHsk3NTbJOLctQyi4tLU4tsnf1UjV0ggaQNDUpteHwsUl-iSlzEyYKcyccixiJy0Dpk6jR94SMiu5o3qMea6Hn_4HkE9BZQmh8UHCzMTGwHkBMGcyaDQRqTIcM-8YcBrlacX9z6bygpMvJJrp5eHvmz61Yr95xjd3dft1Vp2_DTmItDUMP4z9TpX8TbVgG1_FLvf6WyniuW_45YAt8J6x0l3kFVX5a9_COr3vJV95lHzTv_SzwH5Bi1wpgMs9-4TctkYDBs_GTQ-B6YYQysifIXjnSNnNcWeBtIwHMbJ7MhN1LWM9BHyLAYKrEoZLkpbX52zOHxgttyVWYPfE9Hvza-wfHeWUsgaKHUq2ZDC6SAYWJxN3BlUmS40fdq1qctfG271W5eZXsuJOz86Eqk3qtQJ8Xm95der7FfzKRQfOWqvUVue_4C6Y_9fz1eSCyOOB-z9t1b5u2rf5kYLV30FJJjAdZxXZ0=",
			Result{
				LicensePack: &license_proto.LicensePack{
					IssuedAt:            1733490258994,
					LicenseeName:        "tester",
					LicenseeEmail:       "tester@example.com",
					LicensedProduct:     []string{"sample"},
					TimecenseMaxVersion: 50000,
					Attribute: map[string][]byte{
						"sample/hello": []byte("WORLD"),
					},
				},
			},
			false,
		},
	}
	for i, tt := range tests {
		t.Run(fmt.Sprintf("sample#%d", i+1), func(t *testing.T) {
			got, err := VerifyB64(tt.input)
			if (err != nil) != tt.wantErr {
				t.Errorf("Verify() error = %v, wantErr %v", err, tt.wantErr)
				return
			}
			if !proto.Equal(got.LicensePack, tt.want.LicensePack) {
				t.Errorf("Verify() got = %v, want %v", got, tt.want)
			}
		})
	}
}
