(function(e){function t(t){for(var r,c,i=t[0],s=t[1],u=t[2],l=0,d=[];l<i.length;l++)c=i[l],Object.prototype.hasOwnProperty.call(a,c)&&a[c]&&d.push(a[c][0]),a[c]=0;for(r in s)Object.prototype.hasOwnProperty.call(s,r)&&(e[r]=s[r]);p&&p(t);while(d.length)d.shift()();return o.push.apply(o,u||[]),n()}function n(){for(var e,t=0;t<o.length;t++){for(var n=o[t],r=!0,i=1;i<n.length;i++){var s=n[i];0!==a[s]&&(r=!1)}r&&(o.splice(t--,1),e=c(c.s=n[0]))}return e}var r={},a={app:0},o=[];function c(t){if(r[t])return r[t].exports;var n=r[t]={i:t,l:!1,exports:{}};return e[t].call(n.exports,n,n.exports,c),n.l=!0,n.exports}c.m=e,c.c=r,c.d=function(e,t,n){c.o(e,t)||Object.defineProperty(e,t,{enumerable:!0,get:n})},c.r=function(e){"undefined"!==typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(e,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(e,"__esModule",{value:!0})},c.t=function(e,t){if(1&t&&(e=c(e)),8&t)return e;if(4&t&&"object"===typeof e&&e&&e.__esModule)return e;var n=Object.create(null);if(c.r(n),Object.defineProperty(n,"default",{enumerable:!0,value:e}),2&t&&"string"!=typeof e)for(var r in e)c.d(n,r,function(t){return e[t]}.bind(null,r));return n},c.n=function(e){var t=e&&e.__esModule?function(){return e["default"]}:function(){return e};return c.d(t,"a",t),t},c.o=function(e,t){return Object.prototype.hasOwnProperty.call(e,t)},c.p="/valorant-discord-presence/";var i=window["webpackJsonp"]=window["webpackJsonp"]||[],s=i.push.bind(i);i.push=t,i=i.slice();for(var u=0;u<i.length;u++)t(i[u]);var p=s;o.push([0,"chunk-vendors"]),n()})({0:function(e,t,n){e.exports=n("56d7")},"0336":function(e,t,n){},"04b0":function(e,t,n){"use strict";n("0336")},"1ff2":function(e,t,n){"use strict";n("f84c")},"335d":function(e,t,n){},4654:function(e,t,n){},"56d7":function(e,t,n){"use strict";n.r(t);n("e260"),n("e6cf"),n("cca6"),n("a79d");var r=n("7a23"),a=n("6c02"),o={id:"main",class:"main"};function c(e,t,n,a,c,i){var s=Object(r["v"])("auth"),u=Object(r["v"])("bottom-banner");return Object(r["r"])(),Object(r["e"])("div",o,[Object(r["i"])(s),Object(r["i"])(u)])}var i={class:"auth-box"},s={key:0},u=Object(r["f"])("p",{class:"completed-msg"},[Object(r["h"])(" You have requested to join the party. You may now close this webpage."),Object(r["f"])("br"),Object(r["f"])("br"),Object(r["h"])("If you would like to skip the login process, you may download the VALORANT Discord Presence "),Object(r["f"])("a",{href:"https://github.com/jloh02/valorant-discord-presence/releases"},"here"),Object(r["h"])(". ")],-1),p=[u],l={key:1},d=Object(r["f"])("h3",{class:"auth-header"},[Object(r["h"])("Sign In to "),Object(r["f"])("br"),Object(r["h"])("Riot Account")],-1),b={novalidate:""},h={key:0,class:"error-msg"},f={class:"button-container"};function v(e,t,n,a,o,c){var u=Object(r["v"])("auth-input"),v=Object(r["v"])("loading");return Object(r["r"])(),Object(r["e"])("div",i,[a.success?(Object(r["r"])(),Object(r["e"])("div",s,p)):(Object(r["r"])(),Object(r["e"])("div",l,[d,Object(r["f"])("form",b,[Object(r["i"])(u,{label:"Username",type:"text",onOnFieldInput:c.updateUsername},null,8,["onOnFieldInput"]),Object(r["i"])(u,{label:"Password",type:"password",onOnFieldInput:c.updatePassword},null,8,["onOnFieldInput"])]),o.error?(Object(r["r"])(),Object(r["e"])("p",h,Object(r["x"])(o.errorText),1)):Object(r["d"])("",!0),Object(r["f"])("div",f,[this.success||this.loading?(Object(r["r"])(),Object(r["c"])(v,{key:1})):(Object(r["r"])(),Object(r["e"])("button",{key:0,onClick:t[0]||(t[0]=function(){return c.submit&&c.submit.apply(c,arguments)}),class:"login-button"}," Sign In "))])]))])}var O=n("1da1"),j=(n("96cf"),n("d3b7"),{class:"input-container"}),m={class:"input-box"},g=["type","alt"],y={class:"input-label"},w={key:0,xmlns:"http://www.w3.org/2000/svg",viewBox:"0 0 24 24",height:"24px",width:"24px",fill:"#FFFFFF"},x=Object(r["f"])("path",{d:"M0 0h24v24H0z",fill:"none"},null,-1),k=Object(r["f"])("path",{d:"M12 4.5C7 4.5 2.73 7.61 1 12c1.73 4.39 6 7.5 11 7.5s9.27-3.11 11-7.5c-1.73-4.39-6-7.5-11-7.5zM12 17c-2.76 0-5-2.24-5-5s2.24-5 5-5 5 2.24 5 5-2.24 5-5 5zm0-8c-1.66 0-3 1.34-3 3s1.34 3 3 3 3-1.34 3-3-1.34-3-3-3z"},null,-1),I=[x,k],P={key:1,xmlns:"http://www.w3.org/2000/svg",height:"24px",viewBox:"0 0 24 24",width:"24px",fill:"#FFFFFF"},F=Object(r["f"])("path",{d:"M0 0h24v24H0zm0 0h24v24H0zm0 0h24v24H0zm0 0h24v24H0z",fill:"none"},null,-1),T=Object(r["f"])("path",{d:"M12 7c2.76 0 5 2.24 5 5 0 .65-.13 1.26-.36 1.83l2.92 2.92c1.51-1.26 2.7-2.89 3.43-4.75-1.73-4.39-6-7.5-11-7.5-1.4 0-2.74.25-3.98.7l2.16 2.16C10.74 7.13 11.35 7 12 7zM2 4.27l2.28 2.28.46.46C3.08 8.3 1.78 10.02 1 12c1.73 4.39 6 7.5 11 7.5 1.55 0 3.03-.3 4.38-.84l.42.42L19.73 22 21 20.73 3.27 3 2 4.27zM7.53 9.8l1.55 1.55c-.05.21-.08.43-.08.65 0 1.66 1.34 3 3 3 .22 0 .44-.03.65-.08l1.55 1.55c-.67.33-1.41.53-2.2.53-2.76 0-5-2.24-5-5 0-.79.2-1.53.53-2.2zm4.31-.78l3.15 3.15.02-.16c0-1.66-1.34-3-3-3l-.17.01z"},null,-1),M=[F,T];function z(e,t,n,a,o,c){return Object(r["r"])(),Object(r["e"])("div",j,[Object(r["f"])("div",m,[Object(r["f"])("input",{type:o.inputType,onInput:t[0]||(t[0]=function(){return c.onInput&&c.onInput.apply(c,arguments)}),alt:n.label,required:""},null,40,g),Object(r["f"])("span",y,Object(r["x"])(n.label),1),"Password"===n.label&&o.currentInput?(Object(r["r"])(),Object(r["e"])("button",{key:0,onClick:t[1]||(t[1]=function(){return c.showHidePw&&c.showHidePw.apply(c,arguments)}),class:"show-hide-button",type:"button"},["password"===o.inputType?(Object(r["r"])(),Object(r["e"])("svg",w,I)):(Object(r["r"])(),Object(r["e"])("svg",P,M))])):Object(r["d"])("",!0)])])}var S={name:"AuthInput",data:function(){return{inputType:this.type,currentInput:""}},props:["label","type","fieldInput"],methods:{onInput:function(e){this.currentInput=e.target.value,this.$emit("on-field-input",e.target.value)},showHidePw:function(){this.inputType="password"===this.inputType?"text":"password"}}},A=(n("04b0"),n("d959")),H=n.n(A);const R=H()(S,[["render",z]]);var B=R,_={class:"load"};function C(e,t,n,a,o,c){return Object(r["r"])(),Object(r["e"])("div",_)}var J={name:"Loading"};n("9c58");const L=H()(J,[["render",C]]);var U,q=L,N={name:"Auth",components:{AuthInput:B,Loading:q},setup:function(){var e=Object(a["c"])();U=e.query;var t=Object(r["u"])(!1);return D(t),{success:t}},data:function(){return{username:"",password:"",loading:!1,error:!1,errorText:""}},methods:{updateUsername:function(e){this.username=e},updatePassword:function(e){this.password=e},submit:function(){var e=this;if(this.loading=!0,this.error=!1,0==this.username.length||0==this.password.length)return this.error=!0,this.errorText="Invalid username or password",void(this.loading=!1);Y(this.username,this.password).then((function(t){t.text().then((function(n){t.ok?e.success=!0:(e.success=!1,e.error=!0,e.errorText=n),e.loading=!1}))}))}}};function D(e){return G.apply(this,arguments)}function G(){return G=Object(O["a"])(regeneratorRuntime.mark((function e(t){var n,r,a,o,c;return regeneratorRuntime.wrap((function(e){while(1)switch(e.prev=e.next){case 0:return n=36886,e.prev=1,e.next=4,fetch("http://localhost:".concat(n,"/ping"));case 4:return r=e.sent,e.next=7,r.text();case 7:if(a=e.sent,"pong"===a){e.next=11;break}return t.value=!1,e.abrupt("return");case 11:e.next=17;break;case 13:return e.prev=13,e.t0=e["catch"](1),t.value=!1,e.abrupt("return");case 17:return o={party:U.party,puuid:U.puuid},e.next=20,fetch("http://localhost:".concat(n,"/join"),{method:"POST",body:JSON.stringify(o)});case 20:c=e.sent,t.value=c.ok;case 22:case"end":return e.stop()}}),e,null,[[1,13]])}))),G.apply(this,arguments)}function Y(e,t){return V.apply(this,arguments)}function V(){return V=Object(O["a"])(regeneratorRuntime.mark((function e(t,n){var r,a;return regeneratorRuntime.wrap((function(e){while(1)switch(e.prev=e.next){case 0:return r={username:t,password:n,party_id:U.party,region:U.region,puuid:U.puuid},e.next=3,fetch("https://valorant-invite.herokuapp.com/join",{method:"POST",body:JSON.stringify(r)});case 3:return a=e.sent,e.abrupt("return",a);case 5:case"end":return e.stop()}}),e)}))),V.apply(this,arguments)}n("9ac5");const $=H()(N,[["render",v]]);var E=$,K={class:"banner"},Q=Object(r["g"])('<div class="banner-container"><div class="banner-vert-align-container"><div class="banner-text-container"><p>Disclaimer: This product is not affiliated to Riot Games. Usernames and passwords are only used to connect to Riot Games API and are not stored anywhere.<br>Refer to <a href="https://github.com/jloh02/valorant-discord-presence">source code</a> for confirmation <br><br> Project inspired by <a href="https://github.com/colinhartigan/valorant-rpc">Colin Hartigan</a>. Background wallpaper taken from <a href="https://4kwallpapers.com/games/phoenix-jett-valorant-pc-games-2020-games-2827.html">4kwallpapers</a>.</p></div></div><div class="banner-vert-align-container"><a href="https://github.com/jloh02/valorant-discord-presence"><div class="gh-icon"></div></a></div></div>',1),W=[Q];function X(e,t,n,a,o,c){return Object(r["r"])(),Object(r["e"])("div",K,W)}var Z={name:"BottomBanner"};n("1ff2");const ee=H()(Z,[["render",X]]);var te=ee,ne={name:"Main",components:{Auth:E,BottomBanner:te}};n("5d3c");const re=H()(ne,[["render",c]]);var ae=re;function oe(e,t,n,a,o,c){var i=Object(r["v"])("router-view");return Object(r["r"])(),Object(r["c"])(i)}var ce={name:"App"};const ie=H()(ce,[["render",oe]]);var se=ie,ue=Object(r["b"])(se),pe=Object(a["a"])({history:Object(a["b"])(),routes:[{path:"/",redirect:{name:"Main"}},{path:"/valorant-discord-presence/",component:ae,name:"Main"}]});ue.use(pe),ue.mount("#app")},"5d3c":function(e,t,n){"use strict";n("db09")},"9ac5":function(e,t,n){"use strict";n("335d")},"9c58":function(e,t,n){"use strict";n("4654")},db09:function(e,t,n){},f84c:function(e,t,n){}});
//# sourceMappingURL=app.3a63c933.js.map