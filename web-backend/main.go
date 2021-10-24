package main

import (
	"bytes"
	"log"
	"net/http"
	"net/http/cookiejar"
	"os"
)

/*
Local testing:
go build -o bin/main.exe -v .
heroku local web

Deployment:
go build -o bin/main -v .
*/

func main() {
	port := os.Getenv("PORT")

	if port == "" {
		log.Fatal("$PORT must be set")
	}

	http.HandleFunc("/", func(rw http.ResponseWriter, r *http.Request) {
		rw.Write(bytes.NewBufferString("pong").Bytes())
	})
	http.HandleFunc("/join", JoinParty)

	http.ListenAndServe(":"+port, nil)
}

func JoinParty(w http.ResponseWriter, r *http.Request) {
	req, valid := ValidateRequest(w, r)
	if !valid {
		return
	}

	jar, err := cookiejar.New(nil)
	if err != nil {
		log.Printf("Cookie initialization error, %v", err)
		w.WriteHeader(500)
		return
	}

	client := &http.Client{
		Jar: jar,
	}

	creds, err := Authenticate(client, req.Username, req.Password)
	if err != nil {
		log.Printf("Auth error, %v", err)
		w.WriteHeader(401)
		return
	}

	partyjoin(client, w, r, creds, req)
}