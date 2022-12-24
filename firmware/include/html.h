#ifndef HTML_H
#define HTML_H

#include <Arduino.h>

// It can go up to 14k
const char homePage[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
  <title>BubbleButBot</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    .container {position: relative;width: 350px;max-width: 350px;margin: 0 auto;padding: 0 20px;box-sizing: border-box;}.column, .columns {width: 100%;float: left;box-sizing: border-box;}@media (min-width: 400px) {.container {width: 85%;padding: 0;}}@media (min-width: 550px) {.container {width: 80%;}.column, .columns {margin-left: 4%;}.column:first-child, .columns:first-child {margin-left: 0;}.one.column, .one.columns {width: 4.66666666667%;}.two.columns {width: 13.3333333333%;}.three.columns {width: 22%;}.four.columns {width: 30.6666666667%;}.five.columns {width: 39.3333333333%;}.six.columns {width: 48%;}.seven.columns {width: 56.6666666667%;}.eight.columns {width: 65.3333333333%;}.nine.columns {width: 74.0%;}.ten.columns {width: 82.6666666667%;}.eleven.columns {width: 91.3333333333%;}.twelve.columns {width: 100%;margin-left: 0;}.one-third.column {width: 30.6666666667%;}.two-thirds.column {width: 65.3333333333%;}.one-half.column {width: 48%;}.offset-by-one.column, .offset-by-one.columns {margin-left: 8.66666666667%;}.offset-by-two.column, .offset-by-two.columns {margin-left: 17.3333333333%;}.offset-by-three.column, .offset-by-three.columns {margin-left: 26%;}.offset-by-four.column, .offset-by-four.columns {margin-left: 34.6666666667%;}.offset-by-five.column, .offset-by-five.columns {margin-left: 43.3333333333%;}.offset-by-six.column, .offset-by-six.columns {margin-left: 52%;}.offset-by-seven.column, .offset-by-seven.columns {margin-left: 60.6666666667%;}.offset-by-eight.column, .offset-by-eight.columns {margin-left: 69.3333333333%;}.offset-by-nine.column, .offset-by-nine.columns {margin-left: 78.0%;}.offset-by-ten.column, .offset-by-ten.columns {margin-left: 86.6666666667%;}.offset-by-eleven.column, .offset-by-eleven.columns {margin-left: 95.3333333333%;}.offset-by-one-third.column, .offset-by-one-third.columns {margin-left: 34.6666666667%;}.offset-by-two-thirds.column, .offset-by-two-thirds.columns {margin-left: 69.3333333333%;}.offset-by-one-half.column, .offset-by-one-half.columns {margin-left: 52%;}}html {font-size: 62.5%;}body {font-size: 1.5em;line-height: 1.6;font-weight: 400;font-family: "Raleway", "HelveticaNeue", "Helvetica Neue", Helvetica, Arial, sans-serif;color: #222;}h1, h2, h3, h4, h5, h6 {margin-top: 0;margin-bottom: 2rem;font-weight: 300;}h1 {font-size: 4.0rem;line-height: 1.2;letter-spacing: -.1rem;}h2 {font-size: 3.6rem;line-height: 1.25;letter-spacing: -.1rem;}h3 {font-size: 3.0rem;line-height: 1.3;letter-spacing: -.1rem;}h4 {font-size: 2.4rem;line-height: 1.35;letter-spacing: -.08rem;}h5 {font-size: 1.8rem;line-height: 1.5;letter-spacing: -.05rem;}h6 {font-size: 1.5rem;line-height: 1.6;letter-spacing: 0;}@media (min-width: 550px) {h1 {font-size: 5.0rem;}h2 {font-size: 4.2rem;}h3 {font-size: 3.6rem;}h4 {font-size: 3.0rem;}h5 {font-size: 2.4rem;}h6 {font-size: 1.5rem;}}p {margin-top: 0;}a {color: #1EAEDB;}a:hover {color: #0FA0CE;}.button, button, input[type="submit"], input[type="reset"], input[type="button"] {display: inline-block;height: 38px;padding: 0 30px;color: #555;text-align: center;font-size: 11px;font-weight: 600;line-height: 38px;letter-spacing: .1rem;text-transform: uppercase;text-decoration: none;white-space: nowrap;background-color: transparent;border-radius: 4px;border: 1px solid #bbb;cursor: pointer;box-sizing: border-box;}.button:hover, button:hover, input[type="submit"]:hover, input[type="reset"]:hover, input[type="button"]:hover, .button:focus, button:focus, input[type="submit"]:focus, input[type="reset"]:focus, input[type="button"]:focus {color: #333;border-color: #888;outline: 0;}.button.button-primary, button.button-primary, input[type="submit"].button-primary, input[type="reset"].button-primary, input[type="button"].button-primary {color: #FFF;background-color: #33C3F0;border-color: #33C3F0;}.button.button-primary:hover, button.button-primary:hover, input[type="submit"].button-primary:hover, input[type="reset"].button-primary:hover, input[type="button"].button-primary:hover, .button.button-primary:focus, button.button-primary:focus, input[type="submit"].button-primary:focus, input[type="reset"].button-primary:focus, input[type="button"].button-primary:focus {color: #FFF;background-color: #1EAEDB;border-color: #1EAEDB;}input[type="email"], input[type="number"], input[type="search"], input[type="text"], input[type="tel"], input[type="url"], input[type="password"], textarea, select {height: 38px;padding: 6px 10px;background-color: #fff;border: 1px solid #D1D1D1;border-radius: 4px;box-shadow: none;box-sizing: border-box;}input[type="email"], input[type="number"], input[type="search"], input[type="text"], input[type="tel"], input[type="url"], input[type="password"], textarea {-webkit-appearance: none;-moz-appearance: none;appearance: none;}textarea {min-height: 65px;padding-top: 6px;padding-bottom: 6px;}input[type="email"]:focus, input[type="number"]:focus, input[type="search"]:focus, input[type="text"]:focus, input[type="tel"]:focus, input[type="url"]:focus, input[type="password"]:focus, textarea:focus, select:focus {border: 1px solid #33C3F0;outline: 0;}label, legend {display: block;margin-bottom: .5rem;font-weight: 600;}fieldset {padding: 0;border-width: 0;}input[type="checkbox"], input[type="radio"] {display: inline;}label > .label-body {display: inline-block;margin-left: .5rem;font-weight: normal;}ul {list-style: circle inside;}ol {list-style: decimal inside;}ol, ul {padding-left: 0;margin-top: 0;}ul ul, ul ol, ol ol, ol ul {margin: 1.5rem 0 1.5rem 3rem;font-size: 90%;}li {margin-bottom: 1rem;}code {padding: .2rem .5rem;margin: 0 .2rem;font-size: 90%;white-space: nowrap;background: #F1F1F1;border: 1px solid #E1E1E1;border-radius: 4px;}pre > code {display: block;padding: 1rem 1.5rem;white-space: pre;}th, td {padding: 12px 15px;text-align: left;border-bottom: 1px solid #E1E1E1;}th:first-child, td:first-child {padding-left: 0;}th:last-child, td:last-child {padding-right: 0;}button, .button {margin-bottom: 1rem;}input, textarea, select, fieldset {margin-bottom: 1.5rem;}pre, blockquote, dl, figure, table, p, ul, ol, form {margin-bottom: 2.5rem;}.u-full-width {width: 100%;box-sizing: border-box;}.u-max-full-width {max-width: 100%;box-sizing: border-box;}.u-pull-right {float: right;}.u-pull-left {float: left;}hr {margin-top: 3rem;margin-bottom: 3.5rem;border-width: 0;border-top: 1px solid #E1E1E1;}.container:after, .row:after, .u-cf {content: "";display: table;clear: both;}@media (min-width: 400px) {}@media (min-width: 550px) {}@media (min-width: 750px) {}@media (min-width: 1000px) {}@media (min-width: 1200px) {}
    .one.columns {width: 4.66666666667%;}.two.columns {width: 13.3333333333%;}.three.columns {width: 22%;}.four.columns {width: 30.6666666667%;}.five.columns {width: 39.3333333333%;}.six.columns {width: 48%;}.seven.columns {width: 56.6666666667%;}.eight.columns {width: 65.3333333333%;}.nine.columns {width: 74.0%;}.ten.columns {width: 82.6666666667%;}.eleven.columns {width: 91.3333333333%;}.twelve.columns {width: 100%;margin-left: 0;}

    html {
      background-color: whitesmoke;
    }

    body {
      overflow: hidden;
      -webkit-touch-callout: none;
      -webkit-user-select: none;
      -moz-user-select: none;
      -ms-user-select: none;
      user-select: none;
    }

    .vertical-align-row {
      display: flex;
      align-items: center;
    }

    #speed-o-meter {
      text-align: right;
      margin-right: 5px;
      font-size: 5em;
    }

    #speed-o-meter-label{
      text-align: left;
      margin-left: 5px;
    }

    #console-row {
      width: 100%;
      position: fixed;
      bottom: 10px;
    }

    .border {
      border-radius: 2px;
      border-color: black;
      border-style: solid;
    }
  </style>
