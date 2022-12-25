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
    h1,h2,h3{letter-spacing:-.1rem}body,h6{line-height:1.6}ol,p,ul{margin-top:0}.container{position:relative;width:350px;max-width:350px;margin:0 auto;padding:0 20px;box-sizing:border-box}.column,.columns{width:100%;float:left;box-sizing:border-box}html{background-color:#f5f5f5;font-size:62.5%}body{font-size:1.5em;font-weight:400;font-family:Raleway,HelveticaNeue,"Helvetica Neue",Helvetica,Arial,sans-serif;color:#222;overflow:hidden;-webkit-touch-callout:none;-webkit-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none}h1,h2,h3,h4,h5,h6{margin-top:0;margin-bottom:2rem;font-weight:300}h1{font-size:4rem;line-height:1.2}h2{font-size:3.6rem;line-height:1.25}h3{font-size:3rem;line-height:1.3}h4{font-size:2.4rem;line-height:1.35;letter-spacing:-.08rem}h5{font-size:1.8rem;line-height:1.5;letter-spacing:-.05rem}h6{font-size:1.5rem;letter-spacing:0}a{color:#1eaedb}a:hover{color:#0fa0ce}.button,button,input[type=button],input[type=reset],input[type=submit]{display:inline-block;height:38px;padding:0 30px;color:#555;text-align:center;font-size:11px;font-weight:600;line-height:38px;letter-spacing:.1rem;text-transform:uppercase;text-decoration:none;white-space:nowrap;background-color:transparent;border-radius:4px;border:1px solid #bbb;cursor:pointer;box-sizing:border-box}ol,td:first-child,th:first-child,ul{padding-left:0}.button:focus,.button:hover,button:focus,button:hover,input[type=button]:focus,input[type=button]:hover,input[type=reset]:focus,input[type=reset]:hover,input[type=submit]:focus,input[type=submit]:hover{color:#333;border-color:#888;outline:0}.button.button-primary,button.button-primary,input[type=button].button-primary,input[type=reset].button-primary,input[type=submit].button-primary{color:#fff;background-color:#33c3f0;border-color:#33c3f0}.button.button-primary:focus,.button.button-primary:hover,button.button-primary:focus,button.button-primary:hover,input[type=button].button-primary:focus,input[type=button].button-primary:hover,input[type=reset].button-primary:focus,input[type=reset].button-primary:hover,input[type=submit].button-primary:focus,input[type=submit].button-primary:hover{color:#fff;background-color:#1eaedb;border-color:#1eaedb}input[type=email],input[type=number],input[type=password],input[type=search],input[type=tel],input[type=text],input[type=url],select,textarea{height:38px;padding:6px 10px;background-color:#fff;border:1px solid #d1d1d1;border-radius:4px;box-shadow:none;box-sizing:border-box}input[type=email],input[type=number],input[type=password],input[type=search],input[type=tel],input[type=text],input[type=url],textarea{-webkit-appearance:none;-moz-appearance:none;appearance:none}textarea{min-height:65px;padding-top:6px;padding-bottom:6px}input[type=email]:focus,input[type=number]:focus,input[type=password]:focus,input[type=search]:focus,input[type=tel]:focus,input[type=text]:focus,input[type=url]:focus,select:focus,textarea:focus{border:1px solid #33c3f0;outline:0}label,legend{display:block;margin-bottom:.5rem;font-weight:600}fieldset{padding:0;border-width:0}input[type=checkbox],input[type=radio]{display:inline}label>.label-body{display:inline-block;margin-left:.5rem;font-weight:400}ul{list-style:circle inside}ol{list-style:decimal inside}ol ol,ol ul,ul ol,ul ul{margin:1.5rem 0 1.5rem 3rem;font-size:90%}.button,button,li{margin-bottom:1rem}td,th{padding:12px 15px;text-align:left;border-bottom:1px solid #e1e1e1}td:last-child,th:last-child{padding-right:0}fieldset,input,select,textarea{margin-bottom:1.5rem}blockquote,dl,figure,form,ol,p,pre,table,ul{margin-bottom:2.5rem}hr{margin-top:3rem;margin-bottom:3.5rem;border-width:0;border-top:1px solid #e1e1e1}.container:after,.row:after,.u-cf{content:"";display:table;clear:both}.one.columns{width:4.66666666667%}.two.columns{width:13.3333333333%}.three.columns{width:22%}.four.columns{width:30.6666666667%}.five.columns{width:39.3333333333%}.six.columns{width:48%}.seven.columns{width:56.6666666667%}.eight.columns{width:65.3333333333%}.nine.columns{width:74%}.ten.columns{width:82.6666666667%}.eleven.columns{width:91.3333333333%}.twelve.columns{width:100%;margin-left:0}
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
      <div class="eight columns">
        <h1 id="speed-o-meter">0.0</h1>
      </div>
      <div class="four columns">
        <h6 id="speed-o-meter-label">(m/s)</h6>
      </div>
    </div>
    <br>
    <div class="row">
      <button id="action" class="button-primary">Action</button>
    </div>
    <div class="row vertical-align-row " id="console-row">
      <div class="six columns">
        <button class="button">&#x2699; Config</button>
      </div>
      <div class="six columns">
        <p class="console" id="console"><small>&#x2139; CONSOLE</small></p>
      </div>
    </div>
  </div>
  <div style="position: fixed; top: 0px; left: 0px; right: 0px; height: 100vh;">
    <div id="joystick" style="position: relative; width: 200px; height: 200px; margin: auto; top: 50%;"></div>
  </div>

<script>
  let StickStatus={xPosition:0,yPosition:0,x:0,y:0,cardinalDirection:"C"};var JoyStick=function(t,e,i){var n=void 0===(e=e||{}).title?"joystick":e.title,o=void 0===e.width?0:e.width,a=void 0===e.height?0:e.height,r=void 0===e.internalFillColor?"#0096FF":e.internalFillColor,s=void 0===e.internalLineWidth?2:e.internalLineWidth,c=void 0===e.internalStrokeColor?"#FFFFFF":e.internalStrokeColor,d=void 0===e.externalLineWidth?2:e.externalLineWidth,u=void 0===e.externalStrokeColor?"#000000":e.externalStrokeColor,$=void 0===e.autoReturnToCenter||e.autoReturnToCenter;i=i||function(t){};var h=document.getElementById(t);h.style.touchAction="none";var l=document.createElement("canvas");l.id=n,0===o&&(o=h.clientWidth),0===a&&(a=h.clientHeight),l.width=o,l.height=a,h.appendChild(l);var S=l.getContext("2d"),f=0,_=2*Math.PI,k=(l.width-(l.width/2+10))/2,x=k+5,g=k+30,v=l.width/2,y=l.height/2,p=l.width/10,F=-1*p,P=l.height/10,E=-1*P,C=v,L=y;function T(){S.beginPath(),S.arc(v,y,g,0,_,!1),S.lineWidth=d,S.strokeStyle=u,S.stroke()}function m(){S.beginPath(),C<k&&(C=x),C+k>l.width&&(C=l.width-x),L<k&&(L=x),L+k>l.height&&(L=l.height-x),S.arc(C,L,k,0,_,!1);var t=S.createRadialGradient(v,y,5,v,y,200);t.addColorStop(0,r),t.addColorStop(1,c),S.fillStyle=t,S.fill(),S.lineWidth=s,S.strokeStyle=c,S.stroke()}"ontouchstart"in document.documentElement?(l.addEventListener("touchstart",function t(e){f=1,w=e.targetTouches[0].identifier},!1),document.addEventListener("touchmove",function t(e){1===f&&e.targetTouches[0].target===l&&(C=e.targetTouches[0].pageX,L=e.targetTouches[0].pageY,"BODY"===l.offsetParent.tagName.toUpperCase()?(C-=l.offsetLeft,L-=l.offsetTop):(C-=l.offsetParent.offsetLeft,L-=l.offsetParent.offsetTop),S.clearRect(0,0,l.width,l.height),T(),m(),StickStatus.xPosition=C,StickStatus.yPosition=L,StickStatus.x=(100*((C-v)/x)).toFixed(),StickStatus.y=(-(100*((L-y)/x)*1)).toFixed(),StickStatus.cardinalDirection=W(),i(StickStatus))},!1),document.addEventListener("touchend",function t(e){e.changedTouches[0].identifier===w&&(f=0,$&&(C=v,L=y),S.clearRect(0,0,l.width,l.height),T(),m(),StickStatus.xPosition=C,StickStatus.yPosition=L,StickStatus.x=(100*((C-v)/x)).toFixed(),StickStatus.y=(-(100*((L-y)/x)*1)).toFixed(),StickStatus.cardinalDirection=W(),i(StickStatus))},!1)):(l.addEventListener("mousedown",G,!1),document.addEventListener("mousemove",function t(e){1===f&&(C=e.pageX,L=e.pageY,"BODY"===l.offsetParent.tagName.toUpperCase()?(C-=l.offsetLeft,L-=l.offsetTop):(C-=l.offsetParent.offsetLeft,L-=l.offsetParent.offsetTop),S.clearRect(0,0,l.width,l.height),T(),m(),StickStatus.xPosition=C,StickStatus.yPosition=L,StickStatus.x=(100*((C-v)/x)).toFixed(),StickStatus.y=(-(100*((L-y)/x)*1)).toFixed(),StickStatus.cardinalDirection=W(),i(StickStatus))},!1),document.addEventListener("mouseup",function t(e){f=0,$&&(C=v,L=y),S.clearRect(0,0,l.width,l.height),T(),m(),StickStatus.xPosition=C,StickStatus.yPosition=L,StickStatus.x=(100*((C-v)/x)).toFixed(),StickStatus.y=(-(100*((L-y)/x)*1)).toFixed(),StickStatus.cardinalDirection=W(),i(StickStatus)},!1)),T(),m();let w=null;function G(t){f=1}function W(){let t="",e=C-v,i=L-y;return i>=E&&i<=P&&(t="C"),i<E&&(t="N"),i>P&&(t="S"),e<F&&("C"===t?t="W":t+="W"),e>p&&("C"===t?t="E":t+="E"),t}this.GetWidth=function(){return l.width},this.GetHeight=function(){return l.height},this.GetPosX=function(){return C},this.GetPosY=function(){return L},this.GetX=function(){return(100*((C-v)/x)).toFixed()},this.GetY=function(){return(-(100*((L-y)/x)*1)).toFixed()},this.GetDir=function(){return W()}};window.onload=function(){var t=document.getElementById("console"),e=document.getElementById("speed-o-meter");document.getElementById("action");var i=!1;function n(e,n){let o=new XMLHttpRequest;o.onload=()=>{t.innerText=200==o.status?n+" OK":"404",i=!1},o.ontimeout=()=>{i=!1,t.innerText="Timeout on XML request!"},o.onerror=()=>{i=!1,t.innerText="Error on XML request!"},o.open(e,n,!0),o.send()}document.addEventListener("touchstart",t=>{t.preventDefault()}),document.addEventListener("click",t=>{!i&&n("GET","/action")}),new JoyStick("joystick",{},function(t){if(0==t.x||0==t.y||!i){var o,a;i=!0,e.innerText=(o=t.y,a=t.x,(o/(Math.abs(a)+.001)%2).toFixed(1)),n("GET","/update?x="+t.x+"&y="+t.y)}})};
</script>
</body>
</html>
)rawliteral";
#endif
