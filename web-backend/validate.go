package main

import (
	"encoding/json"
	"io/ioutil"
	"log"
	"net/http"
)

func ValidateRequest(w http.ResponseWriter, r *http.Request) (valorantRequest, bool) {
	if r.Method != http.MethodPost {
		w.WriteHeader(405)
		return valorantRequest{}, false
	}
	body, err := ioutil.ReadAll(r.Body)
	if err != nil {
		log.Printf("Body read error, %v", err)
		w.WriteHeader(500)
		return valorantRequest{}, false
	}
	var reqBody valorantRequest
	err = json.Unmarshal(body, &reqBody)
	if err != nil {
		log.Printf("Incorrect json body: %v", err)
		w.WriteHeader(500)
		return valorantRequest{}, false
	}
	return reqBody, true
}