</head>
<body>
  <div class="container">
    <br>
    <div class="row">
      <h4 style="text-align: center;">&#x1F579; BubbleButBot Controller</h4>
    </div>
    <br>
    <div class="row vertical-align-row">
      <!-- Speed-o-meter -->
      <div class="eight columns">
        <h1 id="speed-o-meter">0.0</h1>
      </div>
      <div class="four columns">
        <h6 id="speed-o-meter-label">(m/s)</h6>
      </div>
    </div>
    <div class="row vertical-align-row " id="console-row">
      <div class="five columns">
        <button class="button-primary">&#x2699; Config</button>
      </div>
      <div class="seven columns">
        <p class="console" id="console"><small>&#x2139; CONSOLE</small></p>
      </div>
    </div>
  </div>
  <div style="position: fixed; top: 0px; left: 0px; right: 0px; height: 100vh;">
    <div id="joystick" style="position: relative; width: 200px; height: 200px; margin: auto; top: 50%;"></div>
  </div>
<script>
let StickStatus={xPosition:0,yPosition:0,x:0,y:0,cardinalDirection:"C"};var JoyStick=function(t,e,i){var n=void 0===(e=e||{}).title?"joystick":e.title,o=void 0===e.width?0:e.width,r=void 0===e.height?0:e.height,a=void 0===e.internalFillColor?"#0096FF":e.internalFillColor,s=void 0===e.internalLineWidth?2:e.internalLineWidth,c=void 0===e.internalStrokeColor?"#FFFFFF":e.internalStrokeColor,d=void 0===e.externalLineWidth?2:e.externalLineWidth,u=void 0===e.externalStrokeColor?"#000000":e.externalStrokeColor,$=void 0===e.autoReturnToCenter||e.autoReturnToCenter;i=i||function(t){};var h=document.getElementById(t);h.style.touchAction="none";var l=document.createElement("canvas");l.id=n,0===o&&(o=h.clientWidth),0===r&&(r=h.clientHeight),l.width=o,l.height=r,h.appendChild(l);var S=l.getContext("2d"),f=0,_=2*Math.PI,k=(l.width-(l.width/2+10))/2,x=k+5,g=k+30,v=l.width/2,y=l.height/2,p=l.width/10,F=-1*p,P=l.height/10,C=-1*P,T=v,w=y;function E(){S.beginPath(),S.arc(v,y,g,0,_,!1),S.lineWidth=d,S.strokeStyle=u,S.stroke()}function L(){S.beginPath(),T<k&&(T=x),T+k>l.width&&(T=l.width-x),w<k&&(w=x),w+k>l.height&&(w=l.height-x),S.arc(T,w,k,0,_,!1);var t=S.createRadialGradient(v,y,5,v,y,200);t.addColorStop(0,a),t.addColorStop(1,c),S.fillStyle=t,S.fill(),S.lineWidth=s,S.strokeStyle=c,S.stroke()}"ontouchstart"in document.documentElement?(l.addEventListener("touchstart",function t(e){f=1,m=e.targetTouches[0].identifier},!1),document.addEventListener("touchmove",function t(e){1===f&&e.targetTouches[0].target===l&&(T=e.targetTouches[0].pageX,w=e.targetTouches[0].pageY,"BODY"===l.offsetParent.tagName.toUpperCase()?(T-=l.offsetLeft,w-=l.offsetTop):(T-=l.offsetParent.offsetLeft,w-=l.offsetParent.offsetTop),S.clearRect(0,0,l.width,l.height),E(),L(),StickStatus.xPosition=T,StickStatus.yPosition=w,StickStatus.x=(100*((T-v)/x)).toFixed(),StickStatus.y=(-(100*((w-y)/x)*1)).toFixed(),StickStatus.cardinalDirection=W(),i(StickStatus))},!1),document.addEventListener("touchend",function t(e){e.changedTouches[0].identifier===m&&(f=0,$&&(T=v,w=y),S.clearRect(0,0,l.width,l.height),E(),L(),StickStatus.xPosition=T,StickStatus.yPosition=w,StickStatus.x=(100*((T-v)/x)).toFixed(),StickStatus.y=(-(100*((w-y)/x)*1)).toFixed(),StickStatus.cardinalDirection=W(),i(StickStatus))},!1)):(l.addEventListener("mousedown",G,!1),document.addEventListener("mousemove",function t(e){1===f&&(T=e.pageX,w=e.pageY,"BODY"===l.offsetParent.tagName.toUpperCase()?(T-=l.offsetLeft,w-=l.offsetTop):(T-=l.offsetParent.offsetLeft,w-=l.offsetParent.offsetTop),S.clearRect(0,0,l.width,l.height),E(),L(),StickStatus.xPosition=T,StickStatus.yPosition=w,StickStatus.x=(100*((T-v)/x)).toFixed(),StickStatus.y=(-(100*((w-y)/x)*1)).toFixed(),StickStatus.cardinalDirection=W(),i(StickStatus))},!1),document.addEventListener("mouseup",function t(e){f=0,$&&(T=v,w=y),S.clearRect(0,0,l.width,l.height),E(),L(),StickStatus.xPosition=T,StickStatus.yPosition=w,StickStatus.x=(100*((T-v)/x)).toFixed(),StickStatus.y=(-(100*((w-y)/x)*1)).toFixed(),StickStatus.cardinalDirection=W(),i(StickStatus)},!1)),E(),L();let m=null;function G(t){f=1}function W(){let t="",e=T-v,i=w-y;return i>=C&&i<=P&&(t="C"),i<C&&(t="N"),i>P&&(t="S"),e<F&&("C"===t?t="W":t+="W"),e>p&&("C"===t?t="E":t+="E"),t}this.GetWidth=function(){return l.width},this.GetHeight=function(){return l.height},this.GetPosX=function(){return T},this.GetPosY=function(){return w},this.GetX=function(){return(100*((T-v)/x)).toFixed()},this.GetY=function(){return(-(100*((w-y)/x)*1)).toFixed()},this.GetDir=function(){return W()}};window.onload=function(){var t=document.getElementById("console"),e=document.getElementById("speed-o-meter"),i=!1;document.addEventListener("touchstart",t=>{t.preventDefault()}),new JoyStick("joystick",{},function(n){if(0==n.x||0==n.y||!i){var o,r;i=!0,e.innerText=(o=n.y,r=n.x,(o/(Math.abs(r)+.001)%2).toFixed(1)),function e(n,o){let r=new XMLHttpRequest;r.onload=()=>{t.innerText=200==r.status?o+" OK":"404",i=!1},r.ontimeout=()=>{i=!1,t.innerText="Timeout on XML request!"},r.onerror=()=>{i=!1,t.innerText="Error on XML request!"},r.open("GET",o,!0),r.send()}("GET","/update?x="+n.x+"&y="+n.y)}})};</script>
</body>
</html>
)rawliteral";
#endif
