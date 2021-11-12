package main

type valorantRequest struct {
	Username   string `json:"username"`
	Password   string `json:"password"`
	PartyId    string `json:"party_id"`
	Region     string `json:"region"`
	OwnerPuuid string `json:"puuid"`
}

type valorantCredentials struct {
	PUUID       string
	Token       string
	Entitlement string
}

type authReqBody struct {
	Type     string `json:"type"`
	Username string `json:"username"`
	Password string `json:"password"`
	Remember bool   `json:"remember"`
	Language string `json:"language"`
}

type entitlement struct {
	EntitlementToken string `json:"entitlements_token"`
}

type userinfo struct {
	PUUID string `json:"sub"`
	JTI   string `json:"jti"`
}

type partyJoinResponse struct {
	HttpStatus string `json:"httpStatus"`
	ErrorCode  string `json:"errorCode"`
	Message    string `json:"message"`
}
