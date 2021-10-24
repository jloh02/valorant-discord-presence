package main

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"strings"
)

func partyjoin(client *http.Client, w http.ResponseWriter, r *http.Request, creds valorantCredentials, req valorantRequest) {
	//Request to join
	reqStatus, message := join(fmt.Sprintf("/parties/%s/request", req.PartyId), client, r, creds, req)

	//If open party, joinparty directly
	if reqStatus == 400 && strings.Contains(message, "REQUEST_OPEN_PARTY") {
		reqStatus, message = join(fmt.Sprintf("/players/%s/joinparty/%s", creds.PUUID, req.PartyId), client, r, creds, req)
	}

	if reqStatus != 200 {
		log.Print(message)
	}

	w.WriteHeader(reqStatus)
}

func join(endpoint string, client *http.Client, r *http.Request, creds valorantCredentials, req valorantRequest) (int, string) {
	ptJoinReq, err := http.NewRequest(http.MethodPost, fmt.Sprintf("https://glz-%s-1.%s.a.pvp.net/parties/v1%s", req.Region, req.Region, endpoint), bytes.NewBufferString(fmt.Sprintf("{\"Subjects\":[\"%s\"]}", req.OwnerPuuid)))
	if err != nil {
		return 500, "Unknown internal error"
	}
	ptJoinReq.Header.Add("Content-Type", "application/json")
	ptJoinReq.Header.Add("Authorization", creds.Token)
	ptJoinReq.Header.Add("X-Riot-Entitlements-JWT", creds.Entitlement)

	if resp, err := client.Do(ptJoinReq); err != nil || resp.StatusCode != 200 {
		r, _ := ioutil.ReadAll(resp.Body)
		return resp.StatusCode, string(r)
	} else {
		return 200, "Success"
	}
}
