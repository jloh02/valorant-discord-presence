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

func Authenticate(client *http.Client, username string, password string) (valorantCredentials, error) {

	if !GetCookies(client) {
		return valorantCredentials{}, fmt.Errorf("error connecting cookies")
	}

	token, err := Login(client, username, password)
	if err != nil {
		return valorantCredentials{}, err
	}
	//fmt.Println(token)

	ent, err := GetEntitlement(client, token)
	if err != nil {
		return valorantCredentials{}, err
	}
	//fmt.Println(ent)

	puuid, err := GetPUUID(client, token)
	if err != nil {
		return valorantCredentials{}, err
	}
	//fmt.Println(puuid)

	return valorantCredentials{puuid, token, ent}, nil
}

func GetCookies(client *http.Client) bool {
	cookieReqBody := []byte(`{"client_id":"play-valorant-web-prod","nonce":"1","redirect_uri":"https://playvalorant.com/opt_in","response_type":"token id_token"}`)
	req, err := http.NewRequest(http.MethodPost, "https://auth.riotgames.com/api/v1/authorization", bytes.NewBuffer(cookieReqBody))
	if err != nil {
		return false
	}
	req.Header.Add("Content-Type", "application/json")

	resp, err := client.Do(req)
	return err == nil && resp.StatusCode == 200
}

func Login(client *http.Client, username string, password string) (string, error) {
	authParams := authReqBody{"auth", username, password, true, "en_US"}
	authParamsBytes, err := json.Marshal(authParams)
	if err != nil {
		log.Printf("Json parsing error, %v", err)
		return "", err
	}

	req, err := http.NewRequest(http.MethodPut, "https://auth.riotgames.com/api/v1/authorization", bytes.NewBuffer(authParamsBytes))
	req.Header.Add("Content-Type", "application/json")
	if err != nil {
		return "", err
	}

	resp, err := client.Do(req)
	if err != nil || resp.StatusCode != 200 {
		return "", err
	}

	body, _ := ioutil.ReadAll(resp.Body)
	bodyStr := string(body)

	const searchFieldStart = "access_token="
	const searchFieldEnd = "&scope="

	fmt.Print(bodyStr)

	return "Bearer " + bodyStr[strings.Index(bodyStr, searchFieldStart)+len(searchFieldStart):strings.Index(bodyStr, searchFieldEnd)], nil
}

func GetEntitlement(client *http.Client, token string) (string, error) {
	req, err := http.NewRequest(http.MethodPost, "https://entitlements.auth.riotgames.com/api/token/v1", nil)

	req.Header.Add("Content-Type", "application/json")
	req.Header.Add("Authorization", token)
	if err != nil {
		return "", err
	}

	resp, err := client.Do(req)
	if err != nil {
		return "", err
	} else if resp.StatusCode != 200 {
		return "", fmt.Errorf("error status: %v", resp.Status)
	}

	var ent entitlement
	body, _ := ioutil.ReadAll(resp.Body)
	json.Unmarshal(body, &ent)

	return ent.EntitlementToken, nil
}

func GetPUUID(client *http.Client, token string) (string, error) {
	req, err := http.NewRequest(http.MethodPost, "https://auth.riotgames.com/userinfo", nil)
	req.Header.Add("Content-Type", "application/json")
	req.Header.Add("Authorization", token)
	if err != nil {
		return "", err
	}

	resp, err := client.Do(req)
	if err != nil {
		return "", err
	} else if resp.StatusCode != 200 {
		return "", fmt.Errorf("error status: %v", resp.Status)
	}

	var uinfo userinfo
	body, _ := ioutil.ReadAll(resp.Body)
	json.Unmarshal(body, &uinfo)

	return uinfo.PUUID, nil
}
