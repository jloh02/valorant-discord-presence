<template>
  <div class="auth-box">
      <h3 class="auth-header">Sign In to <br>Riot Account</h3>
      <form>
        <auth-input label='Username' type="text" @on-field-input="updateUsername"/>
        <auth-input label='Password' type="password" @on-field-input="updatePassword"/>
      </form>
      <p v-if="this.error" class="error-msg">Invalid username or password</p>
      <div v-if="!this.success" class="button-container">
        <button @click="submit">Sign In</button>
      </div>
  </div>
</template>

<script>
import AuthInput from './AuthInput.vue'
import { authenticate } from '@/auth.js'

export default {
  name: 'Auth',
  components: { AuthInput },
  data(){
    return{
      username: '',
      password: '',
      error: false,
      success: false,
    }
  },
  methods:{
    updateUsername(v) {
      this.username = v
    },
    updatePassword(v) {
      this.password = v
    },
    submit(){
      this.error = false;
      if(this.username.length == 0 || this.password.length == 0){
        this.error = true;
        return;
      }
      authenticate(this.username,this.password);
    },
  }
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
    min-width:fit-content;
    width: 20%;
    padding: 2rem;
  }

  h3.auth-header {
    text-align: center;
    color: whitesmoke;
    font-size: 1.5rem;
    margin: 0;
  }

  div.button-container{
    margin-top: 30px;
    display: flex;
    align-items: center;
    justify-content: space-around;
  }

  button{
    background-color: #ff4655; /* Green */
    border: none;
    color: whitesmoke;
    padding: 15px 32px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 1rem;
    border-radius: 10px;
  }

  button:hover{
    background-color: #ea3241;
  }

  p.error-msg{
    font-size: 1rem;
    color: red;
    text-align: center;
  }
</style>