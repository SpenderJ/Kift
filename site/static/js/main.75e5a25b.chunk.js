(window.webpackJsonp=window.webpackJsonp||[]).push([[0],{18:function(e,t,n){e.exports=n.p+"static/media/rick.fcf97f8c.png"},26:function(e,t,n){e.exports=n(44)},31:function(e,t,n){},37:function(e,t,n){},44:function(e,t,n){"use strict";n.r(t);var o=n(0),a=n.n(o),r=n(14),i=n.n(r),c=n(20),s=n(5),d=(n(31),n(15)),l=n(16),u=n(24),h=n(17),p=n(7),m=n(25),g=n(18),f=n.n(g),w=n(19),b=n.n(w),v=n(23),k=(n(37),function(e){function t(){var e;return Object(d.a)(this,t),(e=Object(u.a)(this,Object(h.a)(t).call(this))).handleKeyPress=function(t){" "===t.key&&(e.toggleRecording(),document.removeEventListener("keydown",e.handleKeyPress,!0))},e.state={input:"",recognition:"",record:!1},e.handleKeyPress=e.handleKeyPress.bind(Object(p.a)(e)),e.toggleRecording=e.toggleRecording.bind(Object(p.a)(e)),e.recorder=null,e}return Object(m.a)(t,e),Object(l.a)(t,[{key:"componentDidMount",value:function(){document.addEventListener("keydown",this.handleKeyPress)}},{key:"toggleRecording",value:function(){var e=this;if(!1===this.state.record){this.setState({record:!0,recognition:""});var t=new window.AudioContext||new window.webkitAudioContext;this.recorder=new b.a(t);navigator.mediaDevices.getUserMedia({audio:{sampleRate:16e3,channelCount:1}}).then(function(t){return e.recorder.init(t)}).catch(function(e){return console.log("There is a bug streaming...",e)}).then(function(){e.recorder.start()})}else this.setState({record:!1}),this.recorder.stop().then(function(t){var n=t.blob,o=(t.buffer,URL.createObjectURL(n));console.log(o);var a=new FormData;a.append("audio",n);var r={method:"POST",body:a};r&&r.headers&&delete r.headers["Content-Type"],fetch("http://127.0.0.1:6060/api/sendaudio",r).then(function(e){return e.text()}).then(function(t){console.log(t),e.setState({recognition:t})})})}},{key:"render",value:function(){return a.a.createElement("div",{className:"App"},a.a.createElement("header",{className:"App-header"},a.a.createElement("img",{src:f.a,className:"App-logo",alt:"logo"}),!1===this.state.record?a.a.createElement("h2",null," Speak with Rick"):a.a.createElement("h2",null," Speaking ..."),!1===this.state.record?a.a.createElement("button",{id:"speak",type:"button",disabled:!0}," Hit 'Space' and start speaking "):a.a.createElement("button",{type:"button",id:"stop"},"Hit 'Space' and wait for the answer "),""===this.state.recognition?a.a.createElement("p",{id:"comment"},' Try: "Hello", "Open Slack", "Look for 42 on Google" ...'):a.a.createElement("p",{id:"recognition"}," ' ",this.state.recognition," ' "),a.a.createElement(v.a,{record:this.state.record,className:"sound-wave",onStop:this.onStop,onData:this.onData,strokeColor:"#00FF00",backgroundColor:"#282C34"})))}}]),t}(a.a.Component));Boolean("localhost"===window.location.hostname||"[::1]"===window.location.hostname||window.location.hostname.match(/^127(?:\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)){3}$/));var y=a.a.createElement(c.a,null,a.a.createElement("div",null,a.a.createElement(s.a,{path:"/*",component:k})));i.a.render(y,document.getElementById("root")),"serviceWorker"in navigator&&navigator.serviceWorker.ready.then(function(e){e.unregister()})}},[[26,1,2]]]);
//# sourceMappingURL=main.75e5a25b.chunk.js.map