export async function joinParty (username, password) {
    console.log(username)
    console.log(password)

    const req = {
      "username":username,
      "password":password,
      "party_id":this.$route.query.party,
      "region":this.$route.query.region,
      "puuid":this.$route.query.puuid,
    }

    var res = await fetch('https://valorant-invite.herokuapp.com/join',{
      method: 'POST',
      //headers: {
        //'Accept': 'application/json', 
        //'Content-Type': 'application/json'
      //},
      body: JSON.stringify(req)
    })
    console.log(res.status)
    return true;
}