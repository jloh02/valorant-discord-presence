<template>
  <div class="banner">
    <div class="banner-container">  
      <div class="banner-vert-align-container">
        <div class="banner-text-container">
          <p>Disclaimer: This product is not affiliated to Riot Games. Usernames and passwords are only used to connect to Riot Games API and are not stored anywhere.<br>Refer to <a href="https://github.com/jloh02/valorant-discord-presence">source code</a> for confirmation <br><br> Project inspired by <a href="https://github.com/colinhartigan/valorant-rpc">Colin Hartigan</a>. Background wallpaper taken from <a href="https://4kwallpapers.com/games/phoenix-jett-valorant-pc-games-2020-games-2827.html">4kwallpapers</a>.</p>
        </div>
      </div>
      <div class="banner-vert-align-container">
        <!--a href="https://github.com/jloh02/valorant-discord-presence"><img src="@/assets/github-red.png"></a-->
        <!--img src="@/assets/github.png"-->
        <a href="https://github.com/jloh02/valorant-discord-presence"><div class="gh-icon"></div></a>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'BottomBanner',
}
</script>

<style>
  div.gh-icon{    
    height:30px;
    width:30px;
    display:inline-block;
    background:#eeeeee;
    -webkit-mask:url("~@/assets/github.png") center/contain;
            mask:url("~@/assets/github.png") center/contain;
    transition: background 0.1s;
  }

  div.gh-icon:hover{
    background:#bd0505;
  }

  div.banner{
    margin: 0;
    bottom: 0;
    left: 0;
    position: absolute;
    height: 12.5%;
    width: 100%;
    background-color:#000000bb;
  }

  div.banner-container{
    display:flex;
    justify-content: space-between;
    flex-direction: row;
    margin: auto;
    
    height:95%;
    width:90%;
  }

  div.banner-vert-align-container{
    display: flex;
    justify-content: center;
    align-content: center;
    flex-direction: column;
  }

  div.banner-text-container{    
    margin: auto 0;
  }

  p{
    font-size: 0.8rem;
    color:#eeeeee;    
  }

  a:link, a:hover, a:active, a:visited{
    color:#bd0505;
  }

  img{
    background:#eeeeee;

  }

</style>