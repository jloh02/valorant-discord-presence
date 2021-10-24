export async function authenticate (username, password) {
    console.log(username)
    console.log(password)

    const data = {"client_id":"play-valorant-web-prod","nonce":"1","redirect_uri":"https://playvalorant.com/opt_in","response_type":"token id_token"}
    var cookie_res = await fetch('https://auth.riotgames.com/api/v1/authorization',{
      method: 'POST',
      mode: 'no-cors',
      headers: {
        //'Accept': 'application/json', 
        'Content-Type': 'application/json'
      },
      body: JSON.stringify(data)
    })

    console.log(cookie_res.json())

}