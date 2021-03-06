import { createApp } from 'vue'
import { createRouter, createWebHistory } from 'vue-router'
import Main from './components/Main.vue'
import App from './App.vue'

const app = createApp(App)

const router = createRouter({
  history: createWebHistory(),
  routes: [
    {
      path: '/',
      redirect: { name: 'Main' }
    },
   { path: '/valorant-discord-presence/', component: Main, name: 'Main' } 
  ]
})

app.use(router)

app.mount('#app')