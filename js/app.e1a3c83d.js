(function(e){function t(t){for(var r,i,c=t[0],s=t[1],u=t[2],d=0,p=[];d<c.length;d++)i=c[d],Object.prototype.hasOwnProperty.call(o,i)&&o[i]&&p.push(o[i][0]),o[i]=0;for(r in s)Object.prototype.hasOwnProperty.call(s,r)&&(e[r]=s[r]);l&&l(t);while(p.length)p.shift()();return a.push.apply(a,u||[]),n()}function n(){for(var e,t=0;t<a.length;t++){for(var n=a[t],r=!0,c=1;c<n.length;c++){var s=n[c];0!==o[s]&&(r=!1)}r&&(a.splice(t--,1),e=i(i.s=n[0]))}return e}var r={},o={app:0},a=[];function i(t){if(r[t])return r[t].exports;var n=r[t]={i:t,l:!1,exports:{}};return e[t].call(n.exports,n,n.exports,i),n.l=!0,n.exports}i.m=e,i.c=r,i.d=function(e,t,n){i.o(e,t)||Object.defineProperty(e,t,{enumerable:!0,get:n})},i.r=function(e){"undefined"!==typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(e,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(e,"__esModule",{value:!0})},i.t=function(e,t){if(1&t&&(e=i(e)),8&t)return e;if(4&t&&"object"===typeof e&&e&&e.__esModule)return e;var n=Object.create(null);if(i.r(n),Object.defineProperty(n,"default",{enumerable:!0,value:e}),2&t&&"string"!=typeof e)for(var r in e)i.d(n,r,function(t){return e[t]}.bind(null,r));return n},i.n=function(e){var t=e&&e.__esModule?function(){return e["default"]}:function(){return e};return i.d(t,"a",t),t},i.o=function(e,t){return Object.prototype.hasOwnProperty.call(e,t)},i.p="/valorant-discord-presence/";var c=window["webpackJsonp"]=window["webpackJsonp"]||[],s=c.push.bind(c);c.push=t,c=c.slice();for(var u=0;u<c.length;u++)t(c[u]);var l=s;a.push([0,"chunk-vendors"]),n()})({0:function(e,t,n){e.exports=n("56d7")},"1c0c":function(e,t,n){"use strict";n("e835")},"1ff2":function(e,t,n){"use strict";n("f84c")},3035:function(e,t,n){},"332c":function(e,t,n){},4654:function(e,t,n){},"56d7":function(e,t,n){"use strict";n.r(t);n("e260"),n("e6cf"),n("cca6"),n("a79d");var r=n("7a23"),o={id:"main",class:"main"};function a(e,t,n,a,i,c){var s=Object(r["j"])("auth"),u=Object(r["j"])("bottom-banner");return Object(r["i"])(),Object(r["d"])("div",o,[Object(r["h"])(s),Object(r["h"])(u)])}var i={class:"auth-box"},c={key:0},s=Object(r["e"])("p",{class:"completed-msg"}," You have been invited to the party. You may now close this webpage. ",-1),u=[s],l={key:1},d=Object(r["e"])("h3",{class:"auth-header"},[Object(r["g"])("Sign In to "),Object(r["e"])("br"),Object(r["g"])("Riot Account")],-1),p={novalidate:""},b={key:0,class:"error-msg"},f={class:"button-container"};function h(e,t,n,o,a,s){var h=Object(r["j"])("auth-input"),v=Object(r["j"])("loading");return Object(r["i"])(),Object(r["d"])("div",i,[a.success?(Object(r["i"])(),Object(r["d"])("div",c,u)):(Object(r["i"])(),Object(r["d"])("div",l,[d,Object(r["e"])("form",p,[Object(r["h"])(h,{label:"Username",type:"text",onOnFieldInput:s.updateUsername},null,8,["onOnFieldInput"]),Object(r["h"])(h,{label:"Password",type:"password",onOnFieldInput:s.updatePassword},null,8,["onOnFieldInput"])]),a.error?(Object(r["i"])(),Object(r["d"])("p",b,"Invalid username or password")):Object(r["c"])("",!0),Object(r["e"])("div",f,[this.success||this.loading?(Object(r["i"])(),Object(r["b"])(v,{key:1})):(Object(r["i"])(),Object(r["d"])("button",{key:0,onClick:t[0]||(t[0]=function(){return s.submit&&s.submit.apply(s,arguments)})}," Sign In "))])]))])}var v=n("1da1");n("96cf"),n("d3b7");function j(e,t){return m.apply(this,arguments)}function m(){return m=Object(v["a"])(regeneratorRuntime.mark((function e(t,n){var r,o;return regeneratorRuntime.wrap((function(e){while(1)switch(e.prev=e.next){case 0:return console.log(t),console.log(n),r={username:t,password:n,party_id:this.$route.query.party,region:this.$route.query.region,puuid:this.$route.query.puuid},e.next=5,fetch("https://valorant-invite.herokuapp.com/join",{method:"POST",body:JSON.stringify(r)});case 5:return o=e.sent,console.log(o.status),e.abrupt("return",!0);case 8:case"end":return e.stop()}}),e,this)}))),m.apply(this,arguments)}var O={class:"input-container"},g={class:"input-box"},y=["type"],w={class:"input-label"};function k(e,t,n,o,a,i){return Object(r["i"])(),Object(r["d"])("div",O,[Object(r["e"])("div",g,[Object(r["e"])("input",{type:n.type,onInput:t[0]||(t[0]=function(){return i.onInput&&i.onInput.apply(i,arguments)}),alt:"tt",required:""},null,40,y),Object(r["e"])("span",w,Object(r["k"])(n.label),1)])])}var I={name:"AuthInput",props:["label","type","fieldInput"],methods:{onInput:function(e){this.$emit("on-field-input",e.target.value)}}},x=(n("b5ab"),n("d959")),P=n.n(x);const S=P()(I,[["render",k]]);var _=S,A={class:"load"};function R(e,t,n,o,a,i){return Object(r["i"])(),Object(r["d"])("div",A)}var B={name:"Loading"};n("9c58");const M=P()(B,[["render",R]]);var T=M,q={name:"Auth",components:{AuthInput:_,Loading:T},data:function(){return{username:"",password:"",loading:!1,error:!1,success:!1}},methods:{updateUsername:function(e){this.username=e},updatePassword:function(e){this.password=e},submit:function(){var e=this;this.loading=!0,console.log(this.loading),this.error=!1,0!=this.username.length&&0!=this.password.length&&j(this.username,this.password)?this.success=!0:this.error=!0,setTimeout((function(){e.loading=!1}),1e3)}},created:function(){}};n("1c0c");const F=P()(q,[["render",h]]);var U=F,$={class:"banner"},J=Object(r["f"])('<div class="banner-container"><div class="banner-vert-align-container"><div class="banner-text-container"><p>Disclaimer: This product is not affiliated to Riot Games. Usernames and passwords are only used to connect to Riot Games API and are not stored anywhere.<br>Refer to <a href="https://github.com/jloh02/valorant-discord-presence">source code</a> for confirmation <br><br> Project inspired by <a href="https://github.com/colinhartigan/valorant-rpc">Colin Hartigan</a>. Background wallpaper taken from <a href="https://4kwallpapers.com/games/phoenix-jett-valorant-pc-games-2020-games-2827.html">4kwallpapers</a>.</p></div></div><div class="banner-vert-align-container"><a href="https://github.com/jloh02/valorant-discord-presence"><div class="gh-icon"></div></a></div></div>',1),C=[J];function G(e,t,n,o,a,i){return Object(r["i"])(),Object(r["d"])("div",$,C)}var L={name:"BottomBanner"};n("1ff2");const Y=P()(L,[["render",G]]);var D=Y,H={name:"Main",components:{Auth:U,BottomBanner:D}};n("ee93");const N=P()(H,[["render",a]]);var z=N,E=Object(r["a"])(z);E.mount("#main")},"9c58":function(e,t,n){"use strict";n("4654")},b5ab:function(e,t,n){"use strict";n("332c")},e835:function(e,t,n){},ee93:function(e,t,n){"use strict";n("3035")},f84c:function(e,t,n){}});
//# sourceMappingURL=app.e1a3c83d.js.map