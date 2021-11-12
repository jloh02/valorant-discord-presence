package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"strings"
)

func partyjoin(client *http.Client, r *http.Request, creds valorantCredentials, req valorantRequest) (int, []byte) {
	//Request to join
	reqStatus, ret := join(fmt.Sprintf("/parties/%s/request", req.PartyId), client, r, creds, req)

	//If open party, joinparty directly
	if reqStatus == 400 && strings.Compare(ret.ErrorCode, "REQUEST_OPEN_PARTY") == 0 {
		reqStatus, ret = join(fmt.Sprintf("/players/%s/joinparty/%s", creds.PUUID, req.PartyId), client, r, creds, req)
	}

	log.Print(ret.ErrorCode)

	if reqStatus == 500 {
		ret.ErrorCode = "Unknown error has occured"
	}

	return reqStatus, []byte(ret.ErrorCode)
}

func join(endpoint string, client *http.Client, r *http.Request, creds valorantCredentials, req valorantRequest) (int, partyJoinResponse) {
	ptJoinReq, err := http.NewRequest(http.MethodPost, fmt.Sprintf("https://glz-%s-1.%s.a.pvp.net/parties/v1%s", req.Region, req.Region, endpoint), bytes.NewBufferString(fmt.Sprintf("{\"Subjects\":[\"%s\"]}", req.OwnerPuuid)))
	if err != nil {
		return 500, partyJoinResponse{}
	}
	ptJoinReq.Header.Add("Content-Type", "application/json")
	ptJoinReq.Header.Add("Authorization", creds.Token)
	ptJoinReq.Header.Add("X-Riot-Entitlements-JWT", creds.Entitlement)

	resp, err := client.Do(ptJoinReq)
	if err != nil {
		return 500, partyJoinResponse{}
	}

	var res partyJoinResponse
	resBytes, _ := ioutil.ReadAll(resp.Body)
	json.Unmarshal(resBytes, &res)
	return resp.StatusCode, res
}
