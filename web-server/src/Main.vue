<template>
  <div id="main" class="main">
    <auth />
    <bottom-banner />
  </div>
</template>

<script>
import Auth from './components/Auth.vue'
import BottomBanner from './components/BottomBanner.vue'

export default {
  name: 'Main',
  components: {
    Auth,
    BottomBanner
  }
}
</script>

<style>
.main { 
  font-family: Roboto, 'FF Mark W05', sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  background-image: url('~@/assets/background.jpg');
  background-size: cover;
  margin: 0;
  top: 0;
  left: 0;
  position: absolute;
  height: 100%;
  width: 100%;
}
</style>
